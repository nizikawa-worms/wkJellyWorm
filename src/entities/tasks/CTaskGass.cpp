#include "CTaskGass.h"
#include "../../Lua.h"

#include <sol/sol.hpp>
#include "../../Hooks.h"

int CTaskGass::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskGass =  Hooks::scanPattern("ConstructCTaskGass","\x8B\x48\x2C\x51\x50\x56\xE8\x00\x00\x00\x00\x8B\x44\x24\x08\x8B\x4E\x2C\x8B\x54\x24\x04\x89\x46\x38\x33\xC0\x89\x46\x3C\x89\x46\x40\x89\x46\x44\x89\x56\x34", "??????x????xxxxxxxxxxxxxxxxxxxxxxxxxxxx", 0x554750);
	DWORD *addrCTaskGassVTable = *(DWORD **) (addrConstructCTaskGass + 0x29);

	CTaskAddVTHooks(CTaskGass, addrCTaskGassVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype<CTaskGass> ut = lua->new_usertype<CTaskGass>("CTaskGass", sol::base_classes, sol::bases<CTask>());
	CTaskAddLuaVTHooks(CTaskGass);

	ut["unknown30"] = &CTaskGass::unknown30;
	ut["unknown34"] = &CTaskGass::unknown34;
	ut["unknown38"] = &CTaskGass::unknown38;
	ut["unknown3C"] = &CTaskGass::unknown3C;
	ut["unknown40"] = &CTaskGass::unknown40;
	ut["unknown44"] = &CTaskGass::unknown44;
	ut["unknown48"] = &CTaskGass::unknown48;
	ut["unknown4C"] = &CTaskGass::unknown4C;
	ut["unknown50"] = &CTaskGass::unknown50;
	ut["unknown54"] = &CTaskGass::unknown54;
	ut["unknown58"] = &CTaskGass::unknown58;
	ut["unknown5C"] = &CTaskGass::unknown5C;
	ut["unknown60"] = &CTaskGass::unknown60;
	ut["unknown64"] = &CTaskGass::unknown64;
	ut["unknown68"] = &CTaskGass::unknown68;
	ut["unknown6C"] = &CTaskGass::unknown6C;
	ut["unknown70"] = &CTaskGass::unknown70;
	ut["unknown74"] = &CTaskGass::unknown74;
	ut["unknown78"] = &CTaskGass::unknown78;
	ut["unknown7C"] = &CTaskGass::unknown7C;
	ut["unknown80"] = &CTaskGass::unknown80;
	ut["unknown84"] = &CTaskGass::unknown84;
	return 0;
}
