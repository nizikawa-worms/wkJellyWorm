
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/Config.h>
#include <src/Hooks.h>
#include <src/packages/PackageManager.h>
#include "CGameTask.h"



int (__stdcall *origCGameTaskPhysics)(int a1, CGameTask *a2, int a3);
int __stdcall CGameTask::hookCGameTaskPhysics(int a1, CGameTask *object, int a3) {
	int ret = PackageManager::getInstance().handleCGameTaskPhysics(a1, object, a3);
	if(ret) return ret;
	return origCGameTaskPhysics(a1, object, a3);
}


int CGameTask::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCGameTask =   Hooks::scanPattern("ConstructCGameTask","\x64\xA1\x00\x00\x00\x00\x6A\xFF\x68\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x8B\x48\x2C\x53\x56\x57\x8B\x7C\x24\x1C\x51\x50\x57\xE8\x00\x00\x00\x00\x33\xC0", "??????xxx????xxxxxxxx????xxxxxxxxxxxxxx????x", 0x4FED50);
	DWORD* addrCGameTaskVTable = *(DWORD**)(addrConstructCGameTask + 0x36);
	DWORD addrCGameTaskPhysics =   Hooks::scanPattern("CGameTaskPhysics", "\x83\xEC\x08\x53\x8B\x5C\x24\x14\x83\x7B\x3C\x00\x55\x56\x57\x0F\x84\x00\x00\x00\x00\x83\x7B\x48\x00\x0F\x85\x00\x00\x00\x00\x83\xBB\x00\x00\x00\x00\x00\x8B\x6C\x24\x1C\x7E\x4F", "??????xxxxxxxxxxx????xxxxxx????xx?????xxxxxx", 0x4FCDF0);

	CTaskAddVTHooks(CGameTask, addrCGameTaskVTable)
	CGameTaskAddVTHooks(CGameTask, addrCGameTaskVTable)

	Hooks::minhook("CGameTaskPhysics", addrCGameTaskPhysics, (DWORD*)&hookCGameTaskPhysics, (DWORD*)&origCGameTaskPhysics);

	auto * lua = Lua::getInstance().getState();
	sol::usertype <CGameTask> ut = lua->new_usertype <CGameTask> ("CGameTask", sol::base_classes, sol::bases<CTask>());

	CTaskAddLuaVTHooks(CGameTask)
	CGameTaskAddLuaVTHooks(CGameTask)

	ut["unknown30"] = &CGameTask::unknown30;
	ut["unknown34"] = &CGameTask::unknown34;
	ut["unknown38"] = &CGameTask::unknown38;
	ut["unknown3C"] = &CGameTask::unknown3C;
	ut["unknown40"] = &CGameTask::unknown40;
	ut["unknown44"] = &CGameTask::unknown44;
	ut["unknown48"] = &CGameTask::unknown48;
	ut["unknown4C"] = &CGameTask::unknown4C;
	ut["unknown50"] = &CGameTask::unknown50;
	ut["unknown54"] = &CGameTask::unknown54;
	ut["unknown58"] = &CGameTask::unknown58;
	ut["unknown5C"] = &CGameTask::unknown5C;
	ut["unknown60"] = &CGameTask::unknown60;
	ut["unknown64"] = &CGameTask::unknown64;
	ut["unknown68"] = &CGameTask::unknown68;
	ut["unknown6C"] = &CGameTask::unknown6C;
	ut["unknown70"] = &CGameTask::unknown70;
	ut["unknown74"] = &CGameTask::unknown74;
	ut["unknown78"] = &CGameTask::unknown78;
	ut["unknown7C"] = &CGameTask::unknown7C;
	ut["unknown80"] = &CGameTask::unknown80;
	ut["posX"] = &CGameTask::posX;
	ut["posY"] = &CGameTask::posY;
	ut["unknown8C"] = &CGameTask::unknown8C;
	ut["speedX"] = &CGameTask::speedX;
	ut["speedY"] = &CGameTask::speedY;
	ut["unknown98"] = &CGameTask::unknown98;
	ut["unknown9C"] = &CGameTask::unknown9C;
	ut["unknownA0"] = &CGameTask::unknownA0;
	ut["unknownA4"] = &CGameTask::unknownA4;
	ut["unknownA8"] = &CGameTask::unknownA8;
	ut["unknownAC"] = &CGameTask::unknownAC;
	ut["unknownB0"] = &CGameTask::unknownB0;
	ut["unknownB4"] = &CGameTask::unknownB4;
	ut["unknownB8"] = &CGameTask::unknownB8;
	ut["unknownBC"] = &CGameTask::unknownBC;
	ut["unknownC0"] = &CGameTask::unknownC0;
	ut["unknownC4"] = &CGameTask::unknownC4;
	ut["unknownC8"] = &CGameTask::unknownC8;
	ut["unknownCC"] = &CGameTask::unknownCC;
	ut["unknownD0"] = &CGameTask::unknownD0;
	ut["unknownD4"] = &CGameTask::unknownD4;
	ut["unknownD8"] = &CGameTask::unknownD8;
	ut["unknownDC"] = &CGameTask::unknownDC;
	ut["unknownE0"] = &CGameTask::unknownE0;
	ut["unknownE4"] = &CGameTask::unknownE4;
	ut["unknownE8"] = &CGameTask::unknownE8;
	ut["unknownEC"] = &CGameTask::unknownEC;


	return 0;
}
