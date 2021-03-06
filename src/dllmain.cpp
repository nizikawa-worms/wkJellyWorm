#include <Windows.h>
#include <sigscanner.h>
#include "DevConsole.h"
#include "entities/tasks/CTaskFire.h"
#include "entities/tasks/CTaskFlame.h"
#include "entities/tasks/CTaskFilter.h"
#include "entities/tasks/CTaskAirStrike.h"
#include "entities/tasks/CTaskSpriteAnimation.h"
#include "entities/tasks/CTaskSmoke.h"
#include "entities/tasks/CTaskGass.h"
#include "entities/tasks/CTaskCPU.h"
#include "entities/tasks/CTaskCloud.h"
#include "entities/tasks/CTaskDirt.h"
#include "entities/tasks/CTaskFireBall.h"
#include "entities/tasks/CTaskScoreBubble.h"
#include "entities/tasks/CTaskSeaBubble.h"
#include "entities/gametasks/CTaskArrow.h"
#include "entities/gametasks/CTaskCanister.h"
#include "entities/gametasks/CTaskCrate.h"
#include "entities/gametasks/CTaskCross.h"
#include "entities/gametasks/CTaskLand.h"
#include "entities/gametasks/CTaskMine.h"
#include "entities/gametasks/CTaskMissile.h"
#include "entities/gametasks/CTaskOildrum.h"
#include "entities/gametasks/CTaskOldWorm.h"
#include "packages/PackageManager.h"

#include "WaLibc.h"
#include "Game.h"
#include "Lobby.h"
#include "Config.h"
#include "Chat.h"
#include "Landscape.h"
#include "Sounds.h"
#include "Sprites.h"
#include "Explosions.h"
#include "Weapons.h"
#include "renderer/Bitmap.h"
#include "renderer/Renderer.h"
#include "renderer/Drawing.h"

#include "CustomWeapons.h"
#include "Packets.h"
#include "Lua.h"
#include "Hooks.h"
#include <chrono>
#include <MinHook.h>

int install() {
	if(Config::devConsoleEnabled) DevConsole::install();
	SignatureScanner SigScanner;
	module mod = {0, 0};
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("Failed to initialize Minhook");

	WaLibc::install(SigScanner, mod);
	CTask::install(SigScanner, mod);
	CGameTask::install(SigScanner, mod);

	CTaskTurnGame::install(SigScanner, mod);
	CTaskTeam::install(SigScanner, mod);
	CTaskFire::install(SigScanner, mod);
	CTaskFlame::install(SigScanner, mod);
	CTaskFilter::install(SigScanner, mod);
	CTaskAirStrike::install(SigScanner, mod);
	CTaskSpriteAnimation::install(SigScanner, mod);
	CTaskSmoke::install(SigScanner, mod);
	CTaskGass::install(SigScanner, mod);
	CTaskCPU::install(SigScanner, mod);
	CTaskCloud::install(SigScanner, mod);
	CTaskDirt::install(SigScanner, mod);
	CTaskFireBall::install(SigScanner, mod);
	CTaskScoreBubble::install(SigScanner, mod);
	CTaskSeaBubble::install(SigScanner, mod);

	CTaskArrow::install(SigScanner, mod);
	CTaskCanister::install(SigScanner, mod);
	CTaskCrate::install(SigScanner, mod);
	CTaskCross::install(SigScanner, mod);
	CTaskLand::install(SigScanner, mod);
	CTaskMine::install(SigScanner, mod);
	CTaskMissile::install(SigScanner, mod);
	CTaskOildrum::install(SigScanner, mod);
	CTaskOldWorm::install(SigScanner, mod);
	CTaskWorm::install(SigScanner, mod);

	Game::install(SigScanner, mod);
	Lobby::install(SigScanner, mod);
	Config::install(SigScanner, mod);
	Chat::install(SigScanner, mod);
	Sounds::install(SigScanner, mod);
	Sprites::install(SigScanner, mod);
	Landscape::install(SigScanner, mod);
	Explosions::install(SigScanner, mod);
	Weapons::install(SigScanner, mod);
	CustomWeapons::install(SigScanner, mod);
	Packets::install(SigScanner, mod);
	Bitmap::install(SigScanner, mod);
	Renderer::install(SigScanner, mod);
	Drawing::install(SigScanner, mod);

	Lua::getInstance();

	PackageManager::getInstance().scanPackages();
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch(ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
		{
			auto start = std::chrono::high_resolution_clock::now();
			decltype(start) finish;
			try {
				Config::readPrivateProfile();
				if (!Config::moduleEnabled) return TRUE;
				Config::createJellyDirs();
				if(Config::useOffsetCache) Hooks::loadOffsets(Config::offsetsFile);
				install();
				finish = std::chrono::high_resolution_clock::now();
				Hooks::saveOffsets(Config::offsetsFile);
			} catch (std::exception &e) {
				finish = std::chrono::high_resolution_clock::now();
				MessageBoxA(0, e.what(), "wkJellyWorm - initialization failed", MB_ICONERROR);
			}
			std::chrono::duration<double> elapsed = finish - start;
			printf("wkJellyWorm startup took %lf seconds\n", elapsed.count());
		}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
		default:
			break;
	}
	return TRUE;
}
