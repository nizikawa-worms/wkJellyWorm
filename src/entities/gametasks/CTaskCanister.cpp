#include "CTaskCanister.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/Hooks.h>

int CTaskCanister::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskCanister =   Hooks::scanPattern("ConstructCCanister", "\x6A\xFF\x64\xA1\x00\x00\x00\x00\x68\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x53\x8B\x5C\x24\x14\x55\x8B\x6C\x24\x24", "????????x????xxxxxxxx????xxxxxxxxxx", 0x501A80);
	DWORD* addrCTaskCanisterVTable = *(DWORD**)(addrConstructCTaskCanister + 0x3C);

	CTaskAddVTHooks(CTaskCanister, addrCTaskCanisterVTable)
	CGameTaskAddVTHooks(CTaskCanister, addrCTaskCanisterVTable)

	auto * lua = Lua::getInstance().getState();
	sol::usertype <CTaskCanister> ut = lua->new_usertype <CTaskCanister> ("CTaskCanister", sol::base_classes, sol::bases<CGameTask, CTask>());

	CTaskAddLuaVTHooks(CTaskCanister)
	CGameTaskAddLuaVTHooks(CTaskCanister)

	ut["unknownF0"] = &CTaskCanister::unknownF0;
	ut["unknownF4"] = &CTaskCanister::unknownF4;
	ut["unknownF8"] = &CTaskCanister::unknownF8;
	ut["unknownFC"] = &CTaskCanister::unknownFC;
	ut["unknown100"] = &CTaskCanister::unknown100;
	ut["unknown104"] = &CTaskCanister::unknown104;
	ut["unknown108"] = &CTaskCanister::unknown108;
	ut["unknown10C"] = &CTaskCanister::unknown10C;
	ut["unknown110"] = &CTaskCanister::unknown110;
	ut["unknown114"] = &CTaskCanister::unknown114;
	ut["unknown118"] = &CTaskCanister::unknown118;
	ut["unknown11C"] = &CTaskCanister::unknown11C;
	ut["unknown120"] = &CTaskCanister::unknown120;
	ut["unknown124"] = &CTaskCanister::unknown124;
	ut["unknown128"] = &CTaskCanister::unknown128;
	ut["unknown12C"] = &CTaskCanister::unknown12C;
	ut["unknown130"] = &CTaskCanister::unknown130;
	ut["unknown134"] = &CTaskCanister::unknown134;
	ut["unknown138"] = &CTaskCanister::unknown138;
	ut["unknown13C"] = &CTaskCanister::unknown13C;
	ut["unknown140"] = &CTaskCanister::unknown140;
	ut["unknown144"] = &CTaskCanister::unknown144;
	ut["unknown148"] = &CTaskCanister::unknown148;
	ut["unknown14C"] = &CTaskCanister::unknown14C;
	ut["unknown150"] = &CTaskCanister::unknown150;
	ut["unknown154"] = &CTaskCanister::unknown154;
	ut["unknown158"] = &CTaskCanister::unknown158;

	return 0;
}
