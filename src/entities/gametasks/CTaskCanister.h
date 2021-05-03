
#ifndef WKJELLYWORM_CTASKCANISTER_H
#define WKJELLYWORM_CTASKCANISTER_H


#include "../CGameTask.h"

class CTaskCanister : public CGameTask {
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

	static int install(SignatureScanner & signatureScanner, module mod);
};



#endif //WKJELLYWORM_CTASKCANISTER_H
