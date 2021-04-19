
#ifndef WKJELLYWORM_PALETTE_H
#define WKJELLYWORM_PALETTE_H

#include <sigscanner.h>

struct PaletteRGBColor {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char unknown; // alpha?
	DWORD toRGBA() const {return 0xFF000000 | (b << 16) | (g << 8) | r;}
	DWORD toRGBA2() const {return 0xFF000000 | (b << 16) | (g << 8) | r;}
};


class GamePalette {
public:
	WORD unknown0;
	WORD max_color_word2;
	PaletteRGBColor colors[256];
	// todo: fill to 0x70c
};

class ScreenPalette {
public:
	PaletteRGBColor colors[256];
};

#endif //WKJELLYWORM_PALETTE_H
