#include <MinHook.h>
#include "Chat.h"
#include "Game.h"
#include "CustomWeapons.h"
#include "Hooks.h"
#include "Lua.h"
#include <sol/sol.hpp>
#include "packages/PackageManager.h"
#include "renderer/Renderer.h"

void (__stdcall *addrShowChatMessage)(DWORD addrResourceObject, int color, char * msg, int unk);
void Chat::callShowChatMessage(std::string msg, int color) {
	if (!Game::getAddrDDGame()) return;
	addrShowChatMessage(Game::getAddrDDGame(), color, (char*)msg.c_str(), 1);
}

DWORD origOnChatInput = 0;
int __stdcall callOriginalOnChatInput(int a1, char * msg, int a3) {
	_asm mov ecx, a1
	_asm mov eax, msg
	_asm push a3
	_asm call origOnChatInput
}

int Chat::onChatInput(int a1, char * msg, int a3) {
	size_t len = strlen(msg);
	if(!strcmp(msg, "/test")) {
		callShowChatMessage("wkJellyWorm test", 6);
		return 1;
	}
//	if(!strcmp(msg, "/vt")) {
//		Game::listAllTasks();
//		return 1;
//	}
	if(!strcmp(msg, "/arma")) {
		CTaskTurnGame::triggerArmageddon(100, 166);
		return 1;
	}
	if(!strcmp(msg, "/quake")) {
		CTaskTurnGame::triggerQuake(10);
		return 1;
	}
//	if(!strcmp(msg, "/spawn")) {
//		SpawnObjectParams params = {0};
//		params.type = SpawnObjectParams::Mine;
//		Game::spawnObject(&params);
//		return 1;
//	}
	if(!strcmp(msg, "/weapons")) {
		CustomWeapons::printDebugAddrs();
		return 1;
	}
//	if(!strcmp(msg, "/table")) {
//		CustomWeapons::switchWeaponTable();
//		return 1;
//	}
	if(!strcmp(msg, "/exception")) {
		throw std::runtime_error("Test exception");
	}
	if(!strcmp(msg, "/crash")) {
		*(DWORD*)0 += 1;
	}
	if(!strcmp(msg, "/drawing")) {
		printf("toggling native renderer");
		Renderer::toggleNativeDrawing();
		return 1;
	}

	if(PackageManager::getInstance().handleOnChatInput(msg))
		return 1;
	return 0;
}

#pragma optimize( "", off )
char* onchat_eax;
int onchat_ecx;
void __stdcall Chat::hookOnChatInput(int a3) {
	_asm mov onchat_eax, eax
	_asm mov onchat_ecx, ecx
	if(!Chat::onChatInput(onchat_ecx, (char*)onchat_eax, a3)) {
		callOriginalOnChatInput(onchat_ecx, onchat_eax, a3);
	}
}
#pragma optimize( "", on )

int Chat::install(SignatureScanner & signatureScanner, module mod) {
	addrShowChatMessage =
			(void (__stdcall *)(DWORD, int, char *, int))
			Hooks::scanPattern("ShowChatMessage", "\x81\xEC\x00\x00\x00\x00\x53\x55\x8B\xAC\x24\x00\x00\x00\x00\x80\xBD\x00\x00\x00\x00\x00\x8B\x85\x00\x00\x00\x00\x8B\x48\x24\x56\x8B\xB1\x00\x00\x00\x00\x57", "??????xxxxx????xx?????xx????xxxxxx????x", 0x52ACB0);
	DWORD addrOnChatInput = Hooks::scanPattern("OnChatInput", "\x81\xEC\x00\x00\x00\x00\x55\x56\x57\x8B\xF8\x8A\x07\x84\xC0\x8B\xF1\x0F\x84\x00\x00\x00\x00\x3C\x2F\x0F\x85\x00\x00\x00\x00\x8D\x44\x24\x40", "??????xxxxxxxxxxxxx????xxxx????xxxx", 0x52B730);

	Hooks::polyhook("onChatInput", addrOnChatInput, (DWORD *) &hookOnChatInput, (DWORD *) &origOnChatInput);

	auto * lua = Lua::getInstance().getState();
	lua->set_function("showChatMessage", &callShowChatMessage);
	return 0;
}
