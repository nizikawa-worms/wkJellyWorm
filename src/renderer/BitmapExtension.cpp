
#include <src/WaLibc.h>
#include "BitmapExtension.h"


ExtendedBitmap::ExtendedBitmap(Bitmap::BitmapImage *bitmap, Sprites * sprite, int align) : populated(false), sprite(sprite), align(align) {
	bitdepth = 8;
}



ExtendedBitmap * BitmapExtension::constructBitmapImageExtension(Bitmap::BitmapImage *bitmap, Sprites* sprite, int align) {
	auto extension = new ExtendedBitmap(bitmap, sprite, align);
	extensionMap[bitmap] = extension;
	return extension;
}

bool BitmapExtension::populateBitmapImageExtension(Bitmap::BitmapImage *bitmap, unsigned char * data, int forceWidth, int forceHeight) {
	if(bitmap) {
		auto extension = findBitmapExtension(bitmap);
		if(extension && !extension->populated) {
			int width = (!forceWidth) ? bitmap->max_width_dword14 : forceWidth;
			int height = (!forceHeight) ? bitmap->max_height_dword18 : forceHeight;

			glGenFramebuffers(1, &extension->framebuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, extension->framebuffer);
			glGenTextures(1, &extension->texture);
			GLint oldbind;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldbind);
			glBindTexture(GL_TEXTURE_2D, extension->texture);

			if(extension->align != 4)
				glPixelStorei(GL_UNPACK_ALIGNMENT, extension->align);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, data);
			if(extension->align != 4)
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, extension->texture, 0);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				printf("!!!!!!!!!!!!!!!!!!! populateBitmapImageExtension: Failed to create framebuffer\n");
			}

			glBindTexture(GL_TEXTURE_2D, oldbind);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			extension->populated = true;
			return true;
		}
	}
	return false;
}

bool BitmapExtension::paintOnBitmapImageExtension(Bitmap::BitmapImage *bitmap, unsigned char *data, int posX, int posY, int width, int height) {
	if(bitmap) {
		auto extension = findBitmapExtension(bitmap);
		if (extension && extension->populated) {
			glEnable(GL_TEXTURE_2D);
			GLint oldbind;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldbind);
			glBindTexture(GL_TEXTURE_2D, extension->texture);
//			glTexSubImage2D(GL_TEXTURE_2D, 0, posX, posY, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			if(extension->align != 4)
				glPixelStorei(GL_UNPACK_ALIGNMENT, extension->align);
			glTexSubImage2D(GL_TEXTURE_2D, 0, posX, posY, width, height, GL_RED_INTEGER, GL_UNSIGNED_BYTE, data);
			if(extension->align != 4)
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

			glBindTexture(GL_TEXTURE_2D, oldbind);
			glDisable(GL_TEXTURE_2D);
			return true;
		}
	}
	return false;
}

unsigned char * BitmapExtension::convertBitmapImageToGLRGBA(Bitmap::BitmapImage *bitmap, GamePalette *gamePalette, ScreenPalette *screenPalette, int forceWidth, int forceHeight) {
	int width = (!forceWidth && bitmap) ? bitmap->max_width_dword14 : forceWidth;
	int height = (!forceHeight && bitmap) ? bitmap->max_height_dword18 : forceHeight;
	auto data = (unsigned char *) WaLibc::waMalloc(sizeof(DWORD) * width * height);
	if(!data) return (unsigned char*)data;

	if(!gamePalette && !screenPalette) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				unsigned char color = *(unsigned char *) (bitmap->data_dword8 + y * bitmap->rowsize_dword10 + x);
				data[y * bitmap->max_width_dword14 + x] = 0xFF000000 | (color << 16) | (color << 8) | color;
			}
		}
	}
	else if(gamePalette) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				unsigned char palcolor = *(unsigned char*)(bitmap->data_dword8 + y*bitmap->rowsize_dword10 + x);
				DWORD color = (!palcolor) ? 0 : gamePalette->colors[palcolor].toRGBA();
				data[y * bitmap->max_width_dword14 + x] = color;
			}
		}
	}
	else if(screenPalette) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				unsigned char palcolor = *(unsigned char*)(bitmap->data_dword8 + y*bitmap->rowsize_dword10 + x);
				data[y * bitmap->max_width_dword14 + x] = (!palcolor) ? 0 : screenPalette->colors[palcolor].toRGBA();
			}
		}
	}

	return (unsigned char*)data;
}



bool BitmapExtension::destroyBitmapImageExtension(Bitmap::BitmapImage *bitmap) {
	if(bitmap) {
		auto extension = findBitmapExtension(bitmap);
		if(extension) {
			if(extension->populated) {
				glDeleteFramebuffers(1, &extension->framebuffer);
				glDeleteTextures(1, &extension->texture);
			}
			extensionMap.erase(bitmap);
			delete extension;
			return true;
		}
	}
	return false;
}

ExtendedBitmap* BitmapExtension::findBitmapExtension(Bitmap::BitmapImage *bitmap) {
	auto it = extensionMap.find(bitmap);
	if(it != extensionMap.end()) {
		return it->second;
	}
	return nullptr;
}

void BitmapExtension::redrawBitmapImageExtension(Bitmap::BitmapImage *bitmap) {
	if(bitmap) {
		auto extension = findBitmapExtension(bitmap);
		if (extension && extension->populated) {
			paintOnBitmapImageExtension(bitmap, (unsigned char*)bitmap->data_dword8, 0, 0, bitmap->current_width_dword24, bitmap->current_height_dword28);
		}
	}
}

void BitmapExtension::convertSprite(Sprites *sprite, GamePalette *palette) {
	auto bitmap = (Bitmap::BitmapImage8 *) &sprite->bitmap_dword34;
	auto extension = constructBitmapImageExtension(bitmap, sprite);

	// find max frame size
	int maxw = 0, maxh = 0;
	for (int i = 0; i < sprite->max_frames_word16; i++) {
		Sprites::SpriteFrame *frame = &sprite->frame_meta_ptr_dword28[i];
		int width = frame->endx - frame->startx;
		int height = frame->endy - frame->starty;
		maxw = max(maxw, width);
		maxh = max(maxh, height);
	}
	extension->spriteMaxW = maxw;
	extension->spriteMaxH = maxh;
	populateBitmapImageExtension(bitmap, nullptr, maxw, maxh * sprite->max_frames_word16);

	for (int i = 0; i < sprite->max_frames_word16; i++) {
		Sprites::SpriteFrame *frame = &sprite->frame_meta_ptr_dword28[i];
		int width = frame->endx - frame->startx;
		int height = frame->endy - frame->starty;
		bitmap->data_dword8 = sprite->probably_sprite_bitmap_data_dword64 + frame->bitmapoffset;
		bitmap->max_width_dword14 = width;
		bitmap->max_height_dword18 = height;
		bitmap->rowsize_dword10 = width;
		int posX = 0;
		int posY = i * maxh;
		auto data = (unsigned char *) bitmap->data_dword8;
		paintOnBitmapImageExtension(bitmap, data, posX, posY, width, height);
		extension->spriteFrames[bitmap->data_dword8] = i;
	}
	bitmap->data_dword8 = 0;
	bitmap->max_width_dword14 = 0;
	bitmap->max_height_dword18 = 0;
	bitmap->rowsize_dword10 = 0;
}

void BitmapExtension::onDestroySprite(Sprites *sprite) {
	destroyBitmapImageExtension((Bitmap::BitmapImage*)&sprite->bitmap_dword34);
}


