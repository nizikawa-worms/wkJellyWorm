
#include "../Hooks.h"
#include "../Config.h"
#include "../Game.h"
#include "../WaLibc.h"
#include "Drawing.h"
#include "Bitmap.h"
#include "Renderer.h"



DWORD (__fastcall *origDrawLandscape)(int a1, DWORD *a2, Renderer::BitmapDescriptor * Src, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
DWORD __fastcall Drawing::hookDrawLandscape(int a1, DWORD *a2, Renderer::BitmapDescriptor * Src, int posX, int posY, int offsetX, int offsetY, int width, int height, int flag) {
//	printf("drawLandscape: a1: %X a2: %X a3: %X posX: %d posY: %d a6: %d a7: %d width: %d height: %d flag: %d\n",
//		   a1, (DWORD)a2, a3, posX, posY, a6, a7, width, height, flag
//		);
	if(Config::rendererEnabled) {
		if(Src->vtable == (DWORD)Renderer::addrBitmapDescriptorVTable) {
			if(!Src->bitmap) {
				//create a fake bitmap entry so it works with the drawing func
				Src->bitmap = (Bitmap::BitmapImage*) WaLibc::waMalloc(sizeof(Bitmap::BitmapImage));
				memset(Src->bitmap, 0, sizeof(Bitmap::BitmapImage));
				Src->bitmap->max_width_dword14 = Src->width_dword4;
				Src->bitmap->max_height_dword18 = Src->height_dword8;
				Src->bitmap->current_width_dword24 = Src->width_dword4;
				Src->bitmap->current_height_dword28 = Src->height_dword8;
				Src->bitmap->rowsize_dword10 = Src->width_dword4;
				Src->bitmap->data_dword8 = Src->data_dwordC;
				Src->bitmap->bitdepth_dwordC = 8;
				*(DWORD*)Src->bitmap = Bitmap::getAddrBitmapImageVtable();

				auto extension = BitmapExtension::constructBitmapImageExtension(Src->bitmap);
				extension->align = 1;
				BitmapExtension::populateBitmapImageExtension(Src->bitmap, (unsigned char*)Src->data_dwordC);
			}
			callDrawBitmapOnBitmap(0, posX, posY, width, height, Src->bitmap, offsetX, offsetY, 0, flag);
		}
	}
	if(!Renderer::forceDisableNativeDrawing)
		return origDrawLandscape(a1, a2, Src, posX, posY, offsetX, offsetY, width, height, flag);
}

//int *__fastcall maybe_redraw_frontend_landscape_bitmap_sub_5A0BD0(_DWORD *a1, _DWORD *a2, int a3, int a4, int a5, int a6, int a7, size_t Size, int a9, int a10)
DWORD (__fastcall *origRedrawFrontendBitmap)(Renderer::BitmapDescriptor *  a1, DWORD a2, int a3, int a4, Renderer::BitmapDescriptor *  a5, int a6, int a7, int a8, int a9, int a10);
DWORD __fastcall Drawing::hookRedrawFrontendBitmap(Renderer::BitmapDescriptor * a1, DWORD a2, int a3, int a4, Renderer::BitmapDescriptor *  a5, int a6, int a7, int a8, int a9, int a10) {
//	if(Config::rendererEnabled) {
//		printf("RedrawFrontendBitmap %X a2: %X a3: %d a4: %d a5: %X a6: %d a7: %d a8: %d a9: %d a10: %d\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
//	}
	if(!Renderer::forceDisableNativeDrawing)
		return origRedrawFrontendBitmap(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}


float rot = 0;
void Drawing::callDrawBitmapOnBitmap(Bitmap::BitmapImage *Dst, int posX, int posY, int width, int height, Bitmap::BitmapImage *Src, int srcOffsetX, int srcOffsetY, int a9, int flags) {
	_asm push flags
	_asm push a9
	_asm push srcOffsetY
	_asm push srcOffsetX
	_asm push Src
	_asm push height
	_asm push width
	_asm push posY
	_asm push posX
	_asm mov esi, Dst
	_asm call hookDrawBitmapOnBitmap
}


DWORD origDrawBitmapOnBitmap;
int __stdcall Drawing::hookDrawBitmapOnBitmap(int posX, int posY, int width, int height, Bitmap::BitmapImage *Src, int srcOffsetX, int srcOffsetY, int a9, int flags) {
	Bitmap::BitmapImage * Dst;
	int retv;
	_asm mov Dst, esi

	bool drawToScreen = true;
	ExtendedBitmap * srcExtension = nullptr, * dstExtension = nullptr;
	if(Config::rendererEnabled && Renderer::glewInitialized && Renderer::glContextCreated) {
		auto dddisplay = Game::getAddrDdDisplay();
		drawToScreen = (!Dst || (dddisplay && ((DWORD) Dst == *(DWORD *) (dddisplay + 0x3D9C))));

		if (Src->bitdepth_dwordC == 8 && (drawToScreen || (Dst && Dst->bitdepth_dwordC == 8))) {

			srcExtension = BitmapExtension::findBitmapExtension(Src);
			if (!srcExtension) {
				printf("hookDrawBitmapOnBitmap: creating Src BitmapExtension: %X %dx%d (rowsize: %d, depth: %d)\n", Src, Src->max_width_dword14, Src->max_height_dword18, Src->rowsize_dword10, Src->bitdepth_dwordC);
				srcExtension = BitmapExtension::constructBitmapImageExtension(Src);
			}
			if (!srcExtension->populated) {
				printf("hookDrawBitmapOnBitmap: populating Src BitmapExtension: %X %dx%d (rowsize: %d, depth: %d)\n", Src, Src->max_width_dword14, Src->max_height_dword18, Src->rowsize_dword10, Src->bitdepth_dwordC);
//				auto data = BitmapExtension::convertBitmapImageToGLRGBA(Src, nullptr, (ScreenPalette*)Renderer::addrScreenPalette);
				auto data = (unsigned char *) Src->data_dword8;
				BitmapExtension::populateBitmapImageExtension(Src, data);
			}
			if(srcExtension->redraw) {
				srcExtension->redraw = false;
				BitmapExtension::redrawBitmapImageExtension(Src);
			}

			dstExtension = BitmapExtension::findBitmapExtension(Dst);
			if (!drawToScreen && Dst->bitdepth_dwordC == 8) {
				if (!dstExtension) {
					printf("hookDrawBitmapOnBitmap: creating Dst BitmapExtension: %X %dx%d (rowsize: %d, depth: %d)\n", Dst, Dst->max_width_dword14, Dst->max_height_dword18, Dst->rowsize_dword10, Dst->bitdepth_dwordC);
					dstExtension = BitmapExtension::constructBitmapImageExtension(Dst);
				}
				if (!dstExtension->populated) {
					printf("hookDrawBitmapOnBitmap: populating Dst BitmapExtension: %X %dx%d (rowsize: %d, depth: %d)\n", Dst, Dst->max_width_dword14, Dst->max_height_dword18, Dst->rowsize_dword10, Dst->bitdepth_dwordC);
//					auto data = BitmapExtension::convertBitmapImageToGLRGBA(Dst, nullptr, (ScreenPalette*)Renderer::addrScreenPalette);
					auto data = (unsigned char *) Dst->data_dword8;
					BitmapExtension::populateBitmapImageExtension(Dst, data);
				}
			}

			GLint dstBuffer, srcTexture;
			int dstWidth, dstHeight;

			int srcWidth = Src->max_width_dword14;
			int srcHeight = Src->max_height_dword18;
			int glOffsetX = srcOffsetX;
			int glOffsetY = srcOffsetY;
			int glWidth = width;
			int glHeight = height;
			if (srcExtension->sprite) {
				srcWidth = srcExtension->spriteMaxW;
				glOffsetY += srcExtension->spriteFrames[Src->data_dword8] * srcExtension->spriteMaxH;
				srcHeight = srcExtension->spriteMaxH * srcExtension->sprite->max_frames_word16;
			}
			srcTexture = srcExtension->texture;
			if (drawToScreen) {
				dstWidth = Renderer::screenWidth;
				dstHeight = Renderer::screenHeight;
				dstBuffer = 0;
			} else {
				dstBuffer = dstExtension->framebuffer;
				dstWidth = Dst->current_width_dword24;
				dstHeight = Dst->current_height_dword28;
			}

			glDisable(GL_DEPTH_TEST);
			glBindFramebuffer(GL_FRAMEBUFFER, dstBuffer);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();

			glPushAttrib(GL_VIEWPORT_BIT);
			glViewport(0, 0, dstWidth, dstHeight);
			if (drawToScreen)
				glOrtho(0, dstWidth, dstHeight, 0, -1, 1);
			else
				glOrtho(0, dstWidth, 0, dstHeight, -1, 1);

			GLfloat startx = (float) glOffsetX / (float) srcWidth;
			GLfloat starty = (float) glOffsetY / (float) srcHeight;
			GLfloat endx = (float) (glOffsetX + width) / (float) srcWidth;
			GLfloat endy = (float) (glOffsetY + height) / (float) srcHeight;

			int sPosX = posX;
			int sPosY = posY;

//			int srcWidth2 = Src->current_width_dword24;
//			int srcHeight2 = Src->current_height_dword28;
//			glTranslatef(sPosX + srcWidth2/2, sPosY + srcHeight2/2, 0);
//			glRotatef(Renderer::rot, 0, 0, 1);
//			glTranslatef(-sPosX - srcWidth2/2, -sPosY - srcHeight2/2, 0);

			glEnable(GL_TEXTURE_2D);
			if (flags & 0x1) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBlendEquation(GL_FUNC_ADD);
			}

			GLint whichID;
			glActiveTexture(GL_TEXTURE0);
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &whichID);
			glBindTexture(GL_TEXTURE_2D, srcTexture);

			if (flags & 0x10000) { // flip horizontal
				int tmp = startx;
				startx = endx;
				endx = tmp;
			}

			if(drawToScreen) {
				glUseProgram(paletteShaderProgram);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_1D, palette_texture);

				glUniform1i(palette_IndexedTextureSamplerLocation, 0);
				glUniform1i(palette_PaletteTextureSamplerLocation, 1);
				glUniform1i(palette_TransparentFlagLocation, (int)(flags & 0x1) != 0);

				glActiveTexture(GL_TEXTURE0);
			} else {
				glUseProgram(indexedShaderProgram);
			}
			glBegin(GL_QUADS);
			glTexCoord2f(startx, starty);
			glVertex2i(sPosX, sPosY);
			glTexCoord2f(endx, starty);
			glVertex2i(sPosX + glWidth, sPosY);
			glTexCoord2f(endx, endy);
			glVertex2i(sPosX + glWidth, sPosY + glHeight);
			glTexCoord2f(startx, endy);
			glVertex2i(sPosX, sPosY + glHeight);
			glEnd();


			glBindTexture(GL_TEXTURE_2D, whichID);
			glDisable(GL_TEXTURE_2D);
			if (Config::rendererDebugPoints) {
				glPointSize(8.0f);
				glBegin(GL_POINTS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex2i(0, 0);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex2i(sPosX, sPosY);
				glColor3f(0.0f, 1.0f, 1.0f);
				glVertex2i(sPosX + width, sPosY + height);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);
			}
			if (flags & 0x1) {
				glDisable(GL_BLEND);
			}


			glPopMatrix();
			glPopAttrib();
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glUseProgram(0);
		}
	}
	if(!Dst) return 0;
	if(Config::rendererEnabled && drawToScreen) return 0;


	_asm mov esi, Dst
	_asm push flags
	_asm push a9
	_asm push srcOffsetY
	_asm push srcOffsetX
	_asm push Src
	_asm push height
	_asm push width
	_asm push posY
	_asm push posX
	_asm call origDrawBitmapOnBitmap
	_asm mov retv, eax

	if(Config::rendererEnabled && !drawToScreen && dstExtension) {
		dstExtension->redraw = true;
	}

	return retv;
}


