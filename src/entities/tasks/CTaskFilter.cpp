#include "CTaskFilter.h"
#include "../../Lua.h"

#include <sol/sol.hpp>
#include "../../Hooks.h"


int CTaskFilter::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskFlame =  Hooks::scanPattern("ConstructCTaskFilter", "\x6A\xFF\x64\xA1\x00\x00\x00\x00\x68\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x53\x8B\x5C\x24\x14\x56\x57\x8B\xF9\x8B\x48\x2C\x51\x50", "????????x????xxxxxxxx????xxxxxxxxxxxxxx", 0x54F3D0);
	DWORD *addrCTaskFlameVTable = *(DWORD **) (addrConstructCTaskFlame + 0x3C);

	CTaskAddVTHooks(CTaskFilter, addrCTaskFlameVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype<CTaskFilter> ut = lua->new_usertype<CTaskFilter>("CTaskFilter", sol::base_classes, sol::bases<CTask>());

	CTaskAddLuaVTHooks(CTaskFilter);

	ut["unknown30"] = &CTaskFilter::unknown30;
	ut["unknown34"] = &CTaskFilter::unknown34;
	ut["unknown38"] = &CTaskFilter::unknown38;
	ut["unknown3C"] = &CTaskFilter::unknown3C;
	ut["unknown40"] = &CTaskFilter::unknown40;
	ut["unknown44"] = &CTaskFilter::unknown44;
	ut["unknown48"] = &CTaskFilter::unknown48;
	ut["unknown4C"] = &CTaskFilter::unknown4C;
	ut["unknown50"] = &CTaskFilter::unknown50;
	ut["unknown54"] = &CTaskFilter::unknown54;
	ut["unknown58"] = &CTaskFilter::unknown58;
	ut["unknown5C"] = &CTaskFilter::unknown5C;
	ut["unknown60"] = &CTaskFilter::unknown60;
	ut["unknown64"] = &CTaskFilter::unknown64;
	ut["unknown68"] = &CTaskFilter::unknown68;
	ut["unknown6C"] = &CTaskFilter::unknown6C;
	ut["unknown70"] = &CTaskFilter::unknown70;
	ut["unknown74"] = &CTaskFilter::unknown74;
	ut["unknown78"] = &CTaskFilter::unknown78;
	ut["unknown7C"] = &CTaskFilter::unknown7C;
	ut["unknown80"] = &CTaskFilter::unknown80;
	ut["unknown84"] = &CTaskFilter::unknown84;
	ut["unknown88"] = &CTaskFilter::unknown88;
	ut["unknown8C"] = &CTaskFilter::unknown8C;
	ut["unknown90"] = &CTaskFilter::unknown90;
	ut["unknown94"] = &CTaskFilter::unknown94;
	ut["unknown98"] = &CTaskFilter::unknown98;
	ut["unknown9C"] = &CTaskFilter::unknown9C;
	ut["unknownA0"] = &CTaskFilter::unknownA0;
	ut["unknownA4"] = &CTaskFilter::unknownA4;
	ut["unknownA8"] = &CTaskFilter::unknownA8;
	ut["unknownAC"] = &CTaskFilter::unknownAC;
	ut["unknownB0"] = &CTaskFilter::unknownB0;

	return 0;
};