#include "CTaskArrow.h"
#include "../../Lua.h"
#include <sol/sol.hpp>
#include "../../Hooks.h"


int CTaskArrow::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskArrow =   Hooks::scanPattern("ConstructCTaskArrow", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\x8B\x84\x24\x00\x00\x00\x00\x53\x8B\x9C\x24\x00\x00\x00\x00\x55", "???????xx????xxxx????xx????xxx????xxxx????x", 0x4FE130);
	DWORD* addrCTaskArrowVTable = *(DWORD**)(addrConstructCTaskArrow + 0x52);

	CTaskAddVTHooks(CTaskArrow, addrCTaskArrowVTable)
	CGameTaskAddVTHooks(CTaskArrow, addrCTaskArrowVTable)
	auto * lua = Lua::getInstance().getState();
	sol::usertype <CTaskArrow> ut = lua->new_usertype <CTaskArrow> ("CTaskArrow", sol::base_classes, sol::bases<CGameTask, CTask>());
	CTaskAddLuaVTHooks(CTaskArrow)
	CGameTaskAddLuaVTHooks(CTaskArrow)

	ut["unknownF0"] = &CTaskArrow::unknownF0;
	ut["unknownF4"] = &CTaskArrow::unknownF4;
	ut["unknownF8"] = &CTaskArrow::unknownF8;
	ut["unknownFC"] = &CTaskArrow::unknownFC;
	ut["unknown100"] = &CTaskArrow::unknown100;
	ut["unknown104"] = &CTaskArrow::unknown104;
	ut["unknown108"] = &CTaskArrow::unknown108;
	ut["unknown10C"] = &CTaskArrow::unknown10C;
	ut["unknown110"] = &CTaskArrow::unknown110;
	ut["unknown114"] = &CTaskArrow::unknown114;
	ut["unknown118"] = &CTaskArrow::unknown118;
	ut["unknown11C"] = &CTaskArrow::unknown11C;
	ut["unknown120"] = &CTaskArrow::unknown120;
	ut["unknown124"] = &CTaskArrow::unknown124;
	ut["unknown128"] = &CTaskArrow::unknown128;
	ut["unknown12C"] = &CTaskArrow::unknown12C;
	ut["unknown130"] = &CTaskArrow::unknown130;
	ut["unknown134"] = &CTaskArrow::unknown134;
	ut["unknown138"] = &CTaskArrow::unknown138;
	ut["unknown13C"] = &CTaskArrow::unknown13C;
	ut["unknown140"] = &CTaskArrow::unknown140;
	ut["unknown144"] = &CTaskArrow::unknown144;
	return 0;
}
