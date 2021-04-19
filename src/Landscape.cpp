#include <MinHook.h>
#include "Landscape.h"
#include "src/entities/Entities.h"
#include "Game.h"
#include "Hooks.h"

#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/packages/PackageManager.h>

int Landscape::onConstructGlobalContext(int a1) {
//	CTask * turngame = (CTask*)Game::getAddrTurnGameObject();
//
//	for(auto child : turngame->children) {
//		if(child->classtype == Constants::ClassType::ClassType_Task_Land) {
//			addrCTaskLandObject = (DWORD)child;
//			break;
//		}
//	}
//
//	if(!addrCTaskLandObject) throw std::runtime_error("Failed to find CTaskLandObject");
	return 0;
}

int (__stdcall *origRedrawLandRegion)(int startX, int startY, int endX, int endY);
int __stdcall hookRedrawLandRegion(int startX, int startY, int endX, int endY) {
	int seax, retv;
	_asm mov seax, eax

	_asm push endY
	_asm push endX
	_asm push startY
	_asm push startX
	_asm mov eax, seax
	_asm call origRedrawLandRegion
	_asm mov retv, eax

	return retv;
}

int (__fastcall *origWriteLandMaskID)(DWORD This, int EDX, int a2, int a3, int a4);
int __fastcall hookWriteLandMaskID(DWORD This, int EDX, int maskid, int posX, int posY) {
//	printf("writeLandMaskID: %X maskid: %d posX: %d posY: %d\n", This, maskid, posX, posY);
	int ret = PackageManager::getInstance().handleWriteLandMaskID(This, maskid, posX, posY);
	if(ret) return ret;
	return origWriteLandMaskID(This, EDX, maskid, posX, posY);
}

int Landscape::callWriteLandMaskID(int maskid, int posX, int posY) {
	DWORD addrPCLandscape = Game::getAddrPCLandscape();
	return hookWriteLandMaskID(addrPCLandscape, 0, maskid, posX, posY);
}


void (__fastcall *origWriteLandRadius)(DWORD This, int EDX, int radius, int posX, int posY);
void __fastcall hookWriteLandRadius(DWORD This, int EDX, int radius, int posX, int posY) {
//	printf("writeLandRadius: radius: %d posx: %d posy: %d\n", radius, posX, posY);
	int ret = PackageManager::getInstance().handleWriteLandRadius(This, radius, posX, posY);
	if(ret) return;
	return origWriteLandRadius(This, EDX, radius, posX, posY);
}

void Landscape::callWriteLandRadius(int radius, int posX, int posY) {
	DWORD addrPCLandscape = Game::getAddrPCLandscape();
	hookWriteLandRadius(addrPCLandscape, 0, radius, posX, posY);
}

DWORD origWriteLandRaw;
int __stdcall hookWriteLandRaw(int posX, int posY, int layer) {
	int bitmap, land, retv;
	_asm mov bitmap, ecx
	_asm mov land, edi

	int ret = PackageManager::getInstance().handleWriteLandRaw(bitmap, land, posX, posY, layer);
	if(ret) return ret;

//	DWORD addrPCLandscape = *(DWORD*)(Game::getAddrDDGame() + 0x4CC);
//	printf("writeLandRaw: PCLandscape: %X bitmap: %X land: %X posX: %d posY: %d layer: %d\n", addrPCLandscape, bitmap, land, posX, posY, layer);
	_asm mov ecx, bitmap
	_asm mov edi, land
	_asm push layer
	_asm push posY
	_asm push posX
	_asm call origWriteLandRaw
	_asm mov retv, eax

	return retv;
}

int Landscape::callWriteLandRaw(DWORD bitmap, int posX, int posY, int layer) {
	DWORD addrPCLandscape = Game::getAddrPCLandscape();
	int retv;
	_asm mov ecx, bitmap
	_asm mov edi, addrPCLandscape
	_asm push layer
	_asm push posY
	_asm push posX
	_asm call hookWriteLandRaw
	_asm mov retv, eax
	return retv;
}


int Landscape::install(SignatureScanner & signatureScanner, module mod) {
	DWORD addrConstructPCLandscape = Hooks::scanPattern("ConstructPC_Landscape", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\x8B\x84\x24\x00\x00\x00\x00\x53\x55\x8B\xAC\x24\x00\x00\x00\x00\x56\x8B\xB4\x24\x00\x00\x00\x00\x57\x89\x45\x04", "???????xx????xxxx????xx????xxx????xxxxx????xxxx????xxxx", 0x57ACB0);
	DWORD addrPCLandscape_vtable = *(DWORD*)(addrConstructPCLandscape + 0x4C);
	DWORD addrWriteLandRadius = *(DWORD*)(addrPCLandscape_vtable + 0x8); //57C1C0
	DWORD addrWriteLandMaskID = *(DWORD*)(addrPCLandscape_vtable + 0xC); //57C690
	DWORD addrRedrawLandRegion = Hooks::scanPattern("RedrawLandRegion", "\x57\x8B\xF8\x81\xBF\x00\x00\x00\x00\x00\x00\x00\x00\x7C\x05\xE8\x00\x00\x00\x00\x8B\x87\x00\x00\x00\x00\x66\x8B\x4C\x24\x00\x66\x89\x8C\xC7\x00\x00\x00\x00\x8B\x97\x00\x00\x00\x00\x66\x8B\x44\x24\x00\x66\x89\x84\xD7\x00\x00\x00\x00\x8B\x8F\x00\x00\x00\x00\x66\x8B\x54\x24\x00", "?????????????xxx????xx????xxxx?xxxx????xx????xxxx?xxxx????xx????xxxx?", 0x57CC10);
	DWORD addrWriteLandRaw = Hooks::scanPattern("WriteLandRaw", "\x83\xEC\x68\x8B\x87\x00\x00\x00\x00\x8B\x50\x08\x8B\x40\x10\x53\x55\x8B\x6C\x24\x74\x89\x44\x24\x74\x8B\x41\x14\x56\x8B\x71\x18\x89\x44\x24\x48\x83\xC0\x07\xC1\xF8\x03\x8B\xDD\x83\xC0\x03\x83\xE0\xFC\x83\xE3\x1F", "?????????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", 0x57C300);

	Hooks::minhook("RedrawLandRegion", addrRedrawLandRegion, (DWORD*)&hookRedrawLandRegion, (DWORD*)&origRedrawLandRegion);
	Hooks::minhook("WriteLandRadius", addrWriteLandRadius, (DWORD*) &hookWriteLandRadius, (DWORD*)&origWriteLandRadius);
	Hooks::minhook("WriteLandMaskID", addrWriteLandMaskID, (DWORD*) &hookWriteLandMaskID, (DWORD*)&origWriteLandMaskID);
	Hooks::minhook("WriteLandRaw", addrWriteLandRaw, (DWORD*) &hookWriteLandRaw, (DWORD*)&origWriteLandRaw);

	auto * lua = Lua::getInstance().getState();
	lua->set_function("writeLandRadius", &callWriteLandRadius);
	lua->set_function("writeLandMaskID", &callWriteLandMaskID);
	lua->set_function("writeLandRaw", &callWriteLandRaw);
	return 0;
}
