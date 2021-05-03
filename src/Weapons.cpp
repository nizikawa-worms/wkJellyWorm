#include "Weapons.h"
#include "entities/Entities.h"
#include "Game.h"
#include "Hooks.h"
#include "CustomWeapons.h"

#include "Lua.h"
#include <sol/sol.hpp>
#include "packages/PackageManager.h"
#include "entities/gametasks/CTaskMissile.h"



DWORD origWeaponRelease;
int __stdcall hookWeaponRelease(int posX, int posY, int angleX, int angleY) {
	int retv;
	CGameTask * This;
	_asm mov This, eax

//	float FangleX = (float)angleX / (float) 0xFFFF;
//	float FangleY = (float)angleY / (float) 0xFFFF;
//	printf("OnWeaponRelease: a1: %X posX: %d posY: %d angleX: %f angleY: %f\n", (int)This + 0x258, posX / 0xFFFF, posY / 0xFFFF, FangleX, FangleY);
	int ret = PackageManager::getInstance().handleWeaponRelease(This, posX, posY, angleX, angleY);
	if(ret) return ret;

	_asm mov eax, This
	_asm push angleY
	_asm push angleX
	_asm push posY
	_asm push posX
	_asm call origWeaponRelease
	_asm mov retv, eax

	return retv;
}


DWORD origWormStartFiringWeapon;
DWORD __stdcall hookWormStartFiringWeapon() {
	DWORD retv;
	CTaskWorm * worm;
	_asm mov worm, eax

	int ret = PackageManager::getInstance().handleWormStartFiringWeapon(worm);
	if(ret) return ret;

	_asm mov eax, worm
	_asm call origWormStartFiringWeapon
	_asm mov retv, eax

	return retv;
}


DWORD origFireWeapon;
int __stdcall Weapons::hookFireWeapon(CTaskWorm *worm) {
	CustomWeapons::WeaponStruct *weaponstruct;
	WeaponLaunchParams * launchparams;
	int retv;
	_asm mov weaponstruct, eax
	_asm mov launchparams, ecx

	int ret = PackageManager::getInstance().handleFireWeapon(worm, weaponstruct, launchparams);
	if(ret) return ret;

	_asm mov eax, weaponstruct
	_asm mov ecx, launchparams
	_asm push worm
	_asm call origFireWeapon
	_asm mov retv, eax

	return retv;
}

CTaskMissile *(__fastcall *origCreateWeaponProjectile)(CGameTask *This, int EDX, Weapons::WeaponProjectileParams * projectileParams, Weapons::WeaponLaunchParams * weaponLaunchParams);
CTaskMissile *__fastcall Weapons::hookCreateWeaponProjectile(CGameTask *This, int EDX, WeaponProjectileParams * projectileParams, WeaponLaunchParams * launchParams) {
	int ret = PackageManager::getInstance().handleCreateWeaponProjectile(This, projectileParams, launchParams);
	if(ret) return 0;
	return origCreateWeaponProjectile(This, EDX, projectileParams, launchParams);
}

CTaskMissile* Weapons::callCreateWeaponProjectile(CGameTask * This, WeaponProjectileParams * projectileParams, WeaponLaunchParams * launchParams) {
	return hookCreateWeaponProjectile(This, 0, projectileParams, launchParams);
}

