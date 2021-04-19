#include "CTaskFireBall.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/Hooks.h>

int CTaskFireBall::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskFireBall =  Hooks::scanPattern("ConstructCTaskFireBall","\x8B\x48\x2C\x53\x8B\x5C\x24\x08\x55\x8B\x6C\x24\x2C\x56\x57\x51\x50\x53\xE8\x00\x00\x00\x00\x8B\x45\x0C\x8B\x55\x08\x8D\x7B\x3C\xB9\x00\x00\x00\x00", "??????xxxxxxxxxxxxx????xxxxxxxxxx????", 0x550890);
	DWORD *addrCTaskFireBallVTable = *(DWORD **) (addrConstructCTaskFireBall + 0x47);

	CTaskAddVTHooks(CTaskFireBall, addrCTaskFireBallVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype<CTaskFireBall> ut = lua->new_usertype<CTaskFireBall>("CTaskFireBall", sol::base_classes, sol::bases<CTask>());
	CTaskAddLuaVTHooks(CTaskFireBall);
	ut["unknown30"] = &CTaskFireBall::unknown30;
	ut["unknown34"] = &CTaskFireBall::unknown34;
	ut["unknown38"] = &CTaskFireBall::unknown38;
	ut["unknown3C"] = &CTaskFireBall::unknown3C;
	ut["unknown40"] = &CTaskFireBall::unknown40;
	ut["unknown44"] = &CTaskFireBall::unknown44;
	ut["unknown48"] = &CTaskFireBall::unknown48;
	ut["unknown4C"] = &CTaskFireBall::unknown4C;
	ut["unknown50"] = &CTaskFireBall::unknown50;
	ut["unknown54"] = &CTaskFireBall::unknown54;
	ut["unknown58"] = &CTaskFireBall::unknown58;
	ut["unknown5C"] = &CTaskFireBall::unknown5C;
	ut["unknown60"] = &CTaskFireBall::unknown60;
	ut["unknown64"] = &CTaskFireBall::unknown64;
	ut["unknown68"] = &CTaskFireBall::unknown68;
	ut["unknown6C"] = &CTaskFireBall::unknown6C;
	ut["unknown70"] = &CTaskFireBall::unknown70;
	ut["unknown74"] = &CTaskFireBall::unknown74;
	ut["unknown78"] = &CTaskFireBall::unknown78;
	ut["unknown7C"] = &CTaskFireBall::unknown7C;
	ut["unknown80"] = &CTaskFireBall::unknown80;
	ut["unknown84"] = &CTaskFireBall::unknown84;
	ut["unknown88"] = &CTaskFireBall::unknown88;
	ut["unknown8C"] = &CTaskFireBall::unknown8C;
	ut["unknown90"] = &CTaskFireBall::unknown90;
	ut["unknown94"] = &CTaskFireBall::unknown94;
	ut["unknown98"] = &CTaskFireBall::unknown98;
	ut["unknown9C"] = &CTaskFireBall::unknown9C;
	ut["unknownA0"] = &CTaskFireBall::unknownA0;

	return 0;
}
