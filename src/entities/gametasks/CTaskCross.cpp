#include "CTaskCross.h"
#include "../../Lua.h"

#include <sol/sol.hpp>
#include "../../Hooks.h"

int CTaskCross::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskCross =   Hooks::scanPattern("ConstructCTaskCross", "\x64\xA1\x00\x00\x00\x00\x6A\xFF\x68\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x53\x56\x8B\x74\x24\x18\x57\x6A\x02", "??????xxx????xxxxxxxx????xxxxxxxxx", 0x5045C0);
	DWORD* addrCTaskCrossVTable = *(DWORD**)(addrConstructCTaskCross + 0x5A);

	CTaskAddVTHooks(CTaskCross, addrCTaskCrossVTable)
	CGameTaskAddVTHooks(CTaskCross, addrCTaskCrossVTable)

	auto * lua = Lua::getInstance().getState();
	sol::usertype <CTaskCross> ut = lua->new_usertype <CTaskCross> ("CTaskCross", sol::base_classes, sol::bases<CGameTask, CTask>());

	CTaskAddLuaVTHooks(CTaskCross)
	CGameTaskAddLuaVTHooks(CTaskCross)

	ut["unknownF0"] = &CTaskCross::unknownF0;
	ut["unknownF4"] = &CTaskCross::unknownF4;
	ut["unknownF8"] = &CTaskCross::unknownF8;
	ut["unknownFC"] = &CTaskCross::unknownFC;
	ut["unknown100"] = &CTaskCross::unknown100;
	ut["unknown104"] = &CTaskCross::unknown104;
	ut["unknown108"] = &CTaskCross::unknown108;
	ut["unknown10C"] = &CTaskCross::unknown10C;
	ut["unknown110"] = &CTaskCross::unknown110;
	ut["unknown114"] = &CTaskCross::unknown114;
	ut["unknown118"] = &CTaskCross::unknown118;
	ut["unknown11C"] = &CTaskCross::unknown11C;
	ut["unknown120"] = &CTaskCross::unknown120;
	ut["unknown124"] = &CTaskCross::unknown124;
	ut["unknown128"] = &CTaskCross::unknown128;
	ut["unknown12C"] = &CTaskCross::unknown12C;
	ut["unknown130"] = &CTaskCross::unknown130;
	ut["unknown134"] = &CTaskCross::unknown134;
	ut["unknown138"] = &CTaskCross::unknown138;
	ut["unknown13C"] = &CTaskCross::unknown13C;

	return 0;
}
