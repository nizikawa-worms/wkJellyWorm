#ifndef WKJELLYWORM_CTASKCPU_H
#define WKJELLYWORM_CTASKCPU_H


#include "../CTask.h"

class CTaskCPU : public CTask {
public:
	unsigned char unknown[0x345C];
	static int install(SignatureScanner & signatureScanner, module mod);
};


#endif //WKJELLYWORM_CTASKCPU_H
