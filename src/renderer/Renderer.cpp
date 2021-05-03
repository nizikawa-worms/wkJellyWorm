
#include <functional>
#include "Renderer.h"
#include "Bitmap.h"
#include "../Game.h"
#include "../WaLibc.h"
#include "../Hooks.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <set>
#include "Palette.h"
#include "../Config.h"
#include "Drawing.h"


int Renderer::onConstructGlobalContext(int a1) {
	return 0;
}

int Renderer::CTaskTurnGame_vt8(CTaskTurnGame *This, CTask * sender, Constants::TaskMessage mtype, size_t size, void * data) {
	if(mtype == Constants::TaskMessage_RenderScene) {
	}
	return 0;
}


DWORD origBlitScreen;
DWORD __stdcall hookBlitScreen(int width_a3, int a4, DWORD * output_buffer, int a6, DWORD * palette_a7) {
	if(Config::rendererEnabled) return 0;

	DWORD height_a1, retv;
	DWORD * source_buffer;
	_asm mov height_a1, eax
	_asm mov source_buffer, ecx

	_asm mov eax, height_a1
	_asm mov ecx, source_buffer
	_asm push palette_a7
	_asm push a6
	_asm push output_buffer
	_asm push a4
	_asm push width_a3
	_asm call origBlitScreen
	_asm mov retv, eax
	return retv;
}

Renderer::BitmapDescriptor* (__stdcall *origConstructBitmapDescriptor)();
Renderer::BitmapDescriptor* __stdcall Renderer::hookConstructBitmapDescriptor() {
	if(!Config::rendererEnabled) return origConstructBitmapDescriptor();
	auto ret = (BitmapDescriptor*) WaLibc::waMalloc(sizeof(BitmapDescriptor));
	if(!ret) return ret;
	memset(ret, 0, sizeof(BitmapDescriptor));
	ret->vtable = (DWORD)addrBitmapDescriptorVTable;
	return ret;
}

DWORD (__fastcall *origDestroyBitmapDescriptor)(Renderer::BitmapDescriptor * This, int EDX, int a2);
DWORD __fastcall Renderer::hookDestroyBitmapDescriptor(Renderer::BitmapDescriptor * This, int EDX, int a2) {
	if(Config::rendererEnabled && This->vtable == (DWORD)addrBitmapDescriptorVTable && This->bitmap) {
		BitmapExtension::destroyBitmapImageExtension(This->bitmap);
		WaLibc::waFree((void*)This->bitmap);
		This->bitmap = 0;
	}
	return origDestroyBitmapDescriptor(This, EDX, a2);
}

DWORD (__fastcall *origDrawBitmapOnBitmapAnyDepth)(int flags, int srcOffsetY, int posX, int posY, int endX, int endY, int srcOffsetX, Bitmap::BitmapImage *Src, Bitmap::BitmapImage *Dst, int a10);
DWORD __fastcall Renderer::hookDrawBitmapOnBitmapAnyDepth(int flags, int srcOffsetY, int posX, int posY, int endX, int endY, int srcOffsetX, Bitmap::BitmapImage *Src, Bitmap::BitmapImage *Dst, int a10) {
	return origDrawBitmapOnBitmapAnyDepth(flags, srcOffsetY, posX, posY, endX, endY, srcOffsetX, Src, Dst, a10);
}


DWORD (__fastcall *origMarkScreenAsReady)(Renderer::OpenGLRenderer * a1, DWORD a2);
int (__fastcall *origOpenGLDraw)(Renderer::OpenGLRenderer * a1, int a2, int a3);
int __fastcall hookOpenGLDraw(Renderer::OpenGLRenderer * a1, int a2, int a3) {
	if(!Config::rendererEnabled) {
		return origOpenGLDraw(a1, a2, a3);
	}
	return origMarkScreenAsReady(a1, a2);
}

DWORD (__fastcall *origOpenGLSwapBuffers)(int a1, DWORD a2);
DWORD __fastcall Renderer::hookOpenGLSwapBuffers(int a1, DWORD a2) {
	auto ret = origOpenGLSwapBuffers(a1, a2);
	if(Config::rendererEnabled) {
		glClear(GL_COLOR_BUFFER_BIT);
		rot += 0.3;
	}
	return ret;
}

void GLAPIENTRY GLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
		printf("!!!!!!!!!!!!!!!!!! GLErrorCallback: %s\n", message);
	}
}

