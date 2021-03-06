#include "WaLibc.h"
#include "Hooks.h"


void *(__cdecl * origWaNew)(size_t size);
void *WaLibc::waMalloc(size_t size) {
	return origWaNew(size);
}

void (__cdecl *origWaFree)(void * ptr);
void WaLibc::waFree(void *ptr) {
	origWaFree(ptr);
}

int WaLibc::install(SignatureScanner &, module) {
	DWORD addrWaMallocMemset = Hooks::scanPattern("WaMallocMemset", "\x8D\x47\x03\x83\xE0\xFC\x83\xC0\x20\x56\x50\xE8\x00\x00\x00\x00\x57\x8B\xF0\x6A\x00\x56\xE8\x00\x00\x00\x00\x83\xC4\x10\x8B\xC6\x5E\xC3", "??????xxxxxx????xxxxxxx????xxxxxxx", 0x53E910);
	origWaNew = (void *(__cdecl *)(size_t)) (addrWaMallocMemset + 0x10 +  *(DWORD*)(addrWaMallocMemset +  0xC));
	origWaFree = (void (__cdecl *)(void *))Hooks::scanPattern("WaFree", "\x6A\x0C\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x75\x08\x85\xF6\x74\x75\x83\x3D\x00\x00\x00\x00\x00\x75\x43\x6A\x04\xE8\x00\x00\x00\x00\x59\x83\x65\xFC\x00", "???????x????xxxxxxxxx?????xxxxx????xxxxx", 0x5D0D2B);
	return 0;
}