#include "Explosions.h"
#include "Hooks.h"
#include "Game.h"
#include "Utils.h"

#include "Lua.h"
#include <sol/sol.hpp>
#include "packages/PackageManager.h"

DWORD origCreateExplosion;
int __stdcall Explosions::hookCreateExplosion(int pushForce, int power, int a6, int team) {
	int posx_a1, posy_a2, sender_a3, retv;
	_asm mov posx_a1, eax
	_asm mov posy_a2, ecx
	_asm mov sender_a3, esi

//	printf("CreateExplosion: pushForce: %d  power: %d a6: %d team: %d\n", pushForce, power, a6, team);
	int ret = PackageManager::getInstance().handleCreateExplosion(posx_a1, posy_a2, (CGameTask*)sender_a3, pushForce, power, a6, team);
	if(ret) return ret;

	_asm mov eax, posx_a1
	_asm mov ecx, posy_a2
	_asm mov esi, sender_a3
	_asm push team
	_asm push a6
	_asm push power
	_asm push pushForce
	_asm call origCreateExplosion
	_asm mov retv, eax

	return retv;
}

int Explosions::callCreateExplosion(CGameTask * This, int posX, int posY, int pushForce, int power, int a6, int team) {
	int retv;
	_asm push team
	_asm push a6
	_asm push power
	_asm push pushForce
	_asm mov eax, posX
	_asm mov ecx, posY
	_asm mov esi, This
	_asm call hookCreateExplosion
	_asm mov retv, eax

	return retv;
}

int (__stdcall *origSpecialImpact)(CGameTask *This, int posX, int posY, int radiusX, int radiusY, int power, int pushX, int pushY, int type_a9, Constants::SoundIds a10, int a11, int collisionMask, int a13);
int __stdcall hookSpecialImpact(CGameTask *This, int posX, int posY, int radiusX, int radiusY, int power, int pushX, int pushY, int type_a9, Constants::SoundIds soundOnHit, Constants::Sprites spriteOnHit, int collisionMask, int a13) {
//	printf("SpecialImpact: posX: %d posY: %d radiusX: %d radiusY: %d power: %d pushX: %X pushY: %X type_a9: %d soundOnHit: %d spriteOnHit: %d collisionMask: %d a13: %d\n",
//		   posX / 0xFFFF, posY / 0xFFFF, radiusX / 0xFFFF, radiusY / 0xFFFF, power, pushX, pushY, type_a9, soundOnHit, spriteOnHit, collisionMask, a13);
	int ret = PackageManager::getInstance().handleSpecialImpact(This, posX, posY, radiusX, radiusY, power, pushX, pushY, type_a9, soundOnHit, spriteOnHit, collisionMask, a13);
	if(ret) return ret;
	return origSpecialImpact(This, posX, posY, radiusX, radiusY, power, pushX, pushY, type_a9, soundOnHit, spriteOnHit, collisionMask, a13);
}


int Explosions::install(SignatureScanner &, module) {
	DWORD addrCreateExplosion = Hooks::scanPattern("CreateExplosion", "\x55\x8B\xEC\x83\xE4\xF8\x81\xEC\x00\x00\x00\x00\x8B\x55\x08\x89\x4C\x24\x08\x8B\x4D\x10\x89\x54\x24\x0C\x8B\x55\x14\x89\x4C\x24\x14\x89\x44\x24\x04\x8B\x45\x0C\x33\xC9\x89\x54\x24\x18\x56\x8D\x51\x14\xC7\x44\x24\x00\x00\x00\x00\x00\x89\x44\x24\x14\xE8\x00\x00\x00\x00\x85\xC0", "xxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx?????xxxxx????xx", 0x548080);
	DWORD addrSpecialImpact = Hooks::scanPattern("SpecialImpact", "\x81\xEC\x00\x00\x00\x00\x53\x83\xA4\x24\x00\x00\x00\x00\x00\x55\x56\x8B\xB4\x24\x00\x00\x00\x00\x8B\x46\x2C\x8B\x48\x24\x81\xC1\x00\x00\x00\x00\x89\x4C\x24\x14", "??????xxxx?????xxxxx????xxxxxxxx????xxxx", 0x5193D0);
	Hooks::polyhook("CreateExplosion", addrCreateExplosion, (DWORD *) &hookCreateExplosion, (DWORD *) &origCreateExplosion);
	Hooks::polyhook("SpecialImpact", addrSpecialImpact, (DWORD *) &hookSpecialImpact, (DWORD *) &origSpecialImpact);

	auto * lua = Lua::getInstance().getState();
	lua->set_function("createExplosion", &callCreateExplosion);
	lua->set_function("createSpecialImpact", &hookSpecialImpact);
	return 0;
}
