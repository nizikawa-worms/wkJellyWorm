#include "PackageManager.h"
#include <filesystem>
#include <Windows.h>
#include <set>
#include <sstream>
#include "../Lobby.h"
#include "../Utils.h"
#include <args.hxx>
#include "../Config.h"
#include "../Lua.h"
#include <sol/sol.hpp>

namespace fs = std::filesystem;

PackageManager::PackageManager() {
	auto lua = Lua::getInstance().getState();
	lua->set_function("registerCallback_gameGlobalInit", &Callbacks<&gameGlobalInit_t>::registerCallback);
	lua->set_function("registerCallback_handleCGameTaskPhysics", &Callbacks<&handleCGameTaskPhysics_t>::registerCallback);
	lua->set_function("registerCallback_handleCreateExplosion", &Callbacks<&createExplosion_t>::registerCallback);
	lua->set_function("registerCallback_handleSpecialImpact", &Callbacks<&specialImpact_t>::registerCallback);
	lua->set_function("registerCallback_writeLandRaw", &Callbacks<&writeLandRaw_t>::registerCallback);
	lua->set_function("registerCallback_writeLandMaskID", &Callbacks<&writeLandMaskID_t>::registerCallback);
	lua->set_function("registerCallback_weaponRelease", &Callbacks<&weaponRelease_t>::registerCallback);
	lua->set_function("registerCallback_wormStartFiringWeapon", &Callbacks<&wormStartFiringWeapon_t>::registerCallback);
	lua->set_function("registerCallback_fireWeapon", &Callbacks<&fireWeapon_t>::registerCallback);
	lua->set_function("registerCallback_createWeaponProjectile", &Callbacks<&createWeaponProjectile_t>::registerCallback);

}

void PackageManager::clearCallbacks() {
	Callbacks<&gameGlobalInit_t>::clearCallbacks();
	Callbacks<&handleCGameTaskPhysics_t>::clearCallbacks();
}

PackageManager &PackageManager::getInstance() {
	static PackageManager instance;
	return instance;
}

void PackageManager::scanPackages() {
	packages.clear();
	allversions.clear();
	// add all installed packages
	for (const auto & entry : fs::recursive_directory_iterator(Config::packageDir)) {
		if(!entry.is_regular_file()) continue;
		if(entry.path().filename() == "manifest.json") {
			addPackage(entry.path().string());
		}
	}

	// remove packages with unmet dependencies
	std::vector<std::shared_ptr<Package>> brokenPackages;
	std::string brokenPackagesStr = "The following packages were disabled due to unmet dependencies:\n";
	for(auto & it : packages) {
		auto & manifest = it.second->getManifest();
		auto & dependencies = manifest["dependencies"];
		for(std::string dependency : dependencies) {
			if(allversions.find(dependency) == allversions.end()) {
				brokenPackages.push_back(it.second);
				brokenPackagesStr += it.second->getIdentifier() + " ";
				printf("unmet package dependencies: %s (%s)\n", it.second->getIdentifier().c_str(), dependency.c_str());
			}
		}
	}
	if(!brokenPackages.empty()) {
		MessageBoxA(0, brokenPackagesStr.c_str(), "wkJellyWorm", MB_ICONWARNING);
	}
	for(auto & package : brokenPackages) {
		packages.erase(package->getIdentifier());
		auto name = package->getName();
		allversions[name].erase(package);
		if(allversions[name].empty())
			allversions.erase(name);
	}

	// debug - determine latest verions of packages
	for(auto & it : allversions) {
		auto & name = it.first;
		auto latest = getLatestVersion(name);
		printf("latest: %s\n", latest->getIdentifier().c_str());
	}
}

void PackageManager::addPackage(std::string path) {
	try {
		printf("addPackage: %s\n", path.c_str());
		auto package = std::make_shared<Package>(path);
		auto name = package->getName();
		auto versionstr =  package->getVersionstr();
		auto identifier = package->getIdentifier();

		packages[identifier] = package;
		allversions[name].insert(package);

	} catch(std::exception & e) {
		std::string msg = "Failed to load package:\n" + path + "\n\n";
		msg += e.what();
		MessageBoxA(0, msg.c_str(), "wkJellyWorm - Failed to load package manifest", MB_ICONWARNING);
	}
}

void PackageManager::enablePackage(std::string name, std::string version, bool manual) {
	if(allversions.find(name) == allversions.end())
		throw std::runtime_error("Package " + name + " not found");
	std::shared_ptr<Package> pack = nullptr;
	if(version == "latest") {
		pack = getLatestVersion(name);
	} else {
		auto & allv = allversions[name];
		for(auto & packver : allv) {
			if(packver->getVersionstr() == version) {
				pack = packver;
				break;
			}
		}
	}
	if(pack == nullptr)
		throw std::runtime_error("Package version " + name + "(" + version + ") not found");

	enabledPackagesAll[name] = pack;
	if(manual)
		enabledPackagesExplicit[name] = pack;
}