void Drawing::compileShaders() {
	try {
//		glEnableClientState(GL_VERTEX_ARRAY);
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		const char *vs_c_str = vertexShaderSource.c_str();
		glShaderSource(vertex, 1, (const GLchar *const *) &vs_c_str, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to compile vertex shader, reason:\n" + std::string(infoLog));
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		const char *fs_c_str = indexedFragmentShaderSource.c_str();
		glShaderSource(fragment, 1, (const GLchar *const *) &fs_c_str, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to compile fragment shader (indexed), reason:\n" + std::string(infoLog));
		};

		GLint ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to link shader program, reason:\n" + std::string(infoLog));
			return;
		}

		glDeleteShader(fragment);
		indexedShaderProgram = ID;

		indexed_TextureSamplerLocation = glGetUniformLocation(indexedShaderProgram, "indexed_text");


		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		fs_c_str = paletteFragmentShaderSource.c_str();
		glShaderSource(fragment, 1, (const GLchar *const *) &fs_c_str, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to compile fragment shader (palette), reason:\n" + std::string(infoLog));
		};

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, sizeof(infoLog), NULL, infoLog);
			throw std::runtime_error("Failed to link shader program (palette), reason:\n" + std::string(infoLog));
			return;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		paletteShaderProgram = ID;
		palette_IndexedTextureSamplerLocation = glGetUniformLocation(paletteShaderProgram, "indexed_text");
		palette_PaletteTextureSamplerLocation = glGetUniformLocation(paletteShaderProgram, "palette_text");
		palette_TransparentFlagLocation = glGetUniformLocation(paletteShaderProgram, "transparent_flag");

	}
	catch(std::exception & e) {
		MessageBoxA(0, e.what(), "Failed to compile shader", 0);
	}
}

