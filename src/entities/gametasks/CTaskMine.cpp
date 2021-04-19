#include "CTaskMine.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/Hooks.h>

int CTaskMine::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskMine =  Hooks::scanPattern("ConstructCTaskMine", "\x6A\xFF\x64\xA1\x00\x00\x00\x00\x68\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x53\x8B\x5C\x24\x14\x55\x8B\x6C\x24\x24\x56\x57\x6A\x02\x6A\x0A", "????????x????xxxxxxxx????xxxxxxxxxxxxxxxx", 0x506660);
	DWORD* addrCTaskMineVTable = *(DWORD**)(addrConstructCTaskMine + 0x49);

	CTaskAddVTHooks(CTaskMine, addrCTaskMineVTable)
	CGameTaskAddVTHooks(CTaskMine, addrCTaskMineVTable)

	auto * lua = Lua::getInstance().getState();
	sol::usertype <CTaskMine> ut = lua->new_usertype <CTaskMine> ("CTaskMine", sol::base_classes, sol::bases<CGameTask, CTask>());

	CTaskAddLuaVTHooks(CTaskMine)
	CGameTaskAddLuaVTHooks(CTaskMine)

	ut["unknownF0"] = &CTaskMine::unknownF0;
	ut["unknownF4"] = &CTaskMine::unknownF4;
	ut["unknownF8"] = &CTaskMine::unknownF8;
	ut["unknownFC"] = &CTaskMine::unknownFC;
	ut["unknown100"] = &CTaskMine::unknown100;
	ut["unknown104"] = &CTaskMine::unknown104;
	ut["unknown108"] = &CTaskMine::unknown108;
	ut["unknown10C"] = &CTaskMine::unknown10C;
	ut["unknown110"] = &CTaskMine::unknown110;
	ut["unknown114"] = &CTaskMine::unknown114;
	ut["unknown118"] = &CTaskMine::unknown118;
	ut["unknown11C"] = &CTaskMine::unknown11C;
	ut["unknown120"] = &CTaskMine::unknown120;
	ut["unknown124"] = &CTaskMine::unknown124;
	ut["unknown128"] = &CTaskMine::unknown128;
	ut["unknown12C"] = &CTaskMine::unknown12C;
	ut["unknown130"] = &CTaskMine::unknown130;
	ut["unknown134"] = &CTaskMine::unknown134;
	ut["unknown138"] = &CTaskMine::unknown138;
	ut["unknown13C"] = &CTaskMine::unknown13C;
	ut["unknown140"] = &CTaskMine::unknown140;
	ut["unknown144"] = &CTaskMine::unknown144;
	ut["unknown148"] = &CTaskMine::unknown148;
	ut["unknown14C"] = &CTaskMine::unknown14C;
	ut["unknown150"] = &CTaskMine::unknown150;
	ut["unknown154"] = &CTaskMine::unknown154;
	ut["unknown158"] = &CTaskMine::unknown158;
	ut["unknown15C"] = &CTaskMine::unknown15C;
	ut["unknown160"] = &CTaskMine::unknown160;
	ut["unknown164"] = &CTaskMine::unknown164;
	ut["unknown168"] = &CTaskMine::unknown168;
	ut["unknown16C"] = &CTaskMine::unknown16C;
	ut["unknown170"] = &CTaskMine::unknown170;
	ut["unknown174"] = &CTaskMine::unknown174;
	ut["unknown178"] = &CTaskMine::unknown178;
	ut["unknown17C"] = &CTaskMine::unknown17C;
	ut["unknown180"] = &CTaskMine::unknown180;
	ut["unknown184"] = &CTaskMine::unknown184;
	ut["unknown188"] = &CTaskMine::unknown188;
	ut["unknown18C"] = &CTaskMine::unknown18C;
	ut["unknown190"] = &CTaskMine::unknown190;
	ut["unknown194"] = &CTaskMine::unknown194;

	return 0;
}