void PackageManager::disablePackage(std::string name, bool manual) {
	if(enabledPackagesAll.find(name) == enabledPackagesAll.end())
		throw std::runtime_error("Package " + name + " is not enabled");
	if(manual) {
		if(enabledPackagesExplicit.find(name) != enabledPackagesExplicit.end())
			enabledPackagesExplicit.erase(name);
		else
			throw std::runtime_error("disablePackage: Package " + name + " is not found in enabledPackagesExplicit");
	}
	else{
		if(enabledPackagesAll.find(name) != enabledPackagesAll.end())
			enabledPackagesAll.erase(name);
		else
			throw std::runtime_error("disablePackage: Package " + name + " is not found in enabledPackagesAll");
	}
}

void PackageManager::checkDependenciesAdd() {
	std::set<std::string> added;
	bool changed;
	do {
		changed = false;
		for (auto &it : enabledPackagesAll) {
			auto & manifest = it.second->getManifest();
			auto & dependencies = manifest["dependencies"];
			for(std::string dependency : dependencies) {
				if(enabledPackagesAll.find(dependency) == enabledPackagesAll.end()) {
					added.insert(dependency);
					enablePackage(dependency, "latest", false);
					changed = true;
					printf("checkDependenciesAdd: added: %s\n", dependency.c_str());
				}
			}
		}
	} while(changed);
}


void PackageManager::checkDependenciesRemove() {
	enabledPackagesAll.clear();
	for(auto & it : enabledPackagesExplicit) {
		enabledPackagesAll[it.first] = it.second;
	}
	checkDependenciesAdd();
}

void PackageManager::handleLobbyListPackages(void * lobbyObj, bool all, bool manual, bool dependencies) {
	std::stringstream ss;
	if(all) {
		ss << "All packages:\n";
		for (auto &it : allversions) {
			ss << it.first << " : ";
			for (auto &ver : it.second) {
				ss << ver->getVersionstr() << " ";
			}
			ss << "\n";
		}
		ss << "\n";
	}

	if(manual) {
		ss << "Explicitly enabled packages:\n";
		for(auto & it : enabledPackagesExplicit) {
			ss << it.first << " " << it.second->getVersionstr() << "\n";
		}
		ss << "\n";
	}

	if(dependencies) {
		ss << "All enabled packages:\n";
		for(auto & it : enabledPackagesAll) {
			ss << it.first << " " << it.second->getVersionstr() << "\n";
		}
		ss << "\n";
	}
	Lobby::showGreenText(lobbyObj, (char *) ss.str().c_str());
}


int PackageManager::handleLobbyHostCommand(void *lobbyObj, std::string &command, std::string &args) {
	if(command == "packages") {
		handleLobbyListPackages(lobbyObj, true, true, true);
		return 1;
	}
	if(command == "enable") {
		std::vector<std::string> argsSplit;
		Utils::split_in_args(argsSplit, args);

		args::ArgumentParser parser("Enable specified package");
		args::HelpFlag help(parser, "help", "Display this help menu", {"help"});
		args::Positional<std::string> pathsList(parser, "name", "Package name");
		args::ValueFlag<std::string> packversion(parser, "version", "Specify package version", {"version", 'v'}, "latest");

		try {
			if (argsSplit.empty()) throw args::Help("");
			parser.ParseCLI(argsSplit);
			auto & name = pathsList.Get();
			auto & version = packversion.Get();
			enablePackage(name, version, true);
			checkDependenciesAdd();
		}
		catch (const args::Help &) {
			std::string help = "/" + command + parser.Help();
			Lobby::showGreenText(lobbyObj, (char *) help.c_str());
		}
		catch (const std::exception &e) {
			Lobby::showGreenText(lobbyObj, (char *) e.what());
		}
		handleLobbyListPackages(lobbyObj, false, true, true);
		Lobby::sendConfigString(lobbyObj);
		return 1;
	}
	if(command == "disable") {
		std::vector<std::string> argsSplit;
		Utils::split_in_args(argsSplit, args);

		args::ArgumentParser parser("Disable specified package");
		args::HelpFlag help(parser, "help", "Display this help menu", {"help"});
		args::Positional<std::string> pathsList(parser, "name", "Package name");

		try {
			if (argsSplit.empty()) throw args::Help("");
			parser.ParseCLI(argsSplit);
			auto & name = pathsList.Get();
			disablePackage(name, true);
			checkDependenciesRemove();
		}
		catch (const args::Help &) {
			std::string help = "/" + command + parser.Help();
			Lobby::showGreenText(lobbyObj, (char *) help.c_str());
		}
		catch (const std::exception &e) {
			Lobby::showGreenText(lobbyObj, (char *) e.what());
		}
		handleLobbyListPackages(lobbyObj, false, true, true);
		Lobby::sendConfigString(lobbyObj);
		return 1;
	}

	return Interface<&lobbyHostCli_t>::callAllPackages("lobbyHostCli", lobbyObj, command, args);
}

int PackageManager::handleLobbyClientCommand(void *lobbyObj, std::string &command, std::string &args) {
	return Interface<&lobbyClientCli_t>::callAllPackages("lobbyClientCli", lobbyObj, command, args);
}