void Drawing::genPaletteTexture(DWORD palette) {
	auto screenpal = (ScreenPalette *) palette;
	static auto data = (DWORD*)malloc(sizeof(DWORD) * 256);

//	palette = 0;

	if(!palette) {
		for(int i=0; i < 256; i++) {
			data[i] = 0xFF000000 | (rand() & 0xFF) << 16 | (rand() & 0xFF) << 8 | (rand() & 0xFF);
//			printf("Color (rand): %d = 0x%08X\n", i, data[i]);
		}
	} else {
		for(int i=0; i < 256; i++) {
			data[i] = screenpal->colors[i].toRGBA();
//			printf("Color (screen): %d = 0x%08X\n", i, data[i]);
		}
	}

	if(!palette_texture) {
		glGenTextures(1, &palette_texture);
	}
	GLint oldbind;
	glGetIntegerv(GL_TEXTURE_BINDING_1D, &oldbind);
	glBindTexture(GL_TEXTURE_1D, palette_texture);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA32F, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_1D, oldbind);
}


//WPalette *__thiscall SWITCH_PALETTE_hooked_by_indimask_sub_56A1A0(DD_Display *this, WPalette *a2, int commit_a3)
DWORD (__fastcall *origSwitchScreenPalette)(DWORD This, int EDX, DWORD palette, int commit);
DWORD __fastcall Drawing::hookSwitchScreenPalette(DWORD This, int EDX, DWORD palette, int commit) {
	auto ret = origSwitchScreenPalette(This, EDX, palette, commit);
//	if(Config::rendererEnabled) {
//		genPaletteTexture(palette);
//	}
	return ret;
}

