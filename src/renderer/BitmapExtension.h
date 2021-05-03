
#ifndef WKJELLYWORM_BITMAPEXTENSION_H
#define WKJELLYWORM_BITMAPEXTENSION_H

#include <sigscanner.h>
#include <GL/glew.h>
#include "../Sprites.h"
#include <map>
#include <unordered_map>
#include "Palette.h"

class Renderer;
class Drawing;

class ExtendedBitmap {
public:
	bool populated;
	GLuint framebuffer = 0;
	GLuint texture = 0;

	Sprites *sprite;
	std::unordered_map<DWORD, int> spriteFrames;
	int spriteMaxW, spriteMaxH;

	int bitdepth;
	int align;

	bool redraw;

	ExtendedBitmap(Bitmap::BitmapImage * bitmap, Sprites * sprite = nullptr, int align=4);
};


class BitmapExtension {
public:
	static inline std::map<Bitmap::BitmapImage*, ExtendedBitmap*> extensionMap;

	static ExtendedBitmap * constructBitmapImageExtension(Bitmap::BitmapImage * bitmap, Sprites * sprite = nullptr, int align=4);
	static unsigned char * convertBitmapImageToGLRGBA(Bitmap::BitmapImage * bitmap, GamePalette * gamePalette, ScreenPalette * screenPalette, int forceWidth = 0, int forceHeight = 0);
	static bool populateBitmapImageExtension(Bitmap::BitmapImage * bitmap, unsigned char * data, int forceWidth=0, int forceHeight=0);
	static bool paintOnBitmapImageExtension(Bitmap::BitmapImage * bitmap, unsigned char * data, int posX, int posY, int width, int height);
	static bool destroyBitmapImageExtension(Bitmap::BitmapImage * bitmap);
	static void redrawBitmapImageExtension(Bitmap::BitmapImage * bitmap);
	static void convertSprite(Sprites * sprite, GamePalette * palette);
	static void onDestroySprite(Sprites * sprite);
	static ExtendedBitmap* findBitmapExtension(Bitmap::BitmapImage* bitmap);

	friend class Renderer;
	friend class Drawing;
};

#endif //WKJELLYWORM_BITMAPEXTENSION_H
