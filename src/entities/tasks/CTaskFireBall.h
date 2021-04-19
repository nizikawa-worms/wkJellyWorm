
#ifndef WKJELLYWORM_CTASKFIREBALL_H
#define WKJELLYWORM_CTASKFIREBALL_H

#include <src/entities/CTask.h>

class CTaskFireBall : public CTask {
public:
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

	static int install(SignatureScanner & signatureScanner, module mod);
};


#endif //WKJELLYWORM_CTASKFIREBALL_H
