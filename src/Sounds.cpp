#include "Sounds.h"
#include "Hooks.h"
#include "Game.h"
#include "Lua.h"
#include <sol/sol.hpp>


DWORD (__fastcall *origLoadGameSoundFromFile)(DWORD This, int ECX, int index, const char * filename);
DWORD __fastcall hookLoadGameSoundFromFile(DWORD This, int EDX, int index, const char *filename) {
	auto ret = origLoadGameSoundFromFile(This, 0, index, filename);
//	printf("hookLoadGameSoundFromFile: %s = %d ret: %X\n", filename, index);
	return ret;
}

DWORD callLoadGameSoundFromFile(int index, std::string filename) {
	return hookLoadGameSoundFromFile(Game::getAddrDsSound(), 0, index, filename.c_str());
}

void Sounds::onConstructGlobalContext(int a1) {
	int id = customSoundStartingId;
	for(auto & it : customSounds) {
		printf("Loading custom sound: %s = %d\n", it.c_str(), id);
		callLoadGameSoundFromFile(id, it);
		id++;
	}
}

int Sounds::registerCustomSound(std::string filename) {
	customSounds.push_back(filename);
	return customSoundStartingId + customSounds.size() - 1;
}

void Sounds::resetConfig() {
	customSounds.clear();
}

DWORD addrPlaySoundLocal;
int Sounds::callPlaySoundLocal(int a1, int a2, CTask * object, Constants::SoundIds id, int a5) {
	int retv;
	_asm push a5
	_asm push id
	_asm mov edi, object
	_asm mov ecx, a2
	_asm mov eax, a1
	_asm call addrPlaySoundLocal
	_asm mov retv, eax
	return retv;
}


int Sounds::install(SignatureScanner &, module) {
	DWORD addrConstructDSSound = Hooks::scanPattern("ConstructDSSound", "\x53\x56\x8B\xF0\x33\xDB\x57\x33\xC0\xC7\x06\x00\x00\x00\x00\x89\x5E\x08\x89\x5E\x10\x89\x5E\x0C\x89\x9E\x00\x00\x00\x00\xC7\x86\x00\x00\x00\x00\x00\x00\x00\x00\x8D\xBE\x00\x00\x00\x00\xB9\x00\x00\x00\x00\xF3\xAB\x8B\xC6\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xB8\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00", "??????xxxxx????xxxxxxxxxxx????xx????????xx????x????xxxxx????x????x????xx????", 0x573D50);
	addrPlaySoundLocal = Hooks::scanPattern("PlaySoundLocal", "\x8B\x54\x24\x08\x56\x50\x8B\x44\x24\x0C\x51\x52\x50\x8B\xCF\x8D\xB7\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xC0\x74\x50\x8B\x57\x2C\x8B\x82\x00\x00\x00\x00\x83\xE8\x01\x8D\x0C\xC0\x03\xC9", "??????xxxxxxxxxxx????x????xxxxxxxxx????xxxxxxxx", 0x4FDFE0);
	DWORD addrPlaySoundGlobal = Hooks::scanPattern("addrPlaySoundGlobal", "\x8B\x51\x2C\x8B\x82\x00\x00\x00\x00\x83\xF8\x10\x7C\x05\x33\xC0\xC2\x10\x00\x83\x7A\x08\x00\x74\xF5\x8D\x04\xC0\x56\x8B\x74\x24\x08\x03\xC0\x03\xC0\x89\xB4\x10\x00\x00\x00\x00", "?????????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????", 0x546E20);
	DWORD addrDSSound_vtable = *(DWORD*)(addrConstructDSSound + 0xB);
	DWORD addrLoadGameSoundFromFile = *(DWORD*)(addrDSSound_vtable + 0x30);
	Hooks::polyhook("LoadGameSoundFromFile", addrLoadGameSoundFromFile, (DWORD *) &hookLoadGameSoundFromFile, (DWORD *) &origLoadGameSoundFromFile);

	auto * lua = Lua::getInstance().getState();
	lua->set_function("registerCustomSound", &registerCustomSound);
	lua->set_function("playSoundLocal", &callPlaySoundLocal);

	return 0;
}
