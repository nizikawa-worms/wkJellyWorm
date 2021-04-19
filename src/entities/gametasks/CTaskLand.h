
#ifndef WKJELLYWORM_CTASKLAND_H
#define WKJELLYWORM_CTASKLAND_H

#include "src/entities/CGameTask.h"

class CTaskLand : public CGameTask {
public:
	int unknownF0; // 0xF0
	int unknownF4; // 0xF4
	int unknownF8; // 0xF8
	int unknownFC; // 0xFC
	int unknown100; // 0x100
	int unknown104; // 0x104
	int unknown108; // 0x108

	static int install(SignatureScanner & signatureScanner, module mod);
};



#endif //WKJELLYWORM_CTASKLAND_H
