#include "CTaskSeaBubble.h"
#include "../../Lua.h"
#include <sol/sol.hpp>
#include "../../Hooks.h"

int CTaskSeaBubble::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskSeaBubble =  Hooks::scanPattern("ConstructCTaskSeaBubble", "\x57\x8B\xF9\x8B\x48\x2C\x51\x50\x56\xE8\x00\x00\x00\x00\x8B\x17\x8B\x46\x2C\x8B\x4F\x08\xC7\x06\x00\x00\x00\x00\xC7\x46\x00\x00\x00\x00\x00", "??????xxxx????xxxxxxxxxx????xx?????", 0x554FE0);
	DWORD *addrCTaskSeaBubbleVTable = *(DWORD **) (addrConstructCTaskSeaBubble + 0x18);

	CTaskAddVTHooks(CTaskSeaBubble, addrCTaskSeaBubbleVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype<CTaskSeaBubble> ut = lua->new_usertype<CTaskSeaBubble>("CTaskSeaBubble", sol::base_classes, sol::bases<CTask>());
	CTaskAddLuaVTHooks(CTaskSeaBubble);
	ut["unknown30"] = &CTaskSeaBubble::unknown30;
	ut["unknown34"] = &CTaskSeaBubble::unknown34;
	ut["unknown38"] = &CTaskSeaBubble::unknown38;
	ut["unknown3C"] = &CTaskSeaBubble::unknown3C;
	ut["unknown40"] = &CTaskSeaBubble::unknown40;
	ut["unknown44"] = &CTaskSeaBubble::unknown44;
	ut["unknown48"] = &CTaskSeaBubble::unknown48;
	ut["unknown4C"] = &CTaskSeaBubble::unknown4C;
	ut["unknown50"] = &CTaskSeaBubble::unknown50;
	ut["unknown54"] = &CTaskSeaBubble::unknown54;
	ut["unknown58"] = &CTaskSeaBubble::unknown58;
	ut["unknown5C"] = &CTaskSeaBubble::unknown5C;
	ut["unknown60"] = &CTaskSeaBubble::unknown60;
	ut["unknown64"] = &CTaskSeaBubble::unknown64;
	ut["unknown68"] = &CTaskSeaBubble::unknown68;
	ut["unknown6C"] = &CTaskSeaBubble::unknown6C;

	return 0;
}