DWORD (__stdcall *origOpenGLInit)(int width, int height);
DWORD __stdcall Renderer::hookOpenGLInit(int width, int height) {
	auto ret = origOpenGLInit(width, height);
	if(Config::rendererEnabled) {
		printf("OpenGL init\n");
		screenWidth = width;
		screenHeight = height;
		glewInit();
		glewInitialized = true;
//		Drawing::genPaletteTexture(0);
		if(Config::rendererDebugContext) {
			glDebugMessageCallback(GLErrorCallback, nullptr);
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		}
		Drawing::compileShaders();
	}

	return ret;
}

HGLRC __stdcall Renderer::hookOpenGLCreateContext_cpp(HDC dc) {
	glContextCreated = true;
	if(!Config::rendererEnabled) {
		printf("hookCallOpenGLCreateContext: creating default opengl context\n");
		return wglCreateContext(dc);
	} else {
#define WGL_CONTEXT_DEBUG_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define setAttrib(a, v) \
{ \
    assert(((size_t) index + 1) < sizeof(attribs) / sizeof(attribs[0])); \
    attribs[index++] = a; \
    attribs[index++] = v; \
}

		auto origcontext = wglGetCurrentContext();
		auto temprc = wglCreateContext(dc);
		wglMakeCurrent(dc, temprc);

		HGLRC (__stdcall *imp_wglCreateContextAttribsARB)(HDC hDC, HGLRC hShareContext, const int *attribList);
		imp_wglCreateContextAttribsARB = (HGLRC (__stdcall *)(HDC, HGLRC, const int *)) wglGetProcAddress("wglCreateContextAttribsARB");

		int attribs[40];
		memset(attribs, 0, sizeof(attribs));
		int mask = 0, flags = 0, index = 0;

		mask |= WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
		if(Config::rendererDebugContext)
			flags |= WGL_CONTEXT_DEBUG_BIT_ARB;
		setAttrib(WGL_CONTEXT_MAJOR_VERSION_ARB, Config::rendererGLMajor);
		setAttrib(WGL_CONTEXT_MINOR_VERSION_ARB, Config::rendererGLMinor);
		setAttrib(WGL_CONTEXT_FLAGS_ARB, flags);
		setAttrib(WGL_CONTEXT_PROFILE_MASK_ARB, mask);

		HGLRC share = nullptr;
		auto ret = imp_wglCreateContextAttribsARB(dc, share, attribs);

		wglMakeCurrent(dc, origcontext);
		wglDeleteContext(temprc);

		printf("Creating custom OpenGL context, version: %d.%d, result: %X\n", Config::rendererGLMajor, Config::rendererGLMinor, ret);
		return ret;
	}
}

DWORD addrCallOpenGLCreateContext_ret;
DWORD addrWglCreateContext;
void __declspec(naked) hookCallOpenGLCreateContext() {
	_asm push esi
	_asm push edi
	_asm mov ecx,dword ptr ds:[esi+0x18]
	_asm push ecx
	_asm call Renderer::hookOpenGLCreateContext_cpp
	_asm pop edi
	_asm pop esi
	_asm mov dword ptr ds:[esi+0x1C],eax
	_asm test eax,eax

//	_asm mov ecx,dword ptr ds:[esi+0x18]
//	_asm push ecx
//	_asm call addrWglCreateContext
//	_asm mov dword ptr ds:[esi+0x1C],eax
//	_asm test eax,eax

	_asm jmp addrCallOpenGLCreateContext_ret
}


void (__stdcall *origRenderDrawingQueue)(DWORD dddisplay, DWORD a3);
void __stdcall Renderer::hookRenderDrawingQueue(DWORD dddisplay, DWORD a3) {
	DWORD GameScene;
	_asm mov GameScene, eax

	insideRenderDrawingQueue = true;

	_asm mov eax, GameScene
	_asm push a3
	_asm push dddisplay
	_asm call origRenderDrawingQueue

	insideRenderDrawingQueue = false;
}


DWORD origWriteScreenPalette;
DWORD __stdcall Renderer::hookWriteScreenPalette(DWORD a2) {
	DWORD sedi, retv;
	_asm mov sedi, edi


	_asm mov edi, sedi
	_asm push a2
	_asm call origWriteScreenPalette
	_asm mov retv, eax

	Drawing::genPaletteTexture(sedi);

	return retv;
}


