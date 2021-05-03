#include "CTaskCPU.h"
#include "../../Lua.h"

#include <sol/sol.hpp>
#include "../../Hooks.h"

int CTaskCPU::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskCPU =  Hooks::scanPattern("ConstructCTaskCPU", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x53\x8B\x5C\x24\x1C\x55\x56\x8B\x74\x24\x1C\x57\x8B\xF9\x8B\x48\x2C\x51\x50\x56\xE8\x00\x00\x00\x00\x33\xED", "???????xx????xxxxxxxx????xxxxxxxxxxxxxxxxxxxxx????xx", 0x5485D0);
	DWORD *addrCTaskCPUVTable = *(DWORD **) (addrConstructCTaskCPU + 0x56);

	CTaskAddVTHooks(CTaskCPU, addrCTaskCPUVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype<CTaskCPU> ut = lua->new_usertype<CTaskCPU>("CTaskCPU", sol::base_classes, sol::bases<CTask>());
	CTaskAddLuaVTHooks(CTaskCPU);
	ut["unknown"] = &CTaskCPU::unknown;
	return 0;
}
