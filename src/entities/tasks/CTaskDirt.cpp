#include "CTaskDirt.h"
#include <src/Lua.h>
#include <include/lua/lua.hpp>
#include <include/sol.hpp>
#include <src/Hooks.h>


int CTaskDirt::install(SignatureScanner &signatureScanner, module mod) {
	DWORD addrConstructCTaskDirt =  Hooks::scanPattern("ConstructCTaskDirt",
	"\x64\xA1\x00\x00\x00\x00\x6A\xFF\x68\x00\x00\x00\x00\x50\x8B\x44\x24\x14\x64\x89\x25\x00\x00\x00\x00\x8B\x48\x2C\x53\x56\x8B\x74\x24\x18\x57\x51\x50\x56\xE8\x00\x00\x00\x00\x33\xDB\x89\x5C\x24\x14\x8B\x7E\x24\x6A\x30\xC7\x06\x00\x00\x00\x00\xC7\x46\x00\x00\x00\x00\x00\x89\x9E\x00\x00\x00\x00\xC7\x46\x00\x00\x00\x00\x00\x89\x5E\x18\xE8\x00\x00\x00\x00\x83\xC4\x04\x33\xC9\x89\x08\x89\x48\x04\x89\x48\x08\x89\x48\x0C\x8B\x57\x4C\x8B\x4C\x24\x0C\x89\x58\x08\x89\x70\x0C\x89\x10\xC7\x40",
	"??????xxx????xxxxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxx????xx?????xx????xx?????xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x54EDC0);
	DWORD *addrCTaskDirtVTable = *(DWORD **) (addrConstructCTaskDirt + 0x38);

	CTaskAddVTHooks(CTaskDirt, addrCTaskDirtVTable)

	auto *lua = Lua::getInstance().getState();
	sol::usertype<CTaskDirt> ut = lua->new_usertype<CTaskDirt>("CTaskDirt", sol::base_classes, sol::bases<CTask>());
	CTaskAddLuaVTHooks(CTaskDirt);
	ut["unknown30"] = &CTaskDirt::unknown30;
	ut["unknown34"] = &CTaskDirt::unknown34;
	ut["unknown38"] = &CTaskDirt::unknown38;
	ut["unknown3C"] = &CTaskDirt::unknown3C;
	ut["unknown40"] = &CTaskDirt::unknown40;
	ut["unknown44"] = &CTaskDirt::unknown44;
	ut["unknown48"] = &CTaskDirt::unknown48;
	ut["unknown4C"] = &CTaskDirt::unknown4C;
	ut["unknown50"] = &CTaskDirt::unknown50;
	ut["unknown54"] = &CTaskDirt::unknown54;
	ut["unknown58"] = &CTaskDirt::unknown58;
	ut["unknown5C"] = &CTaskDirt::unknown5C;
	ut["unknown60"] = &CTaskDirt::unknown60;
	ut["unknown64"] = &CTaskDirt::unknown64;
	ut["unknown68"] = &CTaskDirt::unknown68;
	ut["unknown6C"] = &CTaskDirt::unknown6C;
	ut["unknown70"] = &CTaskDirt::unknown70;
	ut["unknown74"] = &CTaskDirt::unknown74;
	ut["unknown78"] = &CTaskDirt::unknown78;
	ut["unknown7C"] = &CTaskDirt::unknown7C;
	ut["unknown80"] = &CTaskDirt::unknown80;
	ut["unknown84"] = &CTaskDirt::unknown84;
	ut["unknown88"] = &CTaskDirt::unknown88;
	ut["unknown8C"] = &CTaskDirt::unknown8C;
	ut["unknown90"] = &CTaskDirt::unknown90;
	ut["unknown94"] = &CTaskDirt::unknown94;
	ut["unknown98"] = &CTaskDirt::unknown98;
	ut["unknown9C"] = &CTaskDirt::unknown9C;
	ut["unknownA0"] = &CTaskDirt::unknownA0;
	ut["unknownA4"] = &CTaskDirt::unknownA4;
	ut["unknownA8"] = &CTaskDirt::unknownA8;
	ut["unknownAC"] = &CTaskDirt::unknownAC;
	ut["unknownB0"] = &CTaskDirt::unknownB0;
	ut["unknownB4"] = &CTaskDirt::unknownB4;
	ut["unknownB8"] = &CTaskDirt::unknownB8;
	ut["unknownBC"] = &CTaskDirt::unknownBC;
	ut["unknownC0"] = &CTaskDirt::unknownC0;
	ut["unknownC4"] = &CTaskDirt::unknownC4;
	ut["unknownC8"] = &CTaskDirt::unknownC8;
	ut["unknownCC"] = &CTaskDirt::unknownCC;
	ut["unknownD0"] = &CTaskDirt::unknownD0;
	ut["unknownD4"] = &CTaskDirt::unknownD4;
	ut["unknownD8"] = &CTaskDirt::unknownD8;
	ut["unknownDC"] = &CTaskDirt::unknownDC;
	ut["unknownE0"] = &CTaskDirt::unknownE0;
	ut["unknownE4"] = &CTaskDirt::unknownE4;
	ut["unknownE8"] = &CTaskDirt::unknownE8;
	ut["unknownEC"] = &CTaskDirt::unknownEC;
	ut["unknownF0"] = &CTaskDirt::unknownF0;
	ut["unknownF4"] = &CTaskDirt::unknownF4;
	ut["unknownF8"] = &CTaskDirt::unknownF8;
	ut["unknownFC"] = &CTaskDirt::unknownFC;
	ut["unknown100"] = &CTaskDirt::unknown100;
	ut["unknown104"] = &CTaskDirt::unknown104;
	ut["unknown108"] = &CTaskDirt::unknown108;
	ut["unknown10C"] = &CTaskDirt::unknown10C;
	ut["unknown110"] = &CTaskDirt::unknown110;
	ut["unknown114"] = &CTaskDirt::unknown114;
	ut["unknown118"] = &CTaskDirt::unknown118;
	ut["unknown11C"] = &CTaskDirt::unknown11C;
	ut["unknown120"] = &CTaskDirt::unknown120;
	ut["unknown124"] = &CTaskDirt::unknown124;
	ut["unknown128"] = &CTaskDirt::unknown128;
	ut["unknown12C"] = &CTaskDirt::unknown12C;
	ut["unknown130"] = &CTaskDirt::unknown130;
	ut["unknown134"] = &CTaskDirt::unknown134;
	ut["unknown138"] = &CTaskDirt::unknown138;
	ut["unknown13C"] = &CTaskDirt::unknown13C;
	ut["unknown140"] = &CTaskDirt::unknown140;
	ut["unknown144"] = &CTaskDirt::unknown144;
	ut["unknown148"] = &CTaskDirt::unknown148;
	ut["unknown14C"] = &CTaskDirt::unknown14C;
	ut["unknown150"] = &CTaskDirt::unknown150;
	ut["unknown154"] = &CTaskDirt::unknown154;
	ut["unknown158"] = &CTaskDirt::unknown158;
	ut["unknown15C"] = &CTaskDirt::unknown15C;
	ut["unknown160"] = &CTaskDirt::unknown160;
	ut["unknown164"] = &CTaskDirt::unknown164;
	ut["unknown168"] = &CTaskDirt::unknown168;
	ut["unknown16C"] = &CTaskDirt::unknown16C;
	ut["unknown170"] = &CTaskDirt::unknown170;
	ut["unknown174"] = &CTaskDirt::unknown174;
	ut["unknown178"] = &CTaskDirt::unknown178;
	ut["unknown17C"] = &CTaskDirt::unknown17C;
	ut["unknown180"] = &CTaskDirt::unknown180;
	ut["unknown184"] = &CTaskDirt::unknown184;
	ut["unknown188"] = &CTaskDirt::unknown188;
	ut["unknown18C"] = &CTaskDirt::unknown18C;
	ut["unknown190"] = &CTaskDirt::unknown190;
	ut["unknown194"] = &CTaskDirt::unknown194;
	ut["unknown198"] = &CTaskDirt::unknown198;
	ut["unknown19C"] = &CTaskDirt::unknown19C;
	ut["unknown1A0"] = &CTaskDirt::unknown1A0;
	ut["unknown1A4"] = &CTaskDirt::unknown1A4;
	ut["unknown1A8"] = &CTaskDirt::unknown1A8;
	ut["unknown1AC"] = &CTaskDirt::unknown1AC;
	ut["unknown1B0"] = &CTaskDirt::unknown1B0;
	ut["unknown1B4"] = &CTaskDirt::unknown1B4;
	ut["unknown1B8"] = &CTaskDirt::unknown1B8;
	ut["unknown1BC"] = &CTaskDirt::unknown1BC;
	ut["unknown1C0"] = &CTaskDirt::unknown1C0;
	ut["unknown1C4"] = &CTaskDirt::unknown1C4;
	ut["unknown1C8"] = &CTaskDirt::unknown1C8;
	ut["unknown1CC"] = &CTaskDirt::unknown1CC;
	ut["unknown1D0"] = &CTaskDirt::unknown1D0;
	ut["unknown1D4"] = &CTaskDirt::unknown1D4;
	ut["unknown1D8"] = &CTaskDirt::unknown1D8;
	ut["unknown1DC"] = &CTaskDirt::unknown1DC;
	ut["unknown1E0"] = &CTaskDirt::unknown1E0;
	ut["unknown1E4"] = &CTaskDirt::unknown1E4;
	ut["unknown1E8"] = &CTaskDirt::unknown1E8;
	ut["unknown1EC"] = &CTaskDirt::unknown1EC;
	ut["unknown1F0"] = &CTaskDirt::unknown1F0;
	ut["unknown1F4"] = &CTaskDirt::unknown1F4;
	ut["unknown1F8"] = &CTaskDirt::unknown1F8;
	ut["unknown1FC"] = &CTaskDirt::unknown1FC;
	ut["unknown200"] = &CTaskDirt::unknown200;
	ut["unknown204"] = &CTaskDirt::unknown204;
	ut["unknown208"] = &CTaskDirt::unknown208;
	ut["unknown20C"] = &CTaskDirt::unknown20C;
	ut["unknown210"] = &CTaskDirt::unknown210;
	ut["unknown214"] = &CTaskDirt::unknown214;
	ut["unknown218"] = &CTaskDirt::unknown218;
	ut["unknown21C"] = &CTaskDirt::unknown21C;
	ut["unknown220"] = &CTaskDirt::unknown220;
	ut["unknown224"] = &CTaskDirt::unknown224;
	ut["unknown228"] = &CTaskDirt::unknown228;
	ut["unknown22C"] = &CTaskDirt::unknown22C;
	ut["unknown230"] = &CTaskDirt::unknown230;
	ut["unknown234"] = &CTaskDirt::unknown234;
	ut["unknown238"] = &CTaskDirt::unknown238;
	ut["unknown23C"] = &CTaskDirt::unknown23C;
	ut["unknown240"] = &CTaskDirt::unknown240;
	ut["unknown244"] = &CTaskDirt::unknown244;
	ut["unknown248"] = &CTaskDirt::unknown248;
	ut["unknown24C"] = &CTaskDirt::unknown24C;
	ut["unknown250"] = &CTaskDirt::unknown250;
	ut["unknown254"] = &CTaskDirt::unknown254;
	ut["unknown258"] = &CTaskDirt::unknown258;
	ut["unknown25C"] = &CTaskDirt::unknown25C;
	ut["unknown260"] = &CTaskDirt::unknown260;
	ut["unknown264"] = &CTaskDirt::unknown264;
	ut["unknown268"] = &CTaskDirt::unknown268;
	ut["unknown26C"] = &CTaskDirt::unknown26C;
	ut["unknown270"] = &CTaskDirt::unknown270;
	ut["unknown274"] = &CTaskDirt::unknown274;
	ut["unknown278"] = &CTaskDirt::unknown278;
	ut["unknown27C"] = &CTaskDirt::unknown27C;
	ut["unknown280"] = &CTaskDirt::unknown280;
	ut["unknown284"] = &CTaskDirt::unknown284;
	ut["unknown288"] = &CTaskDirt::unknown288;
	ut["unknown28C"] = &CTaskDirt::unknown28C;
	ut["unknown290"] = &CTaskDirt::unknown290;
	ut["unknown294"] = &CTaskDirt::unknown294;
	ut["unknown298"] = &CTaskDirt::unknown298;
	ut["unknown29C"] = &CTaskDirt::unknown29C;
	ut["unknown2A0"] = &CTaskDirt::unknown2A0;
	ut["unknown2A4"] = &CTaskDirt::unknown2A4;
	ut["unknown2A8"] = &CTaskDirt::unknown2A8;
	ut["unknown2AC"] = &CTaskDirt::unknown2AC;
	ut["unknown2B0"] = &CTaskDirt::unknown2B0;
	ut["unknown2B4"] = &CTaskDirt::unknown2B4;
	ut["unknown2B8"] = &CTaskDirt::unknown2B8;
	ut["unknown2BC"] = &CTaskDirt::unknown2BC;
	ut["unknown2C0"] = &CTaskDirt::unknown2C0;
	ut["unknown2C4"] = &CTaskDirt::unknown2C4;
	ut["unknown2C8"] = &CTaskDirt::unknown2C8;
	ut["unknown2CC"] = &CTaskDirt::unknown2CC;
	ut["unknown2D0"] = &CTaskDirt::unknown2D0;
	ut["unknown2D4"] = &CTaskDirt::unknown2D4;
	ut["unknown2D8"] = &CTaskDirt::unknown2D8;
	ut["unknown2DC"] = &CTaskDirt::unknown2DC;
	ut["unknown2E0"] = &CTaskDirt::unknown2E0;
	ut["unknown2E4"] = &CTaskDirt::unknown2E4;
	ut["unknown2E8"] = &CTaskDirt::unknown2E8;
	ut["unknown2EC"] = &CTaskDirt::unknown2EC;
	ut["unknown2F0"] = &CTaskDirt::unknown2F0;
	ut["unknown2F4"] = &CTaskDirt::unknown2F4;
	ut["unknown2F8"] = &CTaskDirt::unknown2F8;
	ut["unknown2FC"] = &CTaskDirt::unknown2FC;
	ut["unknown300"] = &CTaskDirt::unknown300;
	ut["unknown304"] = &CTaskDirt::unknown304;
	ut["unknown308"] = &CTaskDirt::unknown308;
	ut["unknown30C"] = &CTaskDirt::unknown30C;
	ut["unknown310"] = &CTaskDirt::unknown310;
	ut["unknown314"] = &CTaskDirt::unknown314;
	ut["unknown318"] = &CTaskDirt::unknown318;
	ut["unknown31C"] = &CTaskDirt::unknown31C;
	ut["unknown320"] = &CTaskDirt::unknown320;
	ut["unknown324"] = &CTaskDirt::unknown324;
	ut["unknown328"] = &CTaskDirt::unknown328;
	ut["unknown32C"] = &CTaskDirt::unknown32C;
	ut["unknown330"] = &CTaskDirt::unknown330;
	ut["unknown334"] = &CTaskDirt::unknown334;
	ut["unknown338"] = &CTaskDirt::unknown338;
	ut["unknown33C"] = &CTaskDirt::unknown33C;
	ut["unknown340"] = &CTaskDirt::unknown340;
	ut["unknown344"] = &CTaskDirt::unknown344;
	ut["unknown348"] = &CTaskDirt::unknown348;
	ut["unknown34C"] = &CTaskDirt::unknown34C;
	ut["unknown350"] = &CTaskDirt::unknown350;
	ut["unknown354"] = &CTaskDirt::unknown354;
	ut["unknown358"] = &CTaskDirt::unknown358;
	ut["unknown35C"] = &CTaskDirt::unknown35C;
	ut["unknown360"] = &CTaskDirt::unknown360;
	ut["unknown364"] = &CTaskDirt::unknown364;
	ut["unknown368"] = &CTaskDirt::unknown368;
	ut["unknown36C"] = &CTaskDirt::unknown36C;
	ut["unknown370"] = &CTaskDirt::unknown370;
	ut["unknown374"] = &CTaskDirt::unknown374;
	ut["unknown378"] = &CTaskDirt::unknown378;
	ut["unknown37C"] = &CTaskDirt::unknown37C;
	ut["unknown380"] = &CTaskDirt::unknown380;
	ut["unknown384"] = &CTaskDirt::unknown384;
	ut["unknown388"] = &CTaskDirt::unknown388;
	ut["unknown38C"] = &CTaskDirt::unknown38C;
	ut["unknown390"] = &CTaskDirt::unknown390;
	ut["unknown394"] = &CTaskDirt::unknown394;
	ut["unknown398"] = &CTaskDirt::unknown398;
	ut["unknown39C"] = &CTaskDirt::unknown39C;
	ut["unknown3A0"] = &CTaskDirt::unknown3A0;
	ut["unknown3A4"] = &CTaskDirt::unknown3A4;
	ut["unknown3A8"] = &CTaskDirt::unknown3A8;
	ut["unknown3AC"] = &CTaskDirt::unknown3AC;
	ut["unknown3B0"] = &CTaskDirt::unknown3B0;
	ut["unknown3B4"] = &CTaskDirt::unknown3B4;
	ut["unknown3B8"] = &CTaskDirt::unknown3B8;
	ut["unknown3BC"] = &CTaskDirt::unknown3BC;
	ut["unknown3C0"] = &CTaskDirt::unknown3C0;
	ut["unknown3C4"] = &CTaskDirt::unknown3C4;
	ut["unknown3C8"] = &CTaskDirt::unknown3C8;
	ut["unknown3CC"] = &CTaskDirt::unknown3CC;
	ut["unknown3D0"] = &CTaskDirt::unknown3D0;
	ut["unknown3D4"] = &CTaskDirt::unknown3D4;
	ut["unknown3D8"] = &CTaskDirt::unknown3D8;
	ut["unknown3DC"] = &CTaskDirt::unknown3DC;
	ut["unknown3E0"] = &CTaskDirt::unknown3E0;
	ut["unknown3E4"] = &CTaskDirt::unknown3E4;
	ut["unknown3E8"] = &CTaskDirt::unknown3E8;
	ut["unknown3EC"] = &CTaskDirt::unknown3EC;
	ut["unknown3F0"] = &CTaskDirt::unknown3F0;
	ut["unknown3F4"] = &CTaskDirt::unknown3F4;
	ut["unknown3F8"] = &CTaskDirt::unknown3F8;
	ut["unknown3FC"] = &CTaskDirt::unknown3FC;
	ut["unknown400"] = &CTaskDirt::unknown400;
	ut["unknown404"] = &CTaskDirt::unknown404;
	ut["unknown408"] = &CTaskDirt::unknown408;
	ut["unknown40C"] = &CTaskDirt::unknown40C;
	ut["unknown410"] = &CTaskDirt::unknown410;
	ut["unknown414"] = &CTaskDirt::unknown414;
	ut["unknown418"] = &CTaskDirt::unknown418;
	ut["unknown41C"] = &CTaskDirt::unknown41C;
	ut["unknown420"] = &CTaskDirt::unknown420;
	ut["unknown424"] = &CTaskDirt::unknown424;
	ut["unknown428"] = &CTaskDirt::unknown428;
	ut["unknown42C"] = &CTaskDirt::unknown42C;
	ut["unknown430"] = &CTaskDirt::unknown430;
	ut["unknown434"] = &CTaskDirt::unknown434;
	ut["unknown438"] = &CTaskDirt::unknown438;
	ut["unknown43C"] = &CTaskDirt::unknown43C;
	ut["unknown440"] = &CTaskDirt::unknown440;
	ut["unknown444"] = &CTaskDirt::unknown444;
	ut["unknown448"] = &CTaskDirt::unknown448;
	ut["unknown44C"] = &CTaskDirt::unknown44C;
	ut["unknown450"] = &CTaskDirt::unknown450;
	ut["unknown454"] = &CTaskDirt::unknown454;
	ut["unknown458"] = &CTaskDirt::unknown458;
	ut["unknown45C"] = &CTaskDirt::unknown45C;
	ut["unknown460"] = &CTaskDirt::unknown460;
	ut["unknown464"] = &CTaskDirt::unknown464;
	ut["unknown468"] = &CTaskDirt::unknown468;
	ut["unknown46C"] = &CTaskDirt::unknown46C;
	ut["unknown470"] = &CTaskDirt::unknown470;
	ut["unknown474"] = &CTaskDirt::unknown474;
	ut["unknown478"] = &CTaskDirt::unknown478;
	ut["unknown47C"] = &CTaskDirt::unknown47C;
	ut["unknown480"] = &CTaskDirt::unknown480;
	ut["unknown484"] = &CTaskDirt::unknown484;
	ut["unknown488"] = &CTaskDirt::unknown488;
	ut["unknown48C"] = &CTaskDirt::unknown48C;
	ut["unknown490"] = &CTaskDirt::unknown490;
	ut["unknown494"] = &CTaskDirt::unknown494;
	ut["unknown498"] = &CTaskDirt::unknown498;
	ut["unknown49C"] = &CTaskDirt::unknown49C;
	ut["unknown4A0"] = &CTaskDirt::unknown4A0;
	ut["unknown4A4"] = &CTaskDirt::unknown4A4;
	ut["unknown4A8"] = &CTaskDirt::unknown4A8;
	ut["unknown4AC"] = &CTaskDirt::unknown4AC;
	ut["unknown4B0"] = &CTaskDirt::unknown4B0;
	ut["unknown4B4"] = &CTaskDirt::unknown4B4;
	ut["unknown4B8"] = &CTaskDirt::unknown4B8;
	ut["unknown4BC"] = &CTaskDirt::unknown4BC;
	ut["unknown4C0"] = &CTaskDirt::unknown4C0;
	ut["unknown4C4"] = &CTaskDirt::unknown4C4;
	ut["unknown4C8"] = &CTaskDirt::unknown4C8;
	ut["unknown4CC"] = &CTaskDirt::unknown4CC;
	ut["unknown4D0"] = &CTaskDirt::unknown4D0;
	ut["unknown4D4"] = &CTaskDirt::unknown4D4;
	ut["unknown4D8"] = &CTaskDirt::unknown4D8;
	ut["unknown4DC"] = &CTaskDirt::unknown4DC;
	ut["unknown4E0"] = &CTaskDirt::unknown4E0;
	ut["unknown4E4"] = &CTaskDirt::unknown4E4;
	ut["unknown4E8"] = &CTaskDirt::unknown4E8;
	ut["unknown4EC"] = &CTaskDirt::unknown4EC;
	ut["unknown4F0"] = &CTaskDirt::unknown4F0;
	ut["unknown4F4"] = &CTaskDirt::unknown4F4;
	ut["unknown4F8"] = &CTaskDirt::unknown4F8;
	ut["unknown4FC"] = &CTaskDirt::unknown4FC;
	ut["unknown500"] = &CTaskDirt::unknown500;
	ut["unknown504"] = &CTaskDirt::unknown504;
	ut["unknown508"] = &CTaskDirt::unknown508;
	ut["unknown50C"] = &CTaskDirt::unknown50C;
	ut["unknown510"] = &CTaskDirt::unknown510;
	ut["unknown514"] = &CTaskDirt::unknown514;
	ut["unknown518"] = &CTaskDirt::unknown518;
	ut["unknown51C"] = &CTaskDirt::unknown51C;
	ut["unknown520"] = &CTaskDirt::unknown520;
	ut["unknown524"] = &CTaskDirt::unknown524;
	ut["unknown528"] = &CTaskDirt::unknown528;
	ut["unknown52C"] = &CTaskDirt::unknown52C;
	ut["unknown530"] = &CTaskDirt::unknown530;
	ut["unknown534"] = &CTaskDirt::unknown534;
	ut["unknown538"] = &CTaskDirt::unknown538;
	ut["unknown53C"] = &CTaskDirt::unknown53C;
	ut["unknown540"] = &CTaskDirt::unknown540;
	ut["unknown544"] = &CTaskDirt::unknown544;
	ut["unknown548"] = &CTaskDirt::unknown548;
	ut["unknown54C"] = &CTaskDirt::unknown54C;
	ut["unknown550"] = &CTaskDirt::unknown550;
	ut["unknown554"] = &CTaskDirt::unknown554;
	ut["unknown558"] = &CTaskDirt::unknown558;
	ut["unknown55C"] = &CTaskDirt::unknown55C;
	ut["unknown560"] = &CTaskDirt::unknown560;
	ut["unknown564"] = &CTaskDirt::unknown564;
	ut["unknown568"] = &CTaskDirt::unknown568;
	ut["unknown56C"] = &CTaskDirt::unknown56C;
	ut["unknown570"] = &CTaskDirt::unknown570;
	ut["unknown574"] = &CTaskDirt::unknown574;
	ut["unknown578"] = &CTaskDirt::unknown578;
	ut["unknown57C"] = &CTaskDirt::unknown57C;
	ut["unknown580"] = &CTaskDirt::unknown580;
	ut["unknown584"] = &CTaskDirt::unknown584;
	ut["unknown588"] = &CTaskDirt::unknown588;
	ut["unknown58C"] = &CTaskDirt::unknown58C;
	ut["unknown590"] = &CTaskDirt::unknown590;
	ut["unknown594"] = &CTaskDirt::unknown594;
	ut["unknown598"] = &CTaskDirt::unknown598;
	ut["unknown59C"] = &CTaskDirt::unknown59C;
	ut["unknown5A0"] = &CTaskDirt::unknown5A0;
	ut["unknown5A4"] = &CTaskDirt::unknown5A4;
	ut["unknown5A8"] = &CTaskDirt::unknown5A8;
	ut["unknown5AC"] = &CTaskDirt::unknown5AC;
	ut["unknown5B0"] = &CTaskDirt::unknown5B0;
	ut["unknown5B4"] = &CTaskDirt::unknown5B4;
	ut["unknown5B8"] = &CTaskDirt::unknown5B8;
	ut["unknown5BC"] = &CTaskDirt::unknown5BC;
	ut["unknown5C0"] = &CTaskDirt::unknown5C0;
	ut["unknown5C4"] = &CTaskDirt::unknown5C4;
	ut["unknown5C8"] = &CTaskDirt::unknown5C8;
	ut["unknown5CC"] = &CTaskDirt::unknown5CC;
	ut["unknown5D0"] = &CTaskDirt::unknown5D0;
	ut["unknown5D4"] = &CTaskDirt::unknown5D4;
	ut["unknown5D8"] = &CTaskDirt::unknown5D8;
	ut["unknown5DC"] = &CTaskDirt::unknown5DC;
	ut["unknown5E0"] = &CTaskDirt::unknown5E0;
	ut["unknown5E4"] = &CTaskDirt::unknown5E4;
	ut["unknown5E8"] = &CTaskDirt::unknown5E8;
	ut["unknown5EC"] = &CTaskDirt::unknown5EC;
	ut["unknown5F0"] = &CTaskDirt::unknown5F0;
	ut["unknown5F4"] = &CTaskDirt::unknown5F4;
	ut["unknown5F8"] = &CTaskDirt::unknown5F8;
	ut["unknown5FC"] = &CTaskDirt::unknown5FC;
	ut["unknown600"] = &CTaskDirt::unknown600;
	ut["unknown604"] = &CTaskDirt::unknown604;
	ut["unknown608"] = &CTaskDirt::unknown608;
	ut["unknown60C"] = &CTaskDirt::unknown60C;
	ut["unknown610"] = &CTaskDirt::unknown610;
	ut["unknown614"] = &CTaskDirt::unknown614;
	ut["unknown618"] = &CTaskDirt::unknown618;
	ut["unknown61C"] = &CTaskDirt::unknown61C;
	ut["unknown620"] = &CTaskDirt::unknown620;
	ut["unknown624"] = &CTaskDirt::unknown624;
	ut["unknown628"] = &CTaskDirt::unknown628;
	ut["unknown62C"] = &CTaskDirt::unknown62C;
	ut["unknown630"] = &CTaskDirt::unknown630;
	ut["unknown634"] = &CTaskDirt::unknown634;
	ut["unknown638"] = &CTaskDirt::unknown638;
	ut["unknown63C"] = &CTaskDirt::unknown63C;
	ut["unknown640"] = &CTaskDirt::unknown640;
	ut["unknown644"] = &CTaskDirt::unknown644;
	ut["unknown648"] = &CTaskDirt::unknown648;
	ut["unknown64C"] = &CTaskDirt::unknown64C;
	ut["unknown650"] = &CTaskDirt::unknown650;
	return 0;
}