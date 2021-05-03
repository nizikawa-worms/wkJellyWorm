#ifndef WKJELLYWORM_EXPLOSIONS_H
#define WKJELLYWORM_EXPLOSIONS_H


#include <sigscanner.h>
#include "entities/CGameTask.h"

class Explosions {
private:
	static int __stdcall hookCreateExplosion(int pushForce, int power, int a6, int team);
public:
	static int callCreateExplosion(CGameTask * This, int posX, int posY, int pushForce, int a5, int a6, int team);
	static int install(SignatureScanner &, module);
};


#endif //WKJELLYWORM_EXPLOSIONS_H