int Weapons::install(SignatureScanner &, module) {
	DWORD addrWeaponRelease = Hooks::scanPattern("WeaponRelease", "\x81\xEC\x00\x00\x00\x00\x53\x8B\x9C\x24\x00\x00\x00\x00\x55\x8B\xAC\x24\x00\x00\x00\x00\x56\x57\x6A\x2C\x8B\xF8\x33\xF6\x8D\x44\x24\x18\x56\x50\xE8\x00\x00\x00\x00\x8B\x8F\x00\x00\x00\x00\x83\xC4\x0C", "??????xxxx????xxxx????xxxxxxxxxxxxxxx????xx????xxx", 0x51C3D0);
	DWORD addrWormStartFiringWeapon = Hooks::scanPattern("WormStartFiringWeapon", "\x81\xEC\x00\x00\x00\x00\x53\x55\x56\x8B\xF0\x8B\x46\x44\x57\x8B\xBE\x00\x00\x00\x00\x33\xDB\x83\xE8\x6E", "??????xxxxxxxxxxx????xxxxx", 0x51B7F0);
	DWORD addrFireWeapon = Hooks::scanPattern("FireWeapon", "\x56\x8B\x74\x24\x08\xC7\x46\x00\x00\x00\x00\x00\x8B\x50\x30\x83\xC2\xFF\x83\xFA\x03\x57\x0F\x87\x00\x00\x00\x00\xFF\x24\x95\x00\x00\x00\x00\x8B\x50\x38\x83\xC2\xFF\x83\xFA\x03", "??????x?????xxxxxxxxxxxx????xxx????xxxxxxxxx", 0x51EE60);
	DWORD addrCreateWeaponProjectile = Hooks::scanPattern("CreateWeaponProjectile", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x51\x56\x8B\xF1\x8B\x46\x2C\x8B\x88\x00\x00\x00\x00\x83\xC1\x07\x81\xF9\x00\x00\x00\x00\x57\x7E\x3C", "???????xx????xxxx????xxxxxxxxx????xxxxx????xxx", 0x51E0F0);

	Hooks::polyhook("WeaponRelease", addrWeaponRelease, (DWORD *) &hookWeaponRelease, (DWORD *) &origWeaponRelease);
	Hooks::polyhook("WormStartFiring", addrWormStartFiringWeapon, (DWORD *) &hookWormStartFiringWeapon, (DWORD *) &origWormStartFiringWeapon);
	Hooks::polyhook("FireWeapon", addrFireWeapon, (DWORD *) &hookFireWeapon, (DWORD *) &origFireWeapon);
	Hooks::polyhook("CreateWeaponProjectile", addrCreateWeaponProjectile, (DWORD *) &hookCreateWeaponProjectile, (DWORD *) &origCreateWeaponProjectile);


	auto * lua = Lua::getInstance().getState();
	lua->set_function("createWeaponProjectile", &callCreateWeaponProjectile);

	sol::usertype <WeaponLaunchParams> ut = lua->new_usertype <WeaponLaunchParams> ("WeaponLaunchParams");
	ut["unknown0"] = &WeaponLaunchParams::unknown0;
	ut["unknown4"] = &WeaponLaunchParams::unknown4;
	ut["unknown8"] = &WeaponLaunchParams::unknown8;
	ut["unknownC"] = &WeaponLaunchParams::unknownC;
	ut["unknown10"] = &WeaponLaunchParams::unknown10;
	ut["unknown14"] = &WeaponLaunchParams::unknown14;
	ut["unknown18"] = &WeaponLaunchParams::unknown18;
	ut["unknown1C"] = &WeaponLaunchParams::unknown1C;
	ut["unknown20"] = &WeaponLaunchParams::unknown20;
	ut["unknown24"] = &WeaponLaunchParams::unknown24;
	ut["unknown28"] = &WeaponLaunchParams::unknown28;


	sol::usertype <WeaponProjectileParams> ut2 = lua->new_usertype <WeaponProjectileParams> ("WeaponProjectileParams");
	ut2["unknown0"] = &WeaponProjectileParams::unknown0;
	ut2["unknown4"] = &WeaponProjectileParams::unknown4;
	ut2["unknown8"] = &WeaponProjectileParams::unknown8;
	ut2["unknownC"] = &WeaponProjectileParams::unknownC;
	ut2["unknown10"] = &WeaponProjectileParams::unknown10;
	ut2["unknown14"] = &WeaponProjectileParams::unknown14;
	ut2["unknown18"] = &WeaponProjectileParams::unknown18;
	ut2["unknown1C"] = &WeaponProjectileParams::unknown1C;
	ut2["unknown20"] = &WeaponProjectileParams::unknown20;
	ut2["unknown24"] = &WeaponProjectileParams::unknown24;
	ut2["unknown28"] = &WeaponProjectileParams::unknown28;
	ut2["unknown2C"] = &WeaponProjectileParams::unknown2C;
	ut2["unknown30"] = &WeaponProjectileParams::unknown30;
	ut2["unknown34"] = &WeaponProjectileParams::unknown34;
	ut2["unknown38"] = &WeaponProjectileParams::unknown38;
	ut2["unknown3C"] = &WeaponProjectileParams::unknown3C;
	ut2["unknown40"] = &WeaponProjectileParams::unknown40;
	ut2["unknown44"] = &WeaponProjectileParams::unknown44;
	ut2["unknown48"] = &WeaponProjectileParams::unknown48;
	ut2["unknown4C"] = &WeaponProjectileParams::unknown4C;
	ut2["unknown50"] = &WeaponProjectileParams::unknown50;
	ut2["unknown54"] = &WeaponProjectileParams::unknown54;
	ut2["unknown58"] = &WeaponProjectileParams::unknown58;
	ut2["unknown5C"] = &WeaponProjectileParams::unknown5C;
	ut2["unknown60"] = &WeaponProjectileParams::unknown60;
	ut2["unknown64"] = &WeaponProjectileParams::unknown64;
	ut2["unknown68"] = &WeaponProjectileParams::unknown68;
	ut2["unknown6C"] = &WeaponProjectileParams::unknown6C;
	ut2["unknown70"] = &WeaponProjectileParams::unknown70;
	ut2["unknown74"] = &WeaponProjectileParams::unknown74;
	ut2["unknown78"] = &WeaponProjectileParams::unknown78;
	ut2["unknown7C"] = &WeaponProjectileParams::unknown7C;
	ut2["unknown80"] = &WeaponProjectileParams::unknown80;
	ut2["unknown84"] = &WeaponProjectileParams::unknown84;
	ut2["unknown88"] = &WeaponProjectileParams::unknown88;
	ut2["unknown8C"] = &WeaponProjectileParams::unknown8C;
	ut2["unknown90"] = &WeaponProjectileParams::unknown90;
	ut2["unknown94"] = &WeaponProjectileParams::unknown94;
	ut2["unknown98"] = &WeaponProjectileParams::unknown98;
	ut2["unknown9C"] = &WeaponProjectileParams::unknown9C;
	ut2["unknownA0"] = &WeaponProjectileParams::unknownA0;
	ut2["unknownA4"] = &WeaponProjectileParams::unknownA4;
	ut2["unknownA8"] = &WeaponProjectileParams::unknownA8;
	ut2["unknownAC"] = &WeaponProjectileParams::unknownAC;
	ut2["unknownB0"] = &WeaponProjectileParams::unknownB0;
	ut2["unknownB4"] = &WeaponProjectileParams::unknownB4;
	ut2["unknownB8"] = &WeaponProjectileParams::unknownB8;
	ut2["unknownBC"] = &WeaponProjectileParams::unknownBC;
	ut2["unknownC0"] = &WeaponProjectileParams::unknownC0;
	ut2["unknownC4"] = &WeaponProjectileParams::unknownC4;
	ut2["unknownC8"] = &WeaponProjectileParams::unknownC8;
	ut2["unknownCC"] = &WeaponProjectileParams::unknownCC;
	ut2["unknownD0"] = &WeaponProjectileParams::unknownD0;
	ut2["unknownD4"] = &WeaponProjectileParams::unknownD4;
	ut2["unknownD8"] = &WeaponProjectileParams::unknownD8;
	ut2["unknownDC"] = &WeaponProjectileParams::unknownDC;
	ut2["unknownE0"] = &WeaponProjectileParams::unknownE0;
	ut2["unknownE4"] = &WeaponProjectileParams::unknownE4;
	ut2["unknownE8"] = &WeaponProjectileParams::unknownE8;
	ut2["unknownEC"] = &WeaponProjectileParams::unknownEC;
	ut2["unknownF0"] = &WeaponProjectileParams::unknownF0;
	ut2["unknownF4"] = &WeaponProjectileParams::unknownF4;
	ut2["unknownF8"] = &WeaponProjectileParams::unknownF8;
	ut2["unknownFC"] = &WeaponProjectileParams::unknownFC;
	ut2["unknown100"] = &WeaponProjectileParams::unknown100;
	ut2["unknown104"] = &WeaponProjectileParams::unknown104;
	ut2["unknown108"] = &WeaponProjectileParams::unknown108;
	ut2["unknown10C"] = &WeaponProjectileParams::unknown10C;
	ut2["unknown110"] = &WeaponProjectileParams::unknown110;
	ut2["unknown114"] = &WeaponProjectileParams::unknown114;
	ut2["unknown118"] = &WeaponProjectileParams::unknown118;
	ut2["unknown11C"] = &WeaponProjectileParams::unknown11C;
	ut2["unknown120"] = &WeaponProjectileParams::unknown120;
	ut2["unknown124"] = &WeaponProjectileParams::unknown124;
	ut2["unknown128"] = &WeaponProjectileParams::unknown128;
	ut2["unknown12C"] = &WeaponProjectileParams::unknown12C;
	ut2["unknown130"] = &WeaponProjectileParams::unknown130;
	ut2["unknown134"] = &WeaponProjectileParams::unknown134;
	ut2["unknown138"] = &WeaponProjectileParams::unknown138;
	ut2["unknown13C"] = &WeaponProjectileParams::unknown13C;
	ut2["unknown140"] = &WeaponProjectileParams::unknown140;
	ut2["unknown144"] = &WeaponProjectileParams::unknown144;
	ut2["unknown148"] = &WeaponProjectileParams::unknown148;
	ut2["unknown14C"] = &WeaponProjectileParams::unknown14C;
	ut2["unknown150"] = &WeaponProjectileParams::unknown150;
	ut2["unknown154"] = &WeaponProjectileParams::unknown154;
	ut2["unknown158"] = &WeaponProjectileParams::unknown158;
	ut2["unknown15C"] = &WeaponProjectileParams::unknown15C;
	ut2["unknown160"] = &WeaponProjectileParams::unknown160;
	ut2["unknown164"] = &WeaponProjectileParams::unknown164;
	ut2["unknown168"] = &WeaponProjectileParams::unknown168;
	ut2["unknown16C"] = &WeaponProjectileParams::unknown16C;
	ut2["unknown170"] = &WeaponProjectileParams::unknown170;
	ut2["unknown174"] = &WeaponProjectileParams::unknown174;

	return 0;
}
