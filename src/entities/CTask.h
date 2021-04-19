#ifndef WKJELLYWORM_CTASK_H
#define WKJELLYWORM_CTASK_H


#include <sigscanner.h>
#include <src/Constants.h>
#include "CList.h"
#include <functional>

class CTask;
typedef CList<CTask*> CTaskList;

class CTask {
public:
	virtual int vtable0(int a2) = 0;
	virtual int vtable4_Free(int heap) = 0;
	virtual int vtable8_HandleMessage(CTask * sender, Constants::TaskMessage mtype, size_t size, void * data) = 0;
	virtual int vtableC(int a2, int a3, int a4) = 0;
	virtual int vtable10(int a2, int a3, int a4) = 0;
	virtual int vtable14(int a2) = 0;
	virtual int vtable18() = 0;


	template<typename T> struct CTask_vtableHooks {
		typedef std::function<int(T* This, int a2)> t_vt0;
		typedef std::function<int(T* This, int heap)> t_vt4;
		typedef std::function<int(T* This, CTask * sender, Constants::TaskMessage mtype, size_t size, void * data)> t_vt8;
		typedef std::function<int(T* This, int a2, int a3, int a4)> t_vtC;
		typedef std::function<int(T* This, int a2, int a3, int a4)> t_vt10;
		typedef std::function<int(T* This, int a2)> t_vt14;
		typedef std::function<int(T* This)> t_vt18;
		static const size_t vtNum = 7;

		inline static std::vector<t_vt0> vtable0_callbacks;
		inline static std::vector<t_vt4> vtable4_callbacks;
		inline static std::vector<t_vt8> vtable8_callbacks;
		inline static std::vector<t_vt8> vtable8_builtin_callbacks;
		inline static std::vector<t_vtC> vtableC_callbacks;
		inline static std::vector<t_vt10> vtable10_callbacks;
		inline static std::vector<t_vt14> vtable14_callbacks;
		inline static std::vector<t_vt18> vtable18_callbacks;

		inline static std::array<DWORD, vtNum> vtable_original;

		static void registerCallbackVt0(t_vt0 cb) {vtable0_callbacks.push_back(cb);}
		static void registerCallbackVt4(t_vt4 cb) {vtable4_callbacks.push_back(cb);}
		static void registerCallbackVt8(t_vt8 cb) {vtable8_callbacks.push_back(cb);}
		static void registerBuiltinCallbackVt8(t_vt8 cb) {vtable8_builtin_callbacks.push_back(cb);}
		static void registerCallbackVtC(t_vtC cb) {vtableC_callbacks.push_back(cb);}
		static void registerCallbackVt10(t_vt10 cb) {vtable10_callbacks.push_back(cb);}
		static void registerCallbackVt14(t_vt14 cb) {vtable14_callbacks.push_back(cb);}
		static void registerCallbackVt18(t_vt18 cb) {vtable18_callbacks.push_back(cb);}

		static void clearCallbacks() {
			vtable0_callbacks.clear();
			vtable4_callbacks.clear();
			vtable8_callbacks.clear();
			vtableC_callbacks.clear();
			vtable10_callbacks.clear();
			vtable14_callbacks.clear();
			vtable18_callbacks.clear();
		}

		static int __fastcall hookVtable0(T * This, int EDX, int a2) {
			int ret = 0;
			for(auto & cb : vtable0_callbacks) {
				try {
					ret |= cb(This, a2);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int)>;
				return ((vPtr)vtable_original[0])(This, EDX, a2);
			}
			return 0;
		}
		static int __fastcall hookVtable4(T * This, int EDX, int heap) {
			int ret = 0;
			for(auto & cb : vtable4_callbacks) {
				try {
					ret |= cb(This, heap);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int)>;
				return ((vPtr)vtable_original[1])(This, EDX, heap);
			}
			return 0;
		}
		static int __fastcall hookVtable8(T * This, int EDX, CTask * sender, Constants::TaskMessage mtype, size_t size, void * data) {
			int ret = 0;
			for(auto & cb : vtable8_builtin_callbacks) {
				ret |= cb(This, sender, mtype, size, data);
			}
			for(auto & cb : vtable8_callbacks) {
				try {
					ret |= cb(This, sender, mtype, size, data);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,CTask*,Constants::TaskMessage, size_t, void*)>;
				return ((vPtr)vtable_original[2])(This, EDX, sender, mtype, size, data);
			}
			return 0;
		}
		static int __fastcall hookVtableC(T * This, int EDX, int a2, int a3, int a4) {
			int ret = 0;
			for(auto & cb : vtableC_callbacks) {
				try {
					ret |= cb(This, a2, a3, a4);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int,int,int)>;
				return ((vPtr)vtable_original[3])(This, EDX, a2, a3, a4);
			}
			return 0;
		}
		static int __fastcall hookVtable10(T * This, int EDX, int a2, int a3, int a4) {
			int ret = 0;
			for(auto & cb : vtable10_callbacks) {
				try {
					ret |= cb(This, a2, a3, a4);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int,int,int)>;
				return ((vPtr)vtable_original[4])(This, EDX, a2, a3, a4);
			}
			return 0;
		}
		static int __fastcall hookVtable14(T * This, int EDX, int a2) {
			int ret = 0;
			for(auto & cb : vtable14_callbacks) {
				try {
					ret |= cb(This, a2);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int)>;
				return ((vPtr)vtable_original[5])(This, EDX, a2);
			}
			return 0;
		}
		static int __fastcall hookVtable18(T * This, int EDX) {
			int ret = 0;
			for(auto & cb : vtable18_callbacks) {
				try {
					ret |= cb(This);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int)>;
				return ((vPtr)vtable_original[6])(This, EDX);
			}
			return 0;
		}
	};

