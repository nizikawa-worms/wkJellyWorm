
#include "../Lua.h"
#include <sol/sol.hpp>
#include "../Hooks.h"
#include "CTask.h"


DWORD *(__stdcall *origConstructCTask)(DWORD *This, int a2, int a3);
DWORD *__stdcall CTask::hookConstructCTask(DWORD *This, int a2, int a3) {
	return origConstructCTask(This, a2, a3);
}

CTask * (__fastcall *origGetHashStoreObject)(int a1, int a2, CTask * This);
CTask *CTask::callGetHashStoreObject(int a1, int a2, CTask *This) {
	return origGetHashStoreObject(a1, a2, This);
}

int CTask::install(SignatureScanner &signatureScanner, module mod) {
	auto * lua = Lua::getInstance().getState();

	sol::usertype <CTask> ut = lua->new_usertype <CTask> ("CTask");
	ut["parent"] = &CTask::parent;
	ut["children"] = &CTask::children;
	ut["unknown1C"] = &CTask::unknown1C;
	ut["classtype"] = &CTask::classtype;
	ut["unknown24"] = &CTask::unknown24;
	ut["unknown28"] = &CTask::unknown28;
	ut["unknown2C"] = &CTask::unknown2C;

	ut["getOffset"] = &CTask::getOffset;
	ut["setOffset"] = &CTask::setOffset;
	ut["getAddr"] = &CTask::getAddr;

	lua->new_usertype<CTaskList>("CTaskList",
	   "iterable", [](CTaskList& ns) { return sol::as_container(ns);},
	   "size", &CTaskList::size,
	   "get", [](CTaskList& ns, int index) { return ns[index-1];}
	);


	DWORD addrConstructCTask =  Hooks::scanPattern("ConstructCTask", "\x64\xA1\x00\x00\x00\x00\x6A\xFF\x68\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x56\x57\x8B\x7C\x24\x18\xC7\x07\x00\x00\x00\x00\x6A\x60\xC7\x47\x00\x00\x00\x00\x00\xC7\x47\x00\x00\x00\x00\x00\xC7\x47\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x6A\x40", "??????xxx????xxxx????xxxxxxxx????xxxx?????xx?????xx?????x????xx", 0x5625A0);
	origGetHashStoreObject = (CTask *(__fastcall *)(int,int,CTask *))Hooks::scanPattern("CTaskGetHashStoreObject", "\x8B\xC1\xC1\xE0\x04\x03\xC2\x03\xC1\x25\x00\x00\x00\x00\x56\x79\x07\x48\x0D\x00\x00\x00\x00\x40\x8B\x74\x24\x08\x8B\x76\x24\x8B\x04\x86\x85\xC0\x5E\x74\x10", "??????xxxx????xxxxx????xxxxxxxxxxxxxxxx", 0x4FDF90);
	DWORD * addrCTaskVTable = *(DWORD**)(addrConstructCTask + 0x1D);

	CTaskAddVTHooks(CTask, addrCTaskVTable)
	CTaskAddLuaVTHooks(CTask)

	Hooks::polyhook("constructCTask", addrConstructCTask, (DWORD *) &hookConstructCTask, (DWORD *) &origConstructCTask);
	lua->set_function("getHashStoreObject", &callGetHashStoreObject);
	return 0;
}

DWORD CTask::getOffset(DWORD offset) {
	return *(DWORD*)(this + offset);
}

void CTask::setOffset(DWORD offset, DWORD value) {
	*(DWORD*)(this + offset) = value;
}

DWORD CTask::getAddr() {
	return (DWORD)this;
}

