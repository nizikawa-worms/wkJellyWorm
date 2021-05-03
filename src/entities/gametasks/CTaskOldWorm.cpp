#include "CTaskOldWorm.h"
#include "../../Lua.h"

#include <sol/sol.hpp>
#include "../../Hooks.h"

int CTaskOldWorm::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskOldWorm =  Hooks::scanPattern("ConstructCTaskOldWorm", "\x6A\xFF\x64\xA1\x00\x00\x00\x00\x68\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x8B\x44\x24\x14\x53\x55\x8B\x6C\x24\x28\x56\x8B\x74\x24\x1C\x57\x6A\x03\x6A\x03", "????????x????xxxx????xxxxxxxxxxxxxxxxxxxx", 0x51FEB0);
	DWORD* addrCTaskOldWormVTable = *(DWORD**)(addrConstructCTaskOldWorm + 0x4F);

	CTaskAddVTHooks(CTaskOldWorm, addrCTaskOldWormVTable)
	CGameTaskAddVTHooks(CTaskOldWorm, addrCTaskOldWormVTable)

	auto * lua = Lua::getInstance().getState();
	sol::usertype <CTaskOldWorm> ut = lua->new_usertype <CTaskOldWorm> ("CTaskOldWorm", sol::base_classes, sol::bases<CGameTask, CTask>());

	CTaskAddLuaVTHooks(CTaskOldWorm)
	CGameTaskAddLuaVTHooks(CTaskOldWorm)

	ut["unknownF0"] = &CTaskOldWorm::unknownF0;
	ut["unknownF4"] = &CTaskOldWorm::unknownF4;
	ut["unknownF8"] = &CTaskOldWorm::unknownF8;
	ut["unknownFC"] = &CTaskOldWorm::unknownFC;
	ut["unknown100"] = &CTaskOldWorm::unknown100;
	ut["unknown104"] = &CTaskOldWorm::unknown104;
	ut["unknown108"] = &CTaskOldWorm::unknown108;
	ut["unknown10C"] = &CTaskOldWorm::unknown10C;
	ut["unknown110"] = &CTaskOldWorm::unknown110;
	ut["unknown114"] = &CTaskOldWorm::unknown114;
	ut["unknown118"] = &CTaskOldWorm::unknown118;
	ut["unknown11C"] = &CTaskOldWorm::unknown11C;
	ut["unknown120"] = &CTaskOldWorm::unknown120;
	ut["unknown124"] = &CTaskOldWorm::unknown124;
	ut["unknown128"] = &CTaskOldWorm::unknown128;
	ut["unknown12C"] = &CTaskOldWorm::unknown12C;
	ut["unknown130"] = &CTaskOldWorm::unknown130;
	ut["unknown134"] = &CTaskOldWorm::unknown134;
	ut["unknown138"] = &CTaskOldWorm::unknown138;
	ut["unknown13C"] = &CTaskOldWorm::unknown13C;
	ut["unknown140"] = &CTaskOldWorm::unknown140;
	ut["unknown144"] = &CTaskOldWorm::unknown144;
	ut["unknown148"] = &CTaskOldWorm::unknown148;
	ut["unknown14C"] = &CTaskOldWorm::unknown14C;
	ut["unknown150"] = &CTaskOldWorm::unknown150;
	ut["unknown154"] = &CTaskOldWorm::unknown154;
	ut["unknown158"] = &CTaskOldWorm::unknown158;
	return 0;
}
