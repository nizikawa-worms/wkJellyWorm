#include <src/Hooks.h>
#include <src/Constants.h>
#include <src/Config.h>
#include "CTaskWorm.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>


//int (__fastcall *origCTaskWormHandleMessage)(CTaskWorm *This, DWORD EDX, int x, Constants::TaskMessage y, int a4, int a5);
//int __fastcall CTaskWorm::hookCTaskWormHandleMessage(CTaskWorm *This, DWORD EDX, int x, Constants::TaskMessage y, int a4, int a5) {
//	for(auto feature : Config::getFeatures()) {
//		if(feature->handleCTaskWormHandleMessage(This, x, y, a4, a5))
//			return 0;
//	}
//	return origCTaskWormHandleMessage(This, EDX, x, y, a4, a5);
//}


int CTaskWorm::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskWorm =   Hooks::scanPattern("ConstructCTaskWorm", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x14\x8B\x44\x24\x28\x53\x55\x8B\x6C\x24\x2C\x56\x57\x6A\x03\x6A\x02\x50\x55\xE8\x00\x00\x00\x00\x8B\x54\x24\x3C\x8B\x74\x24\x44\x69\xD2\x00\x00\x00\x00", "???????xx????xxxx????xxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxx????", 0x50BFB0);
	DWORD * addrCTaskWormVTable = *(DWORD**)(addrConstructCTaskWorm + 0x49);
//	DWORD addrCTaskWormHandleMessage = *(DWORD*)(addrCTaskWormVTable + 8);

	CTaskAddVTHooks(CTaskWorm, addrCTaskWormVTable)
	CGameTaskAddVTHooks(CTaskWorm, addrCTaskWormVTable)

	auto * lua = Lua::getInstance().getState();
	sol::usertype <CTaskWorm> ut = lua->new_usertype <CTaskWorm> ("CTaskWorm", sol::base_classes, sol::bases<CGameTask, CTask>());

	CTaskAddLuaVTHooks(CTaskWorm)
	CGameTaskAddLuaVTHooks(CTaskWorm)

	lua->set_function("CTaskWorm_CastCTask", &castCTask<CTaskWorm>);

	ut["unknownF0"] = &CTaskWorm::unknownF0;
	ut["unknownF4"] = &CTaskWorm::unknownF4;
	ut["unknownF8"] = &CTaskWorm::unknownF8;
	ut["unknownFC"] = &CTaskWorm::unknownFC;
	ut["unknown100"] = &CTaskWorm::unknown100;
	ut["unknown104"] = &CTaskWorm::unknown104;
	ut["unknown108"] = &CTaskWorm::unknown108;
	ut["unknown10C"] = &CTaskWorm::unknown10C;
	ut["unknown110"] = &CTaskWorm::unknown110;
	ut["unknown114"] = &CTaskWorm::unknown114;
	ut["unknown118"] = &CTaskWorm::unknown118;
	ut["unknown11C"] = &CTaskWorm::unknown11C;
	ut["unknown120"] = &CTaskWorm::unknown120;
	ut["unknown124"] = &CTaskWorm::unknown124;
	ut["unknown128"] = &CTaskWorm::unknown128;
	ut["unknown12C"] = &CTaskWorm::unknown12C;
	ut["unknown130"] = &CTaskWorm::unknown130;
	ut["unknown134"] = &CTaskWorm::unknown134;
	ut["unknown138"] = &CTaskWorm::unknown138;
	ut["unknown13C"] = &CTaskWorm::unknown13C;
	ut["unknown140"] = &CTaskWorm::unknown140;
	ut["unknown144"] = &CTaskWorm::unknown144;
	ut["unknown148"] = &CTaskWorm::unknown148;
	ut["unknown14C"] = &CTaskWorm::unknown14C;
	ut["unknown150"] = &CTaskWorm::unknown150;
	ut["unknown154"] = &CTaskWorm::unknown154;
	ut["unknown158"] = &CTaskWorm::unknown158;
	ut["unknown15C"] = &CTaskWorm::unknown15C;
	ut["unknown160"] = &CTaskWorm::unknown160;
	ut["unknown164"] = &CTaskWorm::unknown164;
	ut["unknown168"] = &CTaskWorm::unknown168;
	ut["unknown16C"] = &CTaskWorm::unknown16C;
	ut["unknown170"] = &CTaskWorm::unknown170;
	ut["unknown174"] = &CTaskWorm::unknown174;
	ut["unknown178"] = &CTaskWorm::unknown178;
	ut["unknown17C"] = &CTaskWorm::unknown17C;
	ut["unknown180"] = &CTaskWorm::unknown180;
	ut["unknown184"] = &CTaskWorm::unknown184;
	ut["unknown188"] = &CTaskWorm::unknown188;
	ut["unknown18C"] = &CTaskWorm::unknown18C;
	ut["unknown190"] = &CTaskWorm::unknown190;
	ut["unknown194"] = &CTaskWorm::unknown194;
	ut["unknown198"] = &CTaskWorm::unknown198;
	ut["unknown19C"] = &CTaskWorm::unknown19C;
	ut["unknown1A0"] = &CTaskWorm::unknown1A0;
	ut["unknown1A4"] = &CTaskWorm::unknown1A4;
	ut["unknown1A8"] = &CTaskWorm::unknown1A8;
	ut["unknown1AC"] = &CTaskWorm::unknown1AC;
	ut["unknown1B0"] = &CTaskWorm::unknown1B0;
	ut["unknown1B4"] = &CTaskWorm::unknown1B4;
	ut["unknown1B8"] = &CTaskWorm::unknown1B8;
	ut["unknown1BC"] = &CTaskWorm::unknown1BC;
	ut["unknown1C0"] = &CTaskWorm::unknown1C0;
	ut["unknown1C4"] = &CTaskWorm::unknown1C4;
	ut["unknown1C8"] = &CTaskWorm::unknown1C8;
	ut["unknown1CC"] = &CTaskWorm::unknown1CC;
	ut["unknown1D0"] = &CTaskWorm::unknown1D0;
	ut["unknown1D4"] = &CTaskWorm::unknown1D4;
	ut["unknown1D8"] = &CTaskWorm::unknown1D8;
	ut["unknown1DC"] = &CTaskWorm::unknown1DC;
	ut["unknown1E0"] = &CTaskWorm::unknown1E0;
	ut["unknown1E4"] = &CTaskWorm::unknown1E4;
	ut["unknown1E8"] = &CTaskWorm::unknown1E8;
	ut["unknown1EC"] = &CTaskWorm::unknown1EC;
	ut["unknown1F0"] = &CTaskWorm::unknown1F0;
	ut["unknown1F4"] = &CTaskWorm::unknown1F4;
	ut["unknown1F8"] = &CTaskWorm::unknown1F8;
	ut["unknown1FC"] = &CTaskWorm::unknown1FC;
	ut["unknown200"] = &CTaskWorm::unknown200;
	ut["unknown204"] = &CTaskWorm::unknown204;
	ut["unknown208"] = &CTaskWorm::unknown208;
	ut["unknown20C"] = &CTaskWorm::unknown20C;
	ut["unknown210"] = &CTaskWorm::unknown210;
	ut["unknown214"] = &CTaskWorm::unknown214;
	ut["unknown218"] = &CTaskWorm::unknown218;
	ut["unknown21C"] = &CTaskWorm::unknown21C;
	ut["unknown220"] = &CTaskWorm::unknown220;
	ut["unknown224"] = &CTaskWorm::unknown224;
	ut["unknown228"] = &CTaskWorm::unknown228;
	ut["unknown22C"] = &CTaskWorm::unknown22C;
	ut["unknown230"] = &CTaskWorm::unknown230;
	ut["unknown234"] = &CTaskWorm::unknown234;
	ut["unknown238"] = &CTaskWorm::unknown238;
	ut["unknown23C"] = &CTaskWorm::unknown23C;
	ut["unknown240"] = &CTaskWorm::unknown240;
	ut["unknown244"] = &CTaskWorm::unknown244;
	ut["unknown248"] = &CTaskWorm::unknown248;
	ut["unknown24C"] = &CTaskWorm::unknown24C;
	ut["unknown250"] = &CTaskWorm::unknown250;
	ut["unknown254"] = &CTaskWorm::unknown254;
	ut["unknown258"] = &CTaskWorm::unknown258;
	ut["unknown25C"] = &CTaskWorm::unknown25C;
	ut["unknown260"] = &CTaskWorm::unknown260;
	ut["unknown264"] = &CTaskWorm::unknown264;
	ut["unknown268"] = &CTaskWorm::unknown268;
	ut["unknown26C"] = &CTaskWorm::unknown26C;
	ut["unknown270"] = &CTaskWorm::unknown270;
	ut["unknown274"] = &CTaskWorm::unknown274;
	ut["unknown278"] = &CTaskWorm::unknown278;
	ut["unknown27C"] = &CTaskWorm::unknown27C;
	ut["unknown280"] = &CTaskWorm::unknown280;
	ut["unknown284"] = &CTaskWorm::unknown284;
	ut["unknown288"] = &CTaskWorm::unknown288;
	ut["unknown28C"] = &CTaskWorm::unknown28C;
	ut["unknown290"] = &CTaskWorm::unknown290;
	ut["unknown294"] = &CTaskWorm::unknown294;
	ut["unknown298"] = &CTaskWorm::unknown298;
	ut["unknown29C"] = &CTaskWorm::unknown29C;
	ut["unknown2A0"] = &CTaskWorm::unknown2A0;
	ut["unknown2A4"] = &CTaskWorm::unknown2A4;
	ut["unknown2A8"] = &CTaskWorm::unknown2A8;
	ut["unknown2AC"] = &CTaskWorm::unknown2AC;
	ut["unknown2B0"] = &CTaskWorm::unknown2B0;
	ut["unknown2B4"] = &CTaskWorm::unknown2B4;
	ut["unknown2B8"] = &CTaskWorm::unknown2B8;
	ut["unknown2BC"] = &CTaskWorm::unknown2BC;
	ut["unknown2C0"] = &CTaskWorm::unknown2C0;
	ut["unknown2C4"] = &CTaskWorm::unknown2C4;
	ut["unknown2C8"] = &CTaskWorm::unknown2C8;
	ut["unknown2CC"] = &CTaskWorm::unknown2CC;
	ut["unknown2D0"] = &CTaskWorm::unknown2D0;
	ut["unknown2D4"] = &CTaskWorm::unknown2D4;
	ut["unknown2D8"] = &CTaskWorm::unknown2D8;
	ut["unknown2DC"] = &CTaskWorm::unknown2DC;
	ut["unknown2E0"] = &CTaskWorm::unknown2E0;
	ut["unknown2E4"] = &CTaskWorm::unknown2E4;
	ut["unknown2E8"] = &CTaskWorm::unknown2E8;
	ut["unknown2EC"] = &CTaskWorm::unknown2EC;
	ut["unknown2F0"] = &CTaskWorm::unknown2F0;
	ut["unknown2F4"] = &CTaskWorm::unknown2F4;
	ut["unknown2F8"] = &CTaskWorm::unknown2F8;
	ut["unknown2FC"] = &CTaskWorm::unknown2FC;
	ut["unknown300"] = &CTaskWorm::unknown300;
	ut["unknown304"] = &CTaskWorm::unknown304;
	ut["unknown308"] = &CTaskWorm::unknown308;
	ut["unknown30C"] = &CTaskWorm::unknown30C;
	ut["unknown310"] = &CTaskWorm::unknown310;
	ut["unknown314"] = &CTaskWorm::unknown314;
	ut["unknown318"] = &CTaskWorm::unknown318;
	ut["unknown31C"] = &CTaskWorm::unknown31C;
	ut["unknown320"] = &CTaskWorm::unknown320;
	ut["unknown324"] = &CTaskWorm::unknown324;
	ut["unknown328"] = &CTaskWorm::unknown328;
	ut["unknown32C"] = &CTaskWorm::unknown32C;
	ut["unknown330"] = &CTaskWorm::unknown330;
	ut["unknown334"] = &CTaskWorm::unknown334;
	ut["unknown338"] = &CTaskWorm::unknown338;
	ut["unknown33C"] = &CTaskWorm::unknown33C;
	ut["unknown340"] = &CTaskWorm::unknown340;
	ut["unknown344"] = &CTaskWorm::unknown344;
	ut["unknown348"] = &CTaskWorm::unknown348;
	ut["unknown34C"] = &CTaskWorm::unknown34C;
	ut["unknown350"] = &CTaskWorm::unknown350;
	ut["unknown354"] = &CTaskWorm::unknown354;
	ut["unknown358"] = &CTaskWorm::unknown358;
	ut["unknown35C"] = &CTaskWorm::unknown35C;
	ut["unknown360"] = &CTaskWorm::unknown360;
	ut["unknown364"] = &CTaskWorm::unknown364;
	ut["unknown368"] = &CTaskWorm::unknown368;
	ut["unknown36C"] = &CTaskWorm::unknown36C;
	ut["unknown370"] = &CTaskWorm::unknown370;
	ut["unknown374"] = &CTaskWorm::unknown374;
	ut["unknown378"] = &CTaskWorm::unknown378;
	ut["unknown37C"] = &CTaskWorm::unknown37C;
	ut["unknown380"] = &CTaskWorm::unknown380;
	ut["unknown384"] = &CTaskWorm::unknown384;
	ut["unknown388"] = &CTaskWorm::unknown388;
	ut["unknown38C"] = &CTaskWorm::unknown38C;
	ut["unknown390"] = &CTaskWorm::unknown390;
	ut["unknown394"] = &CTaskWorm::unknown394;
	ut["unknown398"] = &CTaskWorm::unknown398;
	ut["unknown39C"] = &CTaskWorm::unknown39C;
	ut["unknown3A0"] = &CTaskWorm::unknown3A0;
	ut["unknown3A4"] = &CTaskWorm::unknown3A4;
	ut["unknown3A8"] = &CTaskWorm::unknown3A8;
	ut["unknown3AC"] = &CTaskWorm::unknown3AC;
	ut["unknown3B0"] = &CTaskWorm::unknown3B0;
	ut["unknown3B4"] = &CTaskWorm::unknown3B4;
	ut["unknown3B8"] = &CTaskWorm::unknown3B8;
	ut["unknown3BC"] = &CTaskWorm::unknown3BC;
	ut["unknown3C0"] = &CTaskWorm::unknown3C0;
	ut["unknown3C4"] = &CTaskWorm::unknown3C4;
	ut["unknown3C8"] = &CTaskWorm::unknown3C8;
	ut["unknown3CC"] = &CTaskWorm::unknown3CC;
	ut["unknown3D0"] = &CTaskWorm::unknown3D0;
	ut["unknown3D4"] = &CTaskWorm::unknown3D4;
	ut["unknown3D8"] = &CTaskWorm::unknown3D8;
	ut["unknown3DC"] = &CTaskWorm::unknown3DC;
	ut["unknown3E0"] = &CTaskWorm::unknown3E0;
	ut["unknown3E4"] = &CTaskWorm::unknown3E4;
	ut["unknown3E8"] = &CTaskWorm::unknown3E8;
	ut["unknown3EC"] = &CTaskWorm::unknown3EC;
	ut["unknown3F0"] = &CTaskWorm::unknown3F0;
	ut["unknown3F4"] = &CTaskWorm::unknown3F4;
	ut["unknown3F8"] = &CTaskWorm::unknown3F8;
	return 0;
}
