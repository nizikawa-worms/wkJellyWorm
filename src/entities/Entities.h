#ifndef WKJELLYWORM_ENTITIES_H
#define WKJELLYWORM_ENTITIES_H


#include "CGameTask.h"


struct SpawnObjectParams {
	enum Type : int {Mine=1, Oildrum, WeaponCrate, HealthCrate, UtilityCrate, UnknownWinRound, UnknownTriggerGameText};
	Type type;
	int unk4;
	int unk8;
	int unkC;
	int unk10;
	int unk14;
	int unk18;
	int unk1C;
	int unk20;
	int unk24;
};
//
//struct SpawnMineParams {
//memcpy(&mine->dword170, params, 0x20u);
//	int ArmRadius;
//	int ArmDelay;
//	int ArmGroup;
//	int FuseTime;
//	int DamageBias;
//	int DamageBlast;
//	int DamagePoints;
//	int DamageLimit;
//};

#endif //WKJELLYWORM_ENTITIES_H
