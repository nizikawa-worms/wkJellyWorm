#ifndef WKJELLYWORM_GAME_H
#define WKJELLYWORM_GAME_H

#include <sigscanner.h>
#include <src/entities/Entities.h>
#include <src/entities/gametasks/CTaskWorm.h>
#include <src/entities/tasks/CTaskTurnGame.h>
#include "Constants.h"

class Game {
private:
	inline static DWORD addrDDGame = 0;
	inline static DWORD addrDDDisplay = 0;
	inline static DWORD addrDSSound = 0;
	inline static DWORD addrDDKeyboard= 0;
	inline static DWORD addrDDMouse = 0;
	inline static DWORD addrWavCDRom = 0;
	inline static DWORD addrWSGameNet = 0;

private:
	inline static DWORD addrGameinfoObject = 0;

	inline static DWORD addrCTaskTurnGameHandleMessage = 0;

	static int __stdcall hookConstructGlobalContext(int a1);
//	static int __fastcall hookConstructCTaskTurnGame(DWORD ECX, DWORD EDX, DWORD This, int y);
//	static int __stdcall hookCGameTaskPhysics(int a1, CGameTask *object, int y);

	static int __fastcall hookCTaskWormHandleMessage(CTaskWorm *This, DWORD EDX, int a2, Constants::TaskMessage a3, int a4, int a5);
//	static int __fastcall hookCTaskTurnGameHandleMessage(CTaskTurnGame *This, DWORD EDX, int x, Constants::TaskMessage y, int a4, int a5);
	static int __fastcall hookDestroyGlobalContext(int This, int EDX);

	static DWORD __stdcall hookConstructDDGameWrapper(DWORD DD_Game_a2, DWORD DD_Display_a3, DWORD DS_Sound_a4, DWORD DD_Keyboard_a5, DWORD DD_Mouse_a6, DWORD WAV_CDrom_a7, DWORD WS_GameNet_a8);
public:
	static DWORD getAddrDDGame();
	static DWORD getAddrGameinfoObject();
	static DWORD getAddrTurnGameObject();
	static DWORD getAddrGameGlobal();

	static DWORD getAddrDdDisplay();
	static DWORD getAddrDsSound();
	static DWORD getAddrDdKeyboard();
	static DWORD getAddrDdMouse();
	static DWORD getAddrWavCdRom();
	static DWORD getAddrWsGameNet();

	static DWORD getAddrPCLandscape();

//	static void listAllTasks();
	static int install(SignatureScanner &, module);
//	static void spawnObject(SpawnObjectParams * params);

	static void printDebugAddrs();

//	static void triggerTaskMessage(int type, int data, int size);
};


#endif //WKJELLYWORM_GAME_H
