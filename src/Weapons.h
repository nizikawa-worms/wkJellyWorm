#ifndef WKJELLYWORM_WEAPONS_H
#define WKJELLYWORM_WEAPONS_H


#include <sigscanner.h>

class CTaskWorm;
class CTaskMissile;
class CGameTask;

class Weapons {
public:
	struct WeaponLaunchParams {
		int unknown0; // 0x0
		int unknown4; // 0x4
		int unknown8; // 0x8
		int unknownC; // 0xC
		int unknown10; // 0x10
		int unknown14; // 0x14
		int unknown18; // 0x18
		int unknown1C; // 0x1C
		int unknown20; // 0x20
		int unknown24; // 0x24
		int unknown28; // 0x28
	};

	struct WeaponProjectileParams {
		int unknown0; // 0x0
		int unknown4; // 0x4
		int unknown8; // 0x8
		int unknownC; // 0xC
		int unknown10; // 0x10
		int unknown14; // 0x14
		int unknown18; // 0x18
		int unknown1C; // 0x1C
		int unknown20; // 0x20
		int unknown24; // 0x24
		int unknown28; // 0x28
		int unknown2C; // 0x2C
		int unknown30; // 0x30
		int unknown34; // 0x34
		int unknown38; // 0x38
		int unknown3C; // 0x3C
		int unknown40; // 0x40
		int unknown44; // 0x44
		int unknown48; // 0x48
		int unknown4C; // 0x4C
		int unknown50; // 0x50
		int unknown54; // 0x54
		int unknown58; // 0x58
		int unknown5C; // 0x5C
		int unknown60; // 0x60
		int unknown64; // 0x64
		int unknown68; // 0x68
		int unknown6C; // 0x6C
		int unknown70; // 0x70
		int unknown74; // 0x74
		int unknown78; // 0x78
		int unknown7C; // 0x7C
		int unknown80; // 0x80
		int unknown84; // 0x84
		int unknown88; // 0x88
		int unknown8C; // 0x8C
		int unknown90; // 0x90
		int unknown94; // 0x94
		int unknown98; // 0x98
		int unknown9C; // 0x9C
		int unknownA0; // 0xA0
		int unknownA4; // 0xA4
		int unknownA8; // 0xA8
		int unknownAC; // 0xAC
		int unknownB0; // 0xB0
		int unknownB4; // 0xB4
		int unknownB8; // 0xB8
		int unknownBC; // 0xBC
		int unknownC0; // 0xC0
		int unknownC4; // 0xC4
		int unknownC8; // 0xC8
		int unknownCC; // 0xCC
		int unknownD0; // 0xD0
		int unknownD4; // 0xD4
		int unknownD8; // 0xD8
		int unknownDC; // 0xDC
		int unknownE0; // 0xE0
		int unknownE4; // 0xE4
		int unknownE8; // 0xE8
		int unknownEC; // 0xEC
		int unknownF0; // 0xF0
		int unknownF4; // 0xF4
		int unknownF8; // 0xF8
		int unknownFC; // 0xFC
		int unknown100; // 0x100
		int unknown104; // 0x104
		int unknown108; // 0x108
		int unknown10C; // 0x10C
		int unknown110; // 0x110
		int unknown114; // 0x114
		int unknown118; // 0x118
		int unknown11C; // 0x11C
		int unknown120; // 0x120
		int unknown124; // 0x124
		int unknown128; // 0x128
		int unknown12C; // 0x12C
		int unknown130; // 0x130
		int unknown134; // 0x134
		int unknown138; // 0x138
		int unknown13C; // 0x13C
		int unknown140; // 0x140
		int unknown144; // 0x144
		int unknown148; // 0x148
		int unknown14C; // 0x14C
		int unknown150; // 0x150
		int unknown154; // 0x154
		int unknown158; // 0x158
		int unknown15C; // 0x15C
		int unknown160; // 0x160
		int unknown164; // 0x164
		int unknown168; // 0x168
		int unknown16C; // 0x16C
		int unknown170; // 0x170
		int unknown174; // 0x174
	};

private:
	static int __stdcall hookFireWeapon(CTaskWorm *worm);
	static CTaskMissile *__fastcall hookCreateWeaponProjectile(CGameTask *This, int EDX, WeaponProjectileParams * projectileParams, WeaponLaunchParams * launchParams);
public:
	static int install(SignatureScanner &, module);
	static CTaskMissile* callCreateWeaponProjectile(CGameTask *This, WeaponProjectileParams *projectileParams, WeaponLaunchParams *launchParams);
};


#endif //WKJELLYWORM_WEAPONS_H
