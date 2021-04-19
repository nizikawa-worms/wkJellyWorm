#ifndef WKJELLYWORM_LANDSCAPE_H
#define WKJELLYWORM_LANDSCAPE_H


#include <sigscanner.h>

class Landscape {
private:

public:
	static int onConstructGlobalContext(int a1);

	static int install(SignatureScanner &, module);

	static int callWriteLandMaskID(int maskid, int posX, int posY);
	static void callWriteLandRadius(int radius, int posX, int posY);
	static int callWriteLandRaw(DWORD bitmap, int posX, int posY, int layer);
};


#endif //WKJELLYWORM_LANDSCAPE_H