int Renderer::install(SignatureScanner &, module) {
	CTaskTurnGame::registerBuiltinCallbackVt8(&CTaskTurnGame_vt8);

	DWORD addrBlitScreen = Hooks::scanPattern("BlitScreen", "\x85\xC0\x8B\x54\x24\x04\x53\x8B\x5C\x24\x18\x56\x57\x8B\x7C\x24\x18\x8B\xF1\x76\x3A\x89\x44\x24\x20\x55\x8D\x9B\x00\x00\x00\x00\x85\xD2\x8B\xCE\x8B\xC7", "??????xxxxxxxxxxxxxxxxxxxxxx????xxxxxx", 0x5A2020);
	DWORD addrConstructFrameBuffer = Hooks::scanPattern("ConstructFrameBuffer", "\x51\x83\x3D\x00\x00\x00\x00\x00\x53\x55\x56\x57\x8B\xEA\x8B\xF1\x74\x0D\x8B\x06\x8B\x40\x1C\x6A\x00\x8D\x54\x24\x14\xFF\xD0\x8B\x7C\x24\x18", "????????xxxxxxxxxxxxxxxxxxxxxxxxxxx", 0x5A2430);
	DWORD addrConstructDDDisplay = Hooks::scanPattern("ConstructDDDisplay", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x8B\x44\x24\x18\x83\xEC\x08\x53\x55\x8B\x6C\x24\x20\x89\x85\x00\x00\x00\x00\x89\x85\x00\x00\x00\x00\x99\x2B\xC2", "???????xx????xxxx????xxxxxxxxxxxxxxx????xx????xxx", 0x569D00);
	DWORD addrDrawBitmapOnBitmapAnyDepth = Hooks::scanPattern("DrawBitmapOnBitmapAnyDepth", "\x8B\x44\x24\x08\x53\x55\x8B\x6C\x24\x28\x8B\xD9\x56\x8B\x74\x24\x28\x81\xE3\x00\x00\x00\x00\x83\xFB\x05\x57\x8B\x7C\x24\x28\x77\x27\xFF\x24\x9D\x00\x00\x00\x00", "??????xxxxxxxxxxxxx????xxxxxxxxxxxxx????", 0x4F80C0);


//	DWORD addrMainReferencesOpenGLCpuVtable = Hooks::scanPattern("MainReferencesOpenGLCpuVtable", "\x74\x34\x89\x48\x18\x89\x48\x1C\x89\x48\x20\x89\x70\x24\x89\x48\x40\x8D\x97\x00\x00\x00\x00\x89\x50\x10\x89\x48\x14", "xxxxxxxxxxxxxxxxxxx????xxxxxx", 0x4E8101);
	DWORD addrConstructOpenGLCpu = Hooks::scanPattern("ConstructOpenGLCPU", "\x6A\x48\xE8\x00\x00\x00\x00\x33\xC9\x83\xC4\x04\x3B\xC1\x74\x29\x8B\x54\x24\x08\x89\x50\x24\x8B\x54\x24\x04\x89\x48\x18\x89\x48\x1C\x89\x48\x20\x89\x48\x40\x89\x50\x10\x89\x48\x14\xC7\x00\x00\x00\x00\x00\x89\x48\x44\xC2\x08\x00", "???????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx", 0x5A0850);
	DWORD* addrOpenGLCpuVtable = *(DWORD**)(addrConstructOpenGLCpu + 0x2F);

//	DWORD addrOpenGLDraw = Hooks::scanPattern("OpenGLDraw", "\x81\xEC\x00\x00\x00\x00\x53\x55\x8B\x2D\x00\x00\x00\x00\x57\x8B\xDA\x8B\xF9\xFF\xD5\x85\xC0\x74\x57\x8B\x07\x8B\x40\x1C\x6A\x00\x8D\x54\x24\x10\x8B\xCF\xFF\xD0\x8B\x0D\x00\x00\x00\x00\x8B\xC1", "??????xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xx", 0x59F3B0);
	DWORD addrOpenGLDraw = addrOpenGLCpuVtable[12];
	DWORD addrOpenGLSwapBuffers = addrOpenGLCpuVtable[13];
	origMarkScreenAsReady = (DWORD (__fastcall *)(Renderer::OpenGLRenderer*,DWORD))addrOpenGLCpuVtable[1];
	DWORD addrOpenGLInit = Hooks::scanPattern("OpenGLInit", "\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\x53\x56\x57\x89\x65\xE8\x8B\xFA\x89\x7D\xE4\x8B\xF1\x8B\x5D\x08", "??????????x????xx????xxxx????xx????xxxxxxxxxxxxxxxx", 0x59F000);

	DWORD addrConstructBitmapDescriptor = Hooks::scanPattern("ConstructBitmapDescriptor", "\x6A\x14\xE8\x00\x00\x00\x00\x33\xC9\x83\xC4\x04\x3B\xC1\x74\x13\x89\x48\x04\x89\x48\x08\xC7\x00\x00\x00\x00\x00\x89\x48\x0C\x88\x48\x10\xC3", "???????xxxxxxxxxxxxxxxxx????xxxxxxx", 0x5A2760);
	addrBitmapDescriptorVTable = *(DWORD**)(addrConstructBitmapDescriptor + 0x18);
	DWORD addrDestroyBitmapDescriptor = addrBitmapDescriptorVTable[0];
			// wrong Hooks::scanPattern("DestroyBitmapDescriptor", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x08\x56\x8B\xF1\x89\x74\x24\x08\xC7\x06\x00\x00\x00\x00\xC7\x44\x24\x00\x00\x00\x00\x00", "???????xx????xxxx????xxxxxxxxxxxx????xxx?????", 0x426AA0);



	DWORD addrWriteScreenPalette = Hooks::scanPattern("WriteScreenPalette", "\x53\x8B\x5C\x24\x08\x55\xBA\x00\x00\x00\x00\x8B\xC7\xB9\x00\x00\x00\x00\x56\x8B\x31\x3B\x30\x75\x12\x83\xEA\x04\x83\xC0\x04\x83\xC1\x04\x83\xFA\x04\x73\xEC", "??????x????xxx????xxxxxxxxxxxxxxxxxxxxx", 0x5A1110);
	addrScreenPalette = *(DWORD*)(addrWriteScreenPalette + 0xE);

	DWORD addrRenderDrawingQueue = Hooks::scanPattern("RenderDrawingQueue", "\x83\xEC\x1C\x53\x55\x8B\x6C\x24\x28\x56\x57\x8B\xF0\x8B\x86\x00\x00\x00\x00\x68\x00\x00\x00\x00\x6A\x04\x50\x8D\x8E\x00\x00\x00\x00\x51\xE8\x00\x00\x00\x00", "??????xxxxxxxxx????x????xxxxx????xx????", 0x542350);

	Hooks::polyhook("BlitScreen", addrBlitScreen, (DWORD *) &hookBlitScreen, (DWORD *) &origBlitScreen);
	Hooks::polyhook("DrawBitmapOnBitmapAnyDepth", addrDrawBitmapOnBitmapAnyDepth, (DWORD *) &hookDrawBitmapOnBitmapAnyDepth, (DWORD *) &origDrawBitmapOnBitmapAnyDepth);
	Hooks::polyhook("OpenGLDraw", addrOpenGLDraw, (DWORD *) &hookOpenGLDraw, (DWORD *) &origOpenGLDraw);
	Hooks::polyhook("OpenGLInit", addrOpenGLInit, (DWORD *) &hookOpenGLInit, (DWORD *) &origOpenGLInit);
	Hooks::polyhook("OpenGLSwapBuffers", addrOpenGLSwapBuffers, (DWORD *) &hookOpenGLSwapBuffers, (DWORD *) &origOpenGLSwapBuffers);

	Hooks::polyhook("DestroyBitmapDescriptor", addrDestroyBitmapDescriptor, (DWORD *) &hookDestroyBitmapDescriptor, (DWORD *) &origDestroyBitmapDescriptor);
	Hooks::polyhook("ConstructBitmapDescriptor", addrConstructBitmapDescriptor, (DWORD *) &hookConstructBitmapDescriptor, (DWORD *) &origConstructBitmapDescriptor);
	Hooks::polyhook("RenderDrawingQueue", addrRenderDrawingQueue, (DWORD *) &hookRenderDrawingQueue, (DWORD *) &origRenderDrawingQueue);
	Hooks::polyhook("WriteScreenPalette", addrWriteScreenPalette, (DWORD *) &hookWriteScreenPalette, (DWORD *) &origWriteScreenPalette);



	addrWglCreateContext = (DWORD)&wglCreateContext;
	DWORD addrOpenGLCreateContext = addrOpenGLInit + 0x27C;
	addrCallOpenGLCreateContext_ret = addrOpenGLInit + 0x28B;
	Hooks::hookAsm(addrOpenGLCreateContext, (DWORD) &hookCallOpenGLCreateContext);
	return 0;
}

void Renderer::toggleNativeDrawing() {
	forceDisableNativeDrawing = !forceDisableNativeDrawing;
	rot = 0;
}
