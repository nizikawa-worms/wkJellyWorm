#include "CTaskFire.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/Hooks.h>

int CTaskFire::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskFire =  Hooks::scanPattern("ConstructCTaskFire", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x8B\x48\x2C\x53\x8B\x5C\x24\x1C\x55\x8B\x6C\x24\x18\x56\x57\x51\x50\x55\xE8\x00\x00\x00\x00\x33\xC0", "???????xx????xxxxxxxx????xxxxxxxxxxxxxxxxxxx????xx", 0x54F4C0);
	DWORD *addrCTaskFireTable = *(DWORD **) (addrConstructCTaskFire + 0x39);

	CTaskAddVTHooks(CTaskFire, addrCTaskFireTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype <CTaskFire> ut = lua->new_usertype<CTaskFire>("CTaskFire", sol::base_classes, sol::bases<CTask>());

	CTaskAddLuaVTHooks(CTaskFire);

	ut["unknown30"] = &CTaskFire::unknown30;
	ut["unknown34"] = &CTaskFire::unknown34;
	ut["unknown38"] = &CTaskFire::unknown38;
	ut["unknown3C"] = &CTaskFire::unknown3C;
	ut["unknown40"] = &CTaskFire::unknown40;
	ut["unknown44"] = &CTaskFire::unknown44;
	ut["unknown48"] = &CTaskFire::unknown48;
	ut["unknown4C"] = &CTaskFire::unknown4C;
	ut["unknown50"] = &CTaskFire::unknown50;
	ut["unknown54"] = &CTaskFire::unknown54;
	ut["unknown58"] = &CTaskFire::unknown58;
	ut["unknown5C"] = &CTaskFire::unknown5C;
	ut["unknown60"] = &CTaskFire::unknown60;
	ut["unknown64"] = &CTaskFire::unknown64;
	ut["unknown68"] = &CTaskFire::unknown68;
	ut["unknown6C"] = &CTaskFire::unknown6C;
	ut["unknown70"] = &CTaskFire::unknown70;
	ut["unknown74"] = &CTaskFire::unknown74;
	ut["unknown78"] = &CTaskFire::unknown78;
	ut["unknown7C"] = &CTaskFire::unknown7C;
	ut["unknown80"] = &CTaskFire::unknown80;
	ut["unknown84"] = &CTaskFire::unknown84;
	ut["unknown88"] = &CTaskFire::unknown88;
	ut["unknown8C"] = &CTaskFire::unknown8C;
	ut["unknown90"] = &CTaskFire::unknown90;
	ut["unknown94"] = &CTaskFire::unknown94;
	ut["unknown98"] = &CTaskFire::unknown98;
	ut["unknown9C"] = &CTaskFire::unknown9C;
	ut["unknownA0"] = &CTaskFire::unknownA0;
	ut["unknownA4"] = &CTaskFire::unknownA4;
	ut["unknownA8"] = &CTaskFire::unknownA8;
	ut["unknownAC"] = &CTaskFire::unknownAC;
	ut["unknownB0"] = &CTaskFire::unknownB0;
	ut["unknownB4"] = &CTaskFire::unknownB4;
	ut["unknownB8"] = &CTaskFire::unknownB8;
	ut["unknownBC"] = &CTaskFire::unknownBC;
	ut["unknownC0"] = &CTaskFire::unknownC0;
	ut["unknownC4"] = &CTaskFire::unknownC4;
	ut["unknownC8"] = &CTaskFire::unknownC8;
	ut["unknownCC"] = &CTaskFire::unknownCC;
	ut["unknownD0"] = &CTaskFire::unknownD0;
	ut["unknownD4"] = &CTaskFire::unknownD4;

	return 0;
};