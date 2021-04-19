
#ifndef WKJELLYWORM_DRAWING_H
#define WKJELLYWORM_DRAWING_H


#include <sigscanner.h>
#include "Bitmap.h"
#include "Renderer.h"

class Drawing {
private:
	static DWORD __fastcall hookDrawLandscape(int a1, DWORD *a2, Renderer::BitmapDescriptor * Src, int posX, int posY, int offsetX, int offsetY, int width, int height, int flag);
	static int __stdcall hookDrawBitmapOnBitmap(int posX, int posY, int width, int height, Bitmap::BitmapImage *Src, int srcOffsetX, int srcOffsetY, int a9, int flags);

	static inline const std::string indexedFragmentShaderSource =
#include "shaders/indexedFragmentShader.fs"
	;
	static inline const std::string vertexShaderSource =
#include "shaders/vertexShader.vs"
	;

	static inline const std::string paletteFragmentShaderSource =
#include "shaders/paletteFragmentShader.fs"
	;

	static void compileShaders();
	static inline GLint indexedShaderProgram, paletteShaderProgram;
	static inline GLint indexed_TextureSamplerLocation;
	static inline GLint palette_IndexedTextureSamplerLocation, palette_PaletteTextureSamplerLocation, palette_TransparentFlagLocation;
	static inline GLuint palette_texture = 0;
	static inline GLuint palette_PaletteTextureSampler = 0;

	static DWORD __fastcall hookRedrawFrontendBitmap(Renderer::BitmapDescriptor * a1, DWORD a2, int a3, int a4, Renderer::BitmapDescriptor *  a5, int a6, int a7, int a8, int a9, int a10);
	static DWORD __fastcall Drawing::hookSwitchScreenPalette(DWORD This, int EDX, DWORD palette, int commit);

	static void genPaletteTexture(DWORD palette);
public:
	static void callDrawBitmapOnBitmap(Bitmap::BitmapImage * Dst, int posX, int posY, int width, int height, Bitmap::BitmapImage *Src, int srcOffsetX, int srcOffsetY, int a9, int flags);
	static int install(SignatureScanner &, module);

	friend class Renderer;
};


#endif //WKJELLYWORM_DRAWING_H
