#ifndef WKJELLYWORM_CTASKMINE_H
#define WKJELLYWORM_CTASKMINE_H


#include "src/entities/CGameTask.h"

class CTaskMine : public CGameTask {
public:
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
	int unknown178; // 0x178
	int unknown17C; // 0x17C
	int unknown180; // 0x180
	int unknown184; // 0x184
	int unknown188; // 0x188
	int unknown18C; // 0x18C
	int unknown190; // 0x190
	int unknown194; // 0x194

	static int install(SignatureScanner & signatureScanner, module mod);
};



#endif //WKJELLYWORM_CTASKMINE_H