int Drawing::install(SignatureScanner &, module) {
	DWORD addrDrawLandscape = Hooks::scanPattern("DrawLandscape", "\x55\x8B\xEC\x83\xE4\xF8\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x30\x53\x56\x57\x8B\xD9\x8B\x4D\x08\x8B\xFA", "??????xxx????xx????xxxx????xxxxxxxxxxxxx", 0x5A2790);
	DWORD addrDrawBitmapOnBitmap = Hooks::scanPattern("DrawBitmapOnBitmap", "\x55\x8B\xEC\x83\xE4\xF8\x8B\x4D\x10\x8B\x45\x18\x83\xEC\x38\x85\xC9\x53\x57\x0F\x84\x00\x00\x00\x00\x83\x7D\x14\x00\x0F\x84\x00\x00\x00\x00\x8B\x50\x08\x8B\x78\x10\x8B\x46\x20\x8B\x5E\x1C", "??????xxxxxxxxxxxxxxx????xxxxxx????xxxxxxxxxxxx", 0x4F6910);
	DWORD addrRedrawFrontendBitmap = Renderer::addrBitmapDescriptorVTable[11]; //5A0BD0

	DWORD addrSwitchScreenPalette = Hooks::scanPattern("SwitchScreenPalette", "\x51\x8B\x44\x24\x08\x66\x83\xB8\x00\x00\x00\x00\x00\x56\x8B\xF1\x66\xC7\x80\x00\x00\x00\x00\x00\x00\x0F\x8E\x00\x00\x00\x00\x53\x0F\xBF\x58\x02\x55\x0F\xBF\x28\x57\x0F\xB6\xB8\x00\x00\x00\x00\x89\x5C\x24\x10", "??????xx?????xxxxxx??????xx????xxxxxxxxxxxxx????xxxx", 0x56A610);

	Hooks::polyhook("DrawBitmapOnBitmap", addrDrawBitmapOnBitmap, (DWORD *) &hookDrawBitmapOnBitmap, (DWORD *) &origDrawBitmapOnBitmap);
	Hooks::polyhook("DrawLandscape", addrDrawLandscape, (DWORD *) &hookDrawLandscape, (DWORD *) &origDrawLandscape);
	Hooks::polyhook("RedrawFrontendBitmap", addrRedrawFrontendBitmap, (DWORD *) &hookRedrawFrontendBitmap, (DWORD *) &origRedrawFrontendBitmap);
	Hooks::polyhook("SwitchScreenPalette", addrSwitchScreenPalette, (DWORD *) &hookSwitchScreenPalette, (DWORD *) &origSwitchScreenPalette);

	return 0;
}
