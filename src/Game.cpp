#include "Game.h"
#include <MinHook.h>
#include <src/packages/PackageManager.h>
#include "Config.h"
#include "src/entities/Entities.h"

#include "Chat.h"
#include "Landscape.h"
#include "CustomWeapons.h"
#include "Hooks.h"
#include "Lua.h"
#include "Sounds.h"
#include "Sprites.h"
#include "renderer/Renderer.h"


int (__stdcall *origConstructGlobalContext)(int a1);
int __stdcall Game::hookConstructGlobalContext(int a1) {
//	addrDDGame = a1;
	int ret = origConstructGlobalContext(a1);
	Config::onConstructGlobalContext(a1);
	auto pmanager = PackageManager::getInstance();
	pmanager.handleInitialize();
	pmanager.handleGameGlobalInit();
	Landscape::onConstructGlobalContext(a1);
	Sounds::onConstructGlobalContext(a1);
	Sprites::onConstructGlobalContext(a1);
	CustomWeapons::onConstructGlobalContext(a1);
	Renderer::onConstructGlobalContext(a1);


	auto addrGameGlobal = getAddrGameGlobal();
	printf("addrGradient: 0x%X\n", addrGameGlobal + 0x30);
//	*(DWORD*)(addrGameGlobal + 0x30) = *(DWORD*)(addrGameGlobal + 0x34);
//	*(DWORD*)(addrGameGlobal + 0x30) = 0; //*(DWORD*)(addrGameGlobal + 0x30);

	return ret;
}

int (__fastcall *origDestroyGlobalContext)(int This, int EDX);
int __fastcall Game::hookDestroyGlobalContext(int This, int EDX) {
	CustomWeapons::onDestroyGlobalContext();
	int ret = origDestroyGlobalContext(This, EDX);

	addrDDDisplay = addrDSSound = addrDDKeyboard = addrDDMouse = addrWavCDRom = addrWSGameNet = addrDDGame = 0;
	return ret;
}

DWORD Game::getAddrDDGame() {
	return addrDDGame;
}

DWORD Game::getAddrGameinfoObject() {
	return addrGameinfoObject;
}

DWORD origConstructDDGameWrapper;
DWORD __stdcall Game::hookConstructDDGameWrapper(DWORD DD_Game_a2, DWORD DD_Display_a3, DWORD DS_Sound_a4, DWORD DD_Keyboard_a5, DWORD DD_Mouse_a6, DWORD WAV_CDrom_a7, DWORD WS_GameNet_a8) {
	DWORD DD_W2Wrapper, retv;
	_asm mov DD_W2Wrapper, edi

	addrDDGame = DD_Game_a2;
	printf("ddgame: %X\n", addrDDGame);
	addrDDDisplay = DD_Display_a3;
	addrDSSound = DS_Sound_a4;
	addrDDKeyboard = DD_Keyboard_a5;
	addrDDMouse = DD_Mouse_a6;
	addrWavCDRom = WAV_CDrom_a7;
	addrWSGameNet = WS_GameNet_a8;

	_asm push WS_GameNet_a8
	_asm push WAV_CDrom_a7
	_asm push DD_Mouse_a6
	_asm push DD_Keyboard_a5
	_asm push DS_Sound_a4
	_asm push DD_Display_a3
	_asm push DD_Game_a2
	_asm mov edi, DD_W2Wrapper
	_asm call origConstructDDGameWrapper
	_asm mov retv, eax

	return retv;
}


int Game::install(SignatureScanner & signatureScanner, module mod) {
	DWORD addrConstructGlobalContext =  Hooks::scanPattern("ConstructGlobalContext", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x24\x53\x55\x8B\x6C\x24\x3C\x8B\x85\x00\x00\x00\x00\x8B\x48\x24", "???????xx????xxxx????xxxxxxxxxxx????xxx", 0x526500);
	DWORD addrDestroyGlobalContext =  Hooks::scanPattern("DestroyGlobalContext","\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x51\x56\x8B\xF1\x89\x74\x24\x04\xC7\x06\x00\x00\x00\x00\x8B\xC6\xC7\x44\x24\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\x78\x5C\x00\x75\x07\x8B\xC6\xE8\x00\x00\x00\x00\x8B\xC6\xE8\x00\x00\x00\x00\x8B\x86\x00\x00\x00\x00\x85\xC0\x74\x09\x50\xE8\x00\x00\x00\x00\x83\xC4\x04", "???????xx????xxxx????xxxxxxxxxx????xxxxx?????x????x????xxxxxxxxx????xxx????xx????xxxxxx????xxx", 0x56DFB0);
	DWORD addrReferencesGameinfo =  Hooks::scanPattern("ReferencesGameinfo", "\x80\x3D\x00\x00\x00\x00\x00\x75\x15\x56\x8B\x35\x00\x00\x00\x00\x6A\x01\xFF\xD6\x80\x3D\x00\x00\x00\x00\x00\x74\xF3\x5E\x8B\x44\x24\x04\x50\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xC2\x04\x00", "???????xxxxx????xxxxxx?????xxxxxxxxx????x????xxx", 0x4E3B40);
	DWORD addrConstructDDGameWrapper = Hooks::scanPattern("ConstructDDGameWrapper", "\x6A\xFF\x64\xA1\x00\x00\x00\x00\x68\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x53\x8B\x5C\x24\x1C\x55\x8B\x6C\x24\x1C\x56\x8B\x74\x24\x1C\x33\xC0\x89\x86\x00\x00\x00\x00\x89\x44\x24\x14\x89\x86\x00\x00\x00\x00\x8B\xC7\xC7\x06\x00\x00\x00\x00\x89\x9E\x00\x00\x00\x00\x89\xAE\x00\x00\x00\x00\xE8\x00\x00\x00\x00", "????????x????xxxx????xxxxxxxxxxxxxxxxxxx????xxxxxx????xxxx????xx????xx????x????", 0x56DEF0);

	addrGameinfoObject =  *(DWORD*)(addrReferencesGameinfo + 0x24);

	Hooks::minhook("constructGlobalContext", addrConstructGlobalContext, (DWORD*)&hookConstructGlobalContext, (DWORD*)&origConstructGlobalContext);
	Hooks::minhook("destroyGlobalContext", addrDestroyGlobalContext, (DWORD*)&hookDestroyGlobalContext, (DWORD*)&origDestroyGlobalContext);
	Hooks::minhook("ConstructDDGameWrapper", addrConstructDDGameWrapper, (DWORD*) &hookConstructDDGameWrapper, (DWORD*)&origConstructDDGameWrapper);
	return 0;
}

DWORD Game::getAddrTurnGameObject() {
	return *(DWORD*)(addrDDGame + 0x8);
}

DWORD Game::getAddrGameGlobal() {
	return *(DWORD*)(addrDDGame + 0x488);
}

void Game::printDebugAddrs() {
}

DWORD Game::getAddrDdDisplay() {
	return addrDDDisplay;
}

DWORD Game::getAddrDsSound() {
	return addrDSSound;
}

DWORD Game::getAddrDdKeyboard() {
	return addrDDKeyboard;
}

DWORD Game::getAddrDdMouse() {
	return addrDDMouse;
}

DWORD Game::getAddrWavCdRom() {
	return addrWavCDRom;
}

DWORD Game::getAddrWsGameNet() {
	return addrWSGameNet;
}

DWORD Game::getAddrPCLandscape() {
	return *(DWORD*)(addrDDGame + 0x4CC);
}