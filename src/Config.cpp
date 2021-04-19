#include "Config.h"
#include <MinHook.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <git.h>
#include <src/packages/PackageManager.h>

#include "Game.h"
#include "CustomWeapons.h"
#include "Sounds.h"
#include "Sprites.h"

namespace fs = std::filesystem;

const std::string Config::jellyBuildTime = __DATE__ " " __TIME__;

void Config::onConstructGlobalContext(int a1) {
	DWORD addrGameinfoObject = Game::getAddrGameinfoObject();
	char * outputReplayPath = (char*)(addrGameinfoObject + 0xDF60);
	char * inputReplayPath = (char*)(addrGameinfoObject + 0xDB60);
	if(strlen(outputReplayPath) && !strlen(inputReplayPath)) saveConfigReplay(outputReplayPath);
	if(!strlen(outputReplayPath) && strlen(inputReplayPath)) loadConfigReplay(inputReplayPath);
}

void Config::createJellyDirs() {
	auto dirs = {jellyDir, schemeDir, luaLibDir, packageDir};
	for (auto & dir : dirs) {
		fs::create_directories(dir);
	}
}

void Config::loadConfigReplay(char *basepath) {
	std::string path(basepath);
	path += schemeExt;
	std::ifstream in(path);
	if (in.good()) {
		std::stringstream buffer;
		buffer << in.rdbuf();
		in.close();
		parseConfigString((char*)buffer.str().c_str());
	}
}

void Config::saveConfigReplay(char *basepath) {
	if(currentConfig.empty()) return;
	std::string path(basepath);
	path += schemeExt;
	std::ofstream out(path);
	if (out.good()) {
		std::string config = getConfigString(4);
		out << config;
		out.close();
	}
}

int Config::saveConfigToFile(std::string & filename) {
	std::string config = getConfigString(4);
	std::string path = schemeDir + "/" + filename + schemeExt;
	std::ofstream out(path);
	if (out.good()) {
		out << config;
		out.close();
		return 0;
	}
	return -1;
}

int Config::loadConfigFromFile(std::string & filename) {
	std::string path = schemeDir + "/" + filename + schemeExt;
	std::ifstream in(path);
	if (in.good()) {
		std::stringstream buffer;
		buffer << in.rdbuf();
		in.close();
		parseConfigString((char*)buffer.str().c_str());
		return 0;
	}
	return -1;
}

std::string Config::listConfigFiles() {
	std::string files;
	for (const auto & entry : fs::directory_iterator(schemeDir)) {
		if(!entry.is_regular_file()) continue;
		if(entry.path().extension().string() == schemeExt) {
			files += entry.path().filename().stem().string() + " ";
		}
	}
	return files;
}


bool Config::parseConfigString(char *config) {
	try {
		currentConfig = nlohmann::json::parse(config);
		printf("configstr: %s\n", config);
		PackageManager::getInstance().handleReadConfig(currentConfig);
	} catch(std::exception & e) {
		printf("parseConfigString:: failed to parse config string: %s\njson config: %s\n", e.what(), config);
		return false;
	}
	return true;
}

void Config::resetConfig() {
	currentConfig = {};
	PackageManager::getInstance().handleResetConfig();
	CustomWeapons::resetConfig();
	Sounds::resetConfig();
	Sprites::resetConfig();
}

std::string Config::getConfigString(int indent, bool host) {
	if(host) {
		currentConfig = {};
		PackageManager::getInstance().handleWriteConfig(currentConfig);
		writeVersionToJson(currentConfig, "host");
	}
	if(!host)
		writeVersionToJson(currentConfig, "local");
	return currentConfig.dump(indent);
}

int Config::install(SignatureScanner & signatureScanner, module mod) {
	return 0;
}

std::string Config::getJellyVersionMessage() {
	std::stringstream ss;
	ss << "wkJellyWorm v. " << jellyVersionStr << " (built: " << jellyBuildTime << ")";
	if(GitMetadata::Populated()) {
		ss << "\nGit commit: " << GitMetadata::CommitSubject() << " (" << GitMetadata::Describe() << ") " << GitMetadata::CommitDate() << " [ " << GitMetadata::AuthorName() << " - " << GitMetadata::AuthorEmail() << " ]";
		ss << "\n" << (GitMetadata::AnyUncommittedChanges() ? "[Uncommitted changes are present]" : "");
	}
	return ss.str();
}

int Config::getJellyVersionInt() {
	return jellyVersionInt;
}

std::string Config::getJellyVersionStr() {
	return jellyVersionStr;
}

int Config::writeVersionToJson(nlohmann::json &config, std::string type) {
	auto & ver = config["version"][type];
	ver = {
			{"versionstr", jellyVersionStr},
			{"versionInt", jellyVersionInt},
			{"built", jellyBuildTime},
			{"git", {
				{"populated",GitMetadata::Populated()},
				{"commitSubject",GitMetadata::CommitSubject()},
				{"commitDescribe",GitMetadata::Describe()},
				{"commitSha1",GitMetadata::CommitSHA1()},
				{"commitBody",GitMetadata::CommitBody()},
				{"commitDate",GitMetadata::CommitDate()},
				{"authorName",GitMetadata::AuthorName()},
				{"authorEmail",GitMetadata::AuthorEmail()},
				{"uncommittedChanges",GitMetadata::AnyUncommittedChanges()},
			}}
	};
	return 0;
}

void Config::readPrivateProfile() {
	moduleEnabled = GetPrivateProfileIntA("general", "EnableModule", 1, iniFile.c_str());
	useOffsetCache = GetPrivateProfileIntA("general", "UseOffsetCache", 0, iniFile.c_str());

	devConsoleEnabled = GetPrivateProfileIntA("debug", "EnableDevConsole", 0, iniFile.c_str());
	signatureMismatchWarning = GetPrivateProfileIntA("debug", "SignatureMismatchWarning", 0, iniFile.c_str());

	rendererEnabled = GetPrivateProfileIntA("renderer", "EnableCustomRenderer", 1, iniFile.c_str());
	rendererDebugContext = GetPrivateProfileIntA("renderer", "DebugContext", 0, iniFile.c_str());
	rendererGLMajor = GetPrivateProfileIntA("renderer", "GLVersionMajor", 3, iniFile.c_str());
	rendererGLMinor = GetPrivateProfileIntA("renderer", "GLVersionMinor", 2, iniFile.c_str());
	rendererDebugPoints = GetPrivateProfileIntA("renderer", "EnableDebugPoints", 0, iniFile.c_str());
}
