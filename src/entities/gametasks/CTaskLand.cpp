#include "CTaskLand.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/Hooks.h>

int CTaskLand::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskLand =  Hooks::scanPattern("ConstructCTaskLand", "\x64\xA1\x00\x00\x00\x00\x6A\xFF\x68\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x53\x55\x56\x8B\x74\x24\x1C\x57\xBD\x00\x00\x00\x00\x55\x55\x50\x56\xE8\x00\x00\x00\x00\x33\xDB", "??????xxx????xxxxxxxx????xxxxxxxxx????xxxxx????xx", 0x505440);
	DWORD* addrCTaskLandVTable = *(DWORD**)(addrConstructCTaskLand + 0x3A);

	CTaskAddVTHooks(CTaskLand, addrCTaskLandVTable)
	CGameTaskAddVTHooks(CTaskLand, addrCTaskLandVTable)

	auto * lua = Lua::getInstance().getState();
	sol::usertype <CTaskLand> ut = lua->new_usertype <CTaskLand> ("CTaskLand", sol::base_classes, sol::bases<CGameTask, CTask>());

	CTaskAddLuaVTHooks(CTaskLand)
	CGameTaskAddLuaVTHooks(CTaskLand)

	ut["unknownF0"] = &CTaskLand::unknownF0;
	ut["unknownF4"] = &CTaskLand::unknownF4;
	ut["unknownF8"] = &CTaskLand::unknownF8;
	ut["unknownFC"] = &CTaskLand::unknownFC;
	ut["unknown100"] = &CTaskLand::unknown100;
	ut["unknown104"] = &CTaskLand::unknown104;
	ut["unknown108"] = &CTaskLand::unknown108;
	return 0;
}