std::shared_ptr<Package> PackageManager::getLatestVersion(std::string package) {
	if(allversions.find(package) == allversions.end()
	   || allversions[package].empty())
		throw std::runtime_error("getLatestVersion: nullptr " + package );
	return *allversions[package].begin();
}


int PackageManager::handleCGameTaskPhysics(int a1, CGameTask *object, int a3) {
	return Callbacks<&handleCGameTaskPhysics_t>::callCallbacks(a1, object, a3);
}

int PackageManager::handleGameGlobalInit() {
	return Callbacks<&gameGlobalInit_t>::callCallbacks();
}

int PackageManager::handleReadConfig(nlohmann::json & config) {
	enabledPackagesAll.clear();
	for(auto & entry : config["packages"]) {
		try {
			std::string name = entry["name"];
			std::string version = entry["version"];
			printf("enabling package: %s\n", name.c_str());
			enablePackage(name, version, 0);
			if(enabledPackagesAll.find(name) == enabledPackagesAll.end())
				throw std::runtime_error("enabling package failed");

			std::string configstr = entry["config"].dump();
			auto package = enabledPackagesAll[name];
			package->callInterface<int, std::function<int(std::string)>>("readConfig", configstr);
		} catch(std::exception & e) {
			printf("handleReadConfig::%s exception: %s\n", entry.dump().c_str(), e.what());
		}
	}
	return 0;
}

int PackageManager::handleWriteConfig(nlohmann::json & config) {
	for(auto & package : enabledPackagesAll) {
		try {
			auto packstr = package.second->callInterface<std::string, std::function<std::string()>>("writeConfig");
			auto packjson = nlohmann::json::parse(packstr);
			nlohmann::json entry = {{"name",package.second->getName()}, {"version",package.second->getVersionstr()}, {"config", packjson}};
			config["packages"][package.second->getIdentifier()] = entry;
		} catch(std::exception & e) {
			printf("handleWriteConfig::%s exception: %s\n", package.second->getIdentifier().c_str(), e.what());
		}
	}
	return 0;
}

int PackageManager::handleResetConfig() {
	int ret = Interface<&resetConfig_t>::callAllPackages("resetConfig");
	clearCallbacks();
	enabledPackagesAll.clear();
	enabledPackagesExplicit.clear();
	return ret;
}

int PackageManager::handleInitialize() {
	return Interface<&initialize_t>::callAllPackages("initialize");
}

int PackageManager::handleOnChatInput(char *msg) {
	return Interface<&onChatInput_t>::callAllPackages("onChatInput", msg);
}

int PackageManager::handleCreateExplosion(int posx, int posy, CGameTask *sender, int pushForce, int power, int a6, int team) {
	return Callbacks<&createExplosion_t>::callCallbacks(posx, posy, sender, pushForce, power, a6, team);
}

int PackageManager::handleSpecialImpact(CGameTask *This, int posX, int posY, int radiusX, int radiusY, int power, int pushX, int pushY, int type_a9, Constants::SoundIds soundOnHit, Constants::Sprites spriteOnHit, int collisionMask, int a13) {
	return Callbacks<&specialImpact_t>::callCallbacks(This, posX, posY, radiusX, radiusY, power, pushX, pushY, type_a9, soundOnHit, spriteOnHit, collisionMask, a13);
}

int PackageManager::handleWriteLandRaw(DWORD bitmap, DWORD PCLandscape, int posX, int posY, int layer) {
	return Callbacks<&writeLandRaw_t>::callCallbacks(bitmap, PCLandscape, posX, posY, layer);
}

int PackageManager::handleWriteLandRadius(DWORD PCLandscape, int radius, int posX, int posY) {
	return Callbacks<&writeLandRadius_t>::callCallbacks(PCLandscape, radius, posX, posY);
}

int PackageManager::handleWriteLandMaskID(DWORD PCLandscape, int maskid, int posX, int posY) {
	return Callbacks<&writeLandMaskID_t>::callCallbacks(PCLandscape, maskid, posX, posY);
}

int PackageManager::handleWeaponRelease(CGameTask *This, int posX, int posY, int angleX, int angleY) {
	return Callbacks<&weaponRelease_t>::callCallbacks(This, posX, posY, angleX, angleY);
}

int PackageManager::handleWormStartFiringWeapon(CTaskWorm *worm) {
	return Callbacks<&wormStartFiringWeapon_t>::callCallbacks(worm);
}

int PackageManager::handleFireWeapon(CTaskWorm *worm, CustomWeapons::WeaponStruct *weaponStruct, Weapons::WeaponLaunchParams *launchParams) {
	return Callbacks<&fireWeapon_t>::callCallbacks(worm, weaponStruct, launchParams);
}

int PackageManager::handleCreateWeaponProjectile(CGameTask *This, Weapons::WeaponProjectileParams *projectileParams, Weapons::WeaponLaunchParams *launchParams) {
	return Callbacks<&createWeaponProjectile_t>::callCallbacks(This, projectileParams, launchParams);
}
