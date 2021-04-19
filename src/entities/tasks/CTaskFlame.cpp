#include "CTaskFlame.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/Hooks.h>


int CTaskFlame::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskFlame =  Hooks::scanPattern("ConstructCTaskFlame", "\x8B\x48\x2C\x51\x50\x56\xE8\x00\x00\x00\x00\x8B\x46\x2C\x8B\x57\x10\x33\xC9\xC7\x06\x00\x00\x00\x00\xC7\x46\x00\x00\x00\x00\x00\x83\x80\x00\x00\x00\x00\x00\x8B\x47\x14\x89\x4E\x38\x89\x4E\x30", "??????x????xxxxxxxxxx????xx?????xx?????xxxxxxxxx", 0x54F0F0);
	DWORD *addrCTaskFlameVTable = *(DWORD **) (addrConstructCTaskFlame + 0x15);

	CTaskAddVTHooks(CTaskFlame, addrCTaskFlameVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype <CTaskFlame> ut = lua->new_usertype<CTaskFlame>("CTaskFlame", sol::base_classes, sol::bases<CTask>());

	CTaskAddLuaVTHooks(CTaskFlame);
	ut["unknown30"] = &CTaskFlame::unknown30;
	ut["unknown34"] = &CTaskFlame::unknown34;
	ut["unknown38"] = &CTaskFlame::unknown38;
	ut["unknown3C"] = &CTaskFlame::unknown3C;
	ut["unknown40"] = &CTaskFlame::unknown40;
	ut["unknown44"] = &CTaskFlame::unknown44;
	ut["unknown48"] = &CTaskFlame::unknown48;
	ut["unknown4C"] = &CTaskFlame::unknown4C;
	ut["unknown50"] = &CTaskFlame::unknown50;
	ut["unknown54"] = &CTaskFlame::unknown54;
	ut["unknown58"] = &CTaskFlame::unknown58;
	ut["unknown5C"] = &CTaskFlame::unknown5C;
	ut["unknown60"] = &CTaskFlame::unknown60;
	ut["unknown64"] = &CTaskFlame::unknown64;
	ut["unknown68"] = &CTaskFlame::unknown68;
	ut["unknown6C"] = &CTaskFlame::unknown6C;
	ut["unknown70"] = &CTaskFlame::unknown70;
	return 0;
}
