#include "CTaskCloud.h"
#include "../../Lua.h"

#include <sol/sol.hpp>
#include "../../Hooks.h"

int CTaskCloud::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskCloud =  Hooks::scanPattern("ConstructCTaskCloud", "\x8B\x48\x2C\x53\x8B\x5C\x24\x10\x51\x50\x56\xE8\x00\x00\x00\x00\x8B\x44\x24\x0C\x8B\x54\x24\x14\x89\x5E\x40\x03\xDF\x81\xE3\x00\x00\x00\x00\x89\x46\x30", "??????xxxxxx????xxxxxxxxxxxxxxx????xxx", 0x5482E0);
	DWORD *addrCTaskCloudVTable = *(DWORD **) (addrConstructCTaskCloud + 0x33);

	CTaskAddVTHooks(CTaskCloud, addrCTaskCloudVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype<CTaskCloud> ut = lua->new_usertype<CTaskCloud>("CTaskCloud", sol::base_classes, sol::bases<CTask>());
	CTaskAddLuaVTHooks(CTaskCloud);

	ut["unknown30"] = &CTaskCloud::unknown30;
	ut["unknown34"] = &CTaskCloud::unknown34;
	ut["unknown38"] = &CTaskCloud::unknown38;
	ut["unknown3C"] = &CTaskCloud::unknown3C;
	ut["unknown40"] = &CTaskCloud::unknown40;
	ut["unknown44"] = &CTaskCloud::unknown44;
	ut["unknown48"] = &CTaskCloud::unknown48;
	ut["unknown4C"] = &CTaskCloud::unknown4C;
	ut["unknown50"] = &CTaskCloud::unknown50;
	ut["unknown54"] = &CTaskCloud::unknown54;
	ut["unknown58"] = &CTaskCloud::unknown58;
	ut["unknown5C"] = &CTaskCloud::unknown5C;
	ut["unknown60"] = &CTaskCloud::unknown60;
	ut["unknown64"] = &CTaskCloud::unknown64;
	ut["unknown68"] = &CTaskCloud::unknown68;
	ut["unknown6C"] = &CTaskCloud::unknown6C;
	ut["unknown70"] = &CTaskCloud::unknown70;
	return 0;
}
