#include "CTaskOildrum.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/Hooks.h>

int CTaskOildrum::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskOildrum =  Hooks::scanPattern("ConstructCTaskOildrum", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x53\x55\x8B\x6C\x24\x20\x56\x8B\x74\x24\x1C\x57\x6A\x09", "???????xx????xxxxxxxx????xxxxxxxxxxxxxx", 0x504AF0);
	DWORD* addrCTaskOildrumVTable = *(DWORD**)(addrConstructCTaskOildrum + 0x42);

	CTaskAddVTHooks(CTaskOildrum, addrCTaskOildrumVTable)
	CGameTaskAddVTHooks(CTaskOildrum, addrCTaskOildrumVTable)

	auto * lua = Lua::getInstance().getState();
	sol::usertype <CTaskOildrum> ut = lua->new_usertype <CTaskOildrum> ("CTaskOildrum", sol::base_classes, sol::bases<CGameTask, CTask>());

	CTaskAddLuaVTHooks(CTaskOildrum)
	CGameTaskAddLuaVTHooks(CTaskOildrum)

	ut["unknownF0"] = &CTaskOildrum::unknownF0;
	ut["unknownF4"] = &CTaskOildrum::unknownF4;
	ut["unknownF8"] = &CTaskOildrum::unknownF8;
	ut["unknownFC"] = &CTaskOildrum::unknownFC;
	ut["unknown100"] = &CTaskOildrum::unknown100;
	ut["unknown104"] = &CTaskOildrum::unknown104;
	ut["unknown108"] = &CTaskOildrum::unknown108;
	ut["unknown10C"] = &CTaskOildrum::unknown10C;

	return 0;
}
