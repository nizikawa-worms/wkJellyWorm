
#include "Sprites.h"
#include "Hooks.h"
#include "Game.h"
#include "Utils.h"
#include "renderer/Bitmap.h"
#include "renderer/Renderer.h"
#include "renderer/BitmapExtension.h"
#include "WaLibc.h"
#include "Config.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>

void Sprites::onConstructGlobalContext(int a1) {
	if(!customSprites.empty()) {
		hookingVfs = true;
		auto addrDD_Display = Game::getAddrDdDisplay();
		auto addrPC_FileArchive = *(DWORD*)(Game::getAddrDDGame() + 0x4C0);
		int id = customSpriteStartingId;
		for(auto & it : customSprites) {
			hookingFilename = it;
			printf("loading custom sprite: %s = %d\n", it.c_str(), id);
			hookLoadSprite(addrDD_Display, 0, 1, id, 0, addrPC_FileArchive, it.c_str());
			id++;
		}
		hookingVfs = false;
	}
}

int Sprites::registerCustomSprite(std::string filename) {
	customSprites.push_back(filename);
	return customSpriteStartingId + customSprites.size() - 1;
}

void Sprites::resetConfig() {
	customSprites.clear();
}

int (__fastcall *origLoadSprite)(DWORD DD_Display, int EDX, int palette, int id, int a4, int a5, const char *filename);
int __fastcall Sprites::hookLoadSprite(DWORD DD_Display, int EDX, int palette, int id, int a4, int a5, const char *filename) {
	int ret = origLoadSprite(DD_Display, EDX, palette, id, a4, a5, filename);
//	printf("loadSprite: %s = %d  (%X), palette: %d a4: %X a5: %X\n", filename, id, ret, palette, a4, a5);
	return ret;
}



//signed int __userpurge process_sprite_sub_4FA7E0@<eax>(int a1@<eax>, int palette_a2@<ecx>, int a3)
DWORD origProcessSprite;
DWORD __stdcall hookProcessSprite(int a3) {
	DWORD retv;
	Sprites * sprite;
	GamePalette * palette;
	_asm mov sprite, eax
	_asm mov palette, ecx

	_asm push a3
	_asm mov ecx, palette
	_asm mov eax, sprite
	_asm call origProcessSprite
	_asm mov retv, eax

	if(Config::rendererEnabled) {
		BitmapExtension::convertSprite(sprite, palette);
	}

	return retv;
}

//DWORD addrLoadSprite_ProcessSprite;
DWORD origLoadSprite_OpenVfsReader;
DWORD __stdcall Sprites::hookLoadSprite_OpenVfsReader(int a3, int a4) {
	int seax, secx, retv; //filename, PC_Filearchive
	_asm mov seax, eax
	_asm mov secx, ecx

	if(!hookingVfs) {
		_asm mov eax, seax
		_asm mov ecx, secx
		_asm push a4
		_asm push a3
		_asm call origLoadSprite_OpenVfsReader
		_asm mov retv, eax
	} else {
		void * data = Utils::readFileToWaBuffer(hookingFilename);
		*(void **)(a3 + 108) = data;
 		_asm push data
		_asm mov eax, a3
		_asm mov ecx, a4
		_asm call hookProcessSprite
		_asm mov retv, eax
	}
	return retv;
}


DWORD origDrawSpriteGlobal;
void Sprites::callDrawSpriteGlobal(int posy, int layer, int posx, int sprite, int frame) {
	DWORD gamescene = *(DWORD*)(Game::getAddrGameGlobal() + 0x524);
	_asm push frame
	_asm push sprite
	_asm push posx
	_asm push layer
	_asm mov ecx, gamescene
	_asm mov eax, posy
	_asm call origDrawSpriteGlobal
}

DWORD origDrawSpriteLocal;
void Sprites::callDrawSpriteLocal(int posy, int layer, int posx, int sprite, int frame) {
	DWORD gamescene = *(DWORD*)(Game::getAddrGameGlobal() + 0x524);
	_asm push frame
	_asm push sprite
	_asm push posx
	_asm push layer
	_asm mov ecx, gamescene
	_asm mov eax, posy
	_asm call origDrawSpriteLocal
}


DWORD (__fastcall *origDestroySprite)(Sprites* sprite, int a2);
DWORD __fastcall hookDestroySprite(Sprites* sprite, int a2) {
	if(Config::rendererEnabled) {
		BitmapExtension::onDestroySprite(sprite);
	}
	return origDestroySprite(sprite, a2);
}

