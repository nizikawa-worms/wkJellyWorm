#ifndef WKJELLYWORM_PACKAGEMANAGER_H
#define WKJELLYWORM_PACKAGEMANAGER_H


#include <string>
#include <map>
#include <set>
#include <src/entities/CGameTask.h>
#include <src/entities/gametasks/CTaskWorm.h>
#include <src/CustomWeapons.h>
#include <src/Weapons.h>
#include "Package.h"


class PackageManager {
private:
	std::map<std::string, std::shared_ptr<Package>> packages;
	std::map<std::string, std::set<std::shared_ptr<Package>>> allversions;
	std::map<std::string, std::shared_ptr<Package>> enabledPackagesAll;
	std::map<std::string, std::shared_ptr<Package>> enabledPackagesExplicit;

	PackageManager();
	void addPackage(std::string path);
	void handleLobbyListPackages(void * lobbyObj, bool all, bool manual, bool dependencies);

public:

	// package callbacks - packages can register their functions as callbacks for various game events
	template<auto value> struct Callbacks;
	template<typename... Args, int(*ptr)(Args...)>
	struct Callbacks<ptr> {
		using callback_t = std::function<int(Args...)>;
		static inline std::vector<callback_t> callbacks;
		static void registerCallback(callback_t cb) {
			callbacks.push_back(cb);
		}
		static void clearCallbacks() {
			callbacks.clear();
		}
		template<typename ...Args>
		static int callCallbacks(Args... args) {
			int ret = 0;
			for(auto & cb : callbacks) {
				try {
					ret |= cb(args...);
				} catch (const std::exception & e) {
					printf("callCallbacks exception: %s\n", e.what());
				}
			}
			return ret;
		}
	};
	// package interface - all packages must implement specified functions
	template<auto value> struct Interface;
	template<typename... Args, int(*ptr)(Args...)>
	struct Interface<ptr> {
		using callback_t = std::function<int(Args...)>;
		template<typename ...Args>
		static int callAllPackages(std::string name, Args... args) {
			int ret=0;
			for(auto & package : getInstance().enabledPackagesAll) {
				ret |= package.second->callInterface<int, callback_t>(name, args...);
			}
			return ret;
		}
	};


	static PackageManager & getInstance();
	void scanPackages();
	void enablePackage(std::string name, std::string version, bool manual);
	void disablePackage(std::string name, bool manual);
	void checkDependenciesAdd();
	void checkDependenciesRemove();
	std::shared_ptr<Package> getLatestVersion(std::string package);



	static int handleCGameTaskPhysics_t(int, CGameTask*, int);
	static int gameGlobalInit_t();
	static int createExplosion_t(int posx, int posy, CGameTask * sender, int pushForce, int power, int a6, int team);
	static int specialImpact_t(CGameTask *This, int posX, int posY, int radiusX, int radiusY, int power, int pushX, int pushY, int type_a9, Constants::SoundIds soundOnHit, Constants::Sprites spriteOnHit, int collisionMask, int a13);

	static int writeLandRaw_t(DWORD bitmap, DWORD PCLandscape, int posX, int posY, int layer);
	static int writeLandRadius_t(DWORD PCLandscape, int radius, int posX, int posY);
	static int writeLandMaskID_t(DWORD PCLandscape, int maskid, int posX, int posY);

	static int weaponRelease_t(CGameTask * This, int posX, int posY, int angleX, int angleY);
	static int wormStartFiringWeapon_t(CTaskWorm * worm);
	static int fireWeapon_t(CTaskWorm * worm, CustomWeapons::WeaponStruct * weaponStruct, Weapons::WeaponLaunchParams * launchParams);
	static int createWeaponProjectile_t(CGameTask * This, Weapons::WeaponProjectileParams * projectileParams, Weapons::WeaponLaunchParams * launchParams);


	int handleCGameTaskPhysics(int a1, CGameTask * object, int a3);
	int handleGameGlobalInit();
	int handleCreateExplosion(int posx, int posy, CGameTask * sender, int pushForce, int power, int a6, int team);
	int handleSpecialImpact(CGameTask *This, int posX, int posY, int radiusX, int radiusY, int power, int pushX, int pushY, int type_a9, Constants::SoundIds soundOnHit, Constants::Sprites spriteOnHit, int collisionMask, int a13);
	int handleWriteLandRaw(DWORD bitmap, DWORD PCLandscape, int posX, int posY, int layer);
	int handleWriteLandRadius(DWORD PCLandscape, int radius, int posX, int posY);
	int handleWriteLandMaskID(DWORD PCLandscape, int maskid, int posX, int posY);

	int handleWeaponRelease(CGameTask * This, int posX, int posY, int angleX, int angleY);
	int handleWormStartFiringWeapon(CTaskWorm * worm);
	int handleFireWeapon(CTaskWorm * worm, CustomWeapons::WeaponStruct * weaponStruct, Weapons::WeaponLaunchParams * launchParams);
	int handleCreateWeaponProjectile(CGameTask * This, Weapons::WeaponProjectileParams * projectileParams, Weapons::WeaponLaunchParams * launchParams);


	void clearCallbacks();


	static int lobbyHostCli_t(void *, std::string&, std::string&);
	static int lobbyClientCli_t(void *, std::string&, std::string&);
	static int readConfig_t(std::string&);
	static int writeConfig_t();
	static int resetConfig_t();
	static int printLobbyHelpCommand_t(void *);
	static int onChatInput_t(char *msg);
	static int initialize_t();

	int handleLobbyHostCommand(void *lobbyObj, std::string &command, std::string &args);
	int handleLobbyClientCommand(void *lobbyObj, std::string &command, std::string &args);

	int handleReadConfig(nlohmann::json & config);
	int handleWriteConfig(nlohmann::json & config);
	int handleResetConfig();
	int handleInitialize();
	int handleOnChatInput(char * msg);
};

#endif //WKJELLYWORM_PACKAGEMANAGER_H
