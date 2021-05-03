#include "CTaskSmoke.h"
#include "../../Lua.h"
#include <sol/sol.hpp>
#include "../../Hooks.h"

int CTaskSmoke::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskSmoke =  Hooks::scanPattern("ConstructCTaskSmoke", "\x8B\x48\x2C\x51\x50\x56\xE8\x00\x00\x00\x00\x8B\x46\x2C\xC7\x06\x00\x00\x00\x00\xC7\x46\x00\x00\x00\x00\x00\x83\x80\x00\x00\x00\x00\x00\x8B\x57\x04", "??????x????xxxxx????xx?????xx?????xxx", 0x5551D0);
	DWORD *addrCTaskSmokeVTable = *(DWORD **) (addrConstructCTaskSmoke + 0x10);

	CTaskAddVTHooks(CTaskSmoke, addrCTaskSmokeVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype<CTaskSmoke> ut = lua->new_usertype<CTaskSmoke>("CTaskSmoke", sol::base_classes, sol::bases<CTask>());
	CTaskAddLuaVTHooks(CTaskSmoke);

	ut["unknown30"] = &CTaskSmoke::unknown30;
	ut["unknown34"] = &CTaskSmoke::unknown34;
	ut["unknown38"] = &CTaskSmoke::unknown38;
	ut["unknown3C"] = &CTaskSmoke::unknown3C;
	ut["unknown40"] = &CTaskSmoke::unknown40;
	ut["unknown44"] = &CTaskSmoke::unknown44;
	ut["unknown48"] = &CTaskSmoke::unknown48;
	ut["unknown4C"] = &CTaskSmoke::unknown4C;
	ut["unknown50"] = &CTaskSmoke::unknown50;
	ut["unknown54"] = &CTaskSmoke::unknown54;
	ut["unknown58"] = &CTaskSmoke::unknown58;
	ut["unknown5C"] = &CTaskSmoke::unknown5C;
	ut["unknown60"] = &CTaskSmoke::unknown60;
	ut["unknown64"] = &CTaskSmoke::unknown64;
	ut["unknown68"] = &CTaskSmoke::unknown68;
	ut["unknown6C"] = &CTaskSmoke::unknown6C;
	ut["unknown70"] = &CTaskSmoke::unknown70;
	ut["unknown74"] = &CTaskSmoke::unknown74;

	return 0;
}