int Sprites::install(SignatureScanner &, module) {
	DWORD addrLoadSprite = Hooks::scanPattern("LoadSprite", "\x55\x8B\x6C\x24\x0C\xF7\xC5\x00\x00\x00\x00\x56\x8B\xF1\x74\x0A\x5E\xB8\x00\x00\x00\x00\x5D\xC2\x14\x00\x53\x8B\x5C\x24\x10\x8D\x43\xFF\x83\xF8\x02\x0F\x87\x00\x00\x00\x00\x83\xBC\x9E\x00\x00\x00\x00\x00", "??????x????xxxxxxx????xxxxxxxxxxxxxxxxx????xxx?????", 0x523400);
	DWORD addrLoadSprite_OpenVfsReader = Hooks::scanPattern("LoadSprite_OpenVfsReader", "\x55\x8B\x6C\x24\x08\x56\x57\x8B\xF1\x56\x8B\xF8\xE8\x00\x00\x00\x00\x85\xC0\x74\x11\x8B\x16\x8B\x40\x04\x8B\x52\x08\x50\x8B\xCE\xFF\xD2\x85\xC0\x75\x57", "??????xxxxxxx????xxxxxxxxxxxxxxxxxxxxx", 0x4FAAF0);
	origDrawSpriteGlobal = Hooks::scanPattern("DrawSpriteGlobal", "\x8B\x91\x00\x00\x00\x00\x81\xFA\x00\x00\x00\x00\x56\x57\x8B\x7C\x24\x10\x8B\xF0\x7D\x5B\x8B\x01\x83\xC0\xE8\x78\x54\x89\x01\x8D\x44\x08\x04\x89\x84\x91\x00\x00\x00\x00\x8B\x91\x00\x00\x00\x00", "??????xx????xxxxxxxxxxxxxxxxxxxxxxxxxx????xx????", 0x541FE0);
	origDrawSpriteLocal = origDrawSpriteGlobal + (0x541BA0 - 0x541B20);

	DWORD addrProcessSprite = Hooks::scanPattern("ProcessSprite", "\x51\x8B\x54\x24\x08\x53\x55\x8B\x2D\x00\x00\x00\x00\x56\x8D\x72\x04\x83\xC6\x04\x57\x8B\xF8\x8B\x46\xFC\x01\x05\x00\x00\x00\x00\x89\x77\x60\x0F\xB7\x1E\x83\xC6\x02\x89\x77\x68\x66\x89\x5F\x14", "??????xxx????xxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxx", 0x4FAB80);

	DWORD addrConstructSprite = Hooks::scanPattern("ConstructSprite", "\x89\x48\x04\x33\xC9\xC7\x00\x00\x00\x00\x00\xC7\x40\x00\x00\x00\x00\x00\x89\x48\x48\x89\x48\x4C\x89\x48\x44\x89\x48\x3C\x89\x48\x50\x89\x48\x54\x89\x48\x58\x89\x48\x5C\xC7\x40\x00\x00\x00\x00\x00", "??????x????xx?????xxxxxxxxxxxxxxxxxxxxxxxxxx?????", 0x4FAA30);
	DWORD *addrSpriteVTable = *(DWORD**)(addrConstructSprite + 0x7);
	DWORD addrDestroySprite = addrSpriteVTable[0];

	Hooks::minhook("LoadSprite", addrLoadSprite, (DWORD*)&hookLoadSprite, (DWORD*)&origLoadSprite);
	Hooks::minhook("ProcessSprite", addrProcessSprite, (DWORD*)&hookProcessSprite, (DWORD*)&origProcessSprite);
	Hooks::minhook("DestroySprite", addrDestroySprite, (DWORD*)&hookDestroySprite, (DWORD*)&origDestroySprite);
	Hooks::minhook("LoadSprite_OpenVfsReader", addrLoadSprite_OpenVfsReader, (DWORD*)&hookLoadSprite_OpenVfsReader, (DWORD*)&origLoadSprite_OpenVfsReader);

	auto * lua = Lua::getInstance().getState();
	lua->set_function("registerCustomSprite", &registerCustomSprite);
	lua->set_function("drawSpriteLocal", &callDrawSpriteLocal);
	lua->set_function("drawSpriteGlobal", &callDrawSpriteGlobal);
	return 0;
}