	template<typename T>
	static T* castCTask(CTask *task) {
		return (T*)task;
	}

#define CTaskAddVTHooks(classname, vtname) \
	Hooks::hookVtable(#classname, 0x0, (DWORD)&vtname[0], (DWORD)&CTask_vtableHooks<classname>::hookVtable0, &CTask_vtableHooks<classname>::vtable_original[0]); \
	Hooks::hookVtable(#classname, 0x4, (DWORD)&vtname[1], (DWORD)&CTask_vtableHooks<classname>::hookVtable4, &CTask_vtableHooks<classname>::vtable_original[1]); \
	Hooks::hookVtable(#classname, 0x8, (DWORD)&vtname[2], (DWORD)&CTask_vtableHooks<classname>::hookVtable8, &CTask_vtableHooks<classname>::vtable_original[2]); \
	Hooks::hookVtable(#classname, 0xC, (DWORD)&vtname[3], (DWORD)&CTask_vtableHooks<classname>::hookVtableC, &CTask_vtableHooks<classname>::vtable_original[3]); \
	Hooks::hookVtable(#classname, 0x10, (DWORD)&vtname[4], (DWORD)&CTask_vtableHooks<classname>::hookVtable10, &CTask_vtableHooks<classname>::vtable_original[4]); \
	Hooks::hookVtable(#classname, 0x14, (DWORD)&vtname[5], (DWORD)&CTask_vtableHooks<classname>::hookVtable14, &CTask_vtableHooks<classname>::vtable_original[5]); \
	Hooks::hookVtable(#classname, 0x18, (DWORD)&vtname[6], (DWORD)&CTask_vtableHooks<classname>::hookVtable18, &CTask_vtableHooks<classname>::vtable_original[6]);

#define CTaskAddLuaVTHooks(classname) \
	lua->set_function(#classname "_RegisterCallback_vtable0", &CTask_vtableHooks<classname>::registerCallbackVt0); \
	lua->set_function(#classname "_RegisterCallback_vtable4", &CTask_vtableHooks<classname>::registerCallbackVt4); \
	lua->set_function(#classname "_RegisterCallback_vtable8", &CTask_vtableHooks<classname>::registerCallbackVt8); \
	lua->set_function(#classname "_RegisterCallback_vtableC", &CTask_vtableHooks<classname>::registerCallbackVtC); \
	lua->set_function(#classname "_RegisterCallback_vtable10", &CTask_vtableHooks<classname>::registerCallbackVt10); \
	lua->set_function(#classname "_RegisterCallback_vtable14", &CTask_vtableHooks<classname>::registerCallbackVt14); \
	lua->set_function(#classname "_RegisterCallback_vtable18", &CTask_vtableHooks<classname>::registerCallbackVt18); \
	lua->set_function(#classname "_CastCTask", &castCTask<classname>);
	//int vtable;
	CTask * parent; // 0x4

//	int unknown8; // 0x8
//	int unknownC; // 0xC
//	int children_num; // 0x10
//	CTask ** children_ptrs; // 0x14
//	int unknown18; // 0x18
	CTaskList children;

	int unknown1C; // 0x1C
	int classtype; // 0x20
	int unknown24; // 0x24
	int unknown28; // 0x28
	int unknown2C; // 0x2C


	static int install(SignatureScanner & signatureScanner, module mod);
	static DWORD *__stdcall hookConstructCTask(DWORD *This, int a2, int a3);

	static CTask * callGetHashStoreObject(int a1, int a2, CTask * This);
	DWORD getOffset(DWORD offset);
	void setOffset(DWORD offset, DWORD value);
	DWORD getAddr();
};


#endif //WKJELLYWORM_CTASK_H
