#include "CTaskScoreBubble.h"
#include "../../Lua.h"
#include <sol/sol.hpp>
#include "../../Hooks.h"


int CTaskScoreBubble::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskScoreBubble =  Hooks::scanPattern("ConstructCTaskScoreBubble","\x64\xA1\x00\x00\x00\x00\x6A\xFF\x68\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x8B\x48\x2C\x57\x8B\x7C\x24\x14\x51\x50\x57\xE8\x00\x00\x00\x00\x8B\x44\x24\x20", "??????xxx????xxxxxxxx????xxxxxxxxxxxx????xxxx", 0x554CA0);
	DWORD *addrCTaskScoreBubbleVTable = *(DWORD **) (addrConstructCTaskScoreBubble + 0x53);

	CTaskAddVTHooks(CTaskScoreBubble, addrCTaskScoreBubbleVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype<CTaskScoreBubble> ut = lua->new_usertype<CTaskScoreBubble>("CTaskScoreBubble", sol::base_classes, sol::bases<CTask>());
	CTaskAddLuaVTHooks(CTaskScoreBubble);
	ut["unknown30"] = &CTaskScoreBubble::unknown30;
	ut["unknown34"] = &CTaskScoreBubble::unknown34;
	ut["unknown38"] = &CTaskScoreBubble::unknown38;
	ut["unknown3C"] = &CTaskScoreBubble::unknown3C;
	ut["unknown40"] = &CTaskScoreBubble::unknown40;
	ut["unknown44"] = &CTaskScoreBubble::unknown44;
	ut["unknown48"] = &CTaskScoreBubble::unknown48;
	ut["unknown4C"] = &CTaskScoreBubble::unknown4C;
	ut["unknown50"] = &CTaskScoreBubble::unknown50;
	ut["unknown54"] = &CTaskScoreBubble::unknown54;
	ut["unknown58"] = &CTaskScoreBubble::unknown58;
	ut["unknown5C"] = &CTaskScoreBubble::unknown5C;
	ut["unknown60"] = &CTaskScoreBubble::unknown60;
	ut["unknown64"] = &CTaskScoreBubble::unknown64;
	ut["unknown68"] = &CTaskScoreBubble::unknown68;
	ut["unknown6C"] = &CTaskScoreBubble::unknown6C;
	ut["unknown70"] = &CTaskScoreBubble::unknown70;
	ut["unknown74"] = &CTaskScoreBubble::unknown74;
	ut["unknown78"] = &CTaskScoreBubble::unknown78;

	return 0;
}
