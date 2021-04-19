#ifndef WKJELLYWORM_CGAMETASK_H
#define WKJELLYWORM_CGAMETASK_H


#include "CTask.h"

class CGameTask : public CTask {
public:
	virtual int vtable1C(int a2, int a3) = 0;
	virtual int vtable20(int a2, int a3) = 0;
	virtual int vtable24(int a2) = 0;
	virtual int vtable28(int a2) = 0;
	virtual int vtable2C_OnSink(int a2, int a3) = 0;
	virtual int vtable30() = 0;
	virtual int vtable34() = 0;
	virtual int vtable38_SetState(int a2) = 0;
	virtual int vtable3C() = 0;
	virtual int vtable40() = 0;
	virtual int vtable44(int a2, int a3, int a4) = 0;
	virtual int vtable48() = 0;


	template<typename T> struct CGameTask_vtableHooks {
		typedef std::function<int(T* This, int a2, int a3)> t_vt1C;
		typedef std::function<int(T* This, int a2, int a3)> t_vt20;
		typedef std::function<int(T* This, int a2)> t_vt24;
		typedef std::function<int(T* This, int a2)> t_vt28;
		typedef std::function<int(T* This, int a2, int a3)> t_vt2C;
		typedef std::function<int(T* This)> t_vt30;
		typedef std::function<int(T* This)> t_vt34;
		typedef std::function<int(T* This, int a2)> t_vt38;
		typedef std::function<int(T* This)> t_vt3C;
		typedef std::function<int(T* This)> t_vt40;
		typedef std::function<int(T* This, int a2, int a3, int a4)> t_vt44;
		typedef std::function<int(T* This)> t_vt48;

		static const size_t vtNum = 12;
		inline static std::vector<t_vt1C> vtable1C_callbacks;
		inline static std::vector<t_vt20> vtable20_callbacks;
		inline static std::vector<t_vt24> vtable24_callbacks;
		inline static std::vector<t_vt28> vtable28_callbacks;
		inline static std::vector<t_vt2C> vtable2C_callbacks;
		inline static std::vector<t_vt30> vtable30_callbacks;
		inline static std::vector<t_vt34> vtable34_callbacks;
		inline static std::vector<t_vt38> vtable38_callbacks;
		inline static std::vector<t_vt3C> vtable3C_callbacks;
		inline static std::vector<t_vt40> vtable40_callbacks;
		inline static std::vector<t_vt44> vtable44_callbacks;
		inline static std::vector<t_vt48> vtable48_callbacks;

		inline static std::array<DWORD, vtNum> vtable_original;

		static void registerCallbackVt1C(t_vt1C cb) {vtable1C_callbacks.push_back(cb);}
		static void registerCallbackVt20(t_vt20 cb) {vtable20_callbacks.push_back(cb);}
		static void registerCallbackVt24(t_vt24 cb) {vtable24_callbacks.push_back(cb);}
		static void registerCallbackVt28(t_vt28 cb) {vtable28_callbacks.push_back(cb);}
		static void registerCallbackVt2C(t_vt2C cb) {vtable2C_callbacks.push_back(cb);}
		static void registerCallbackVt30(t_vt30 cb) {vtable30_callbacks.push_back(cb);}
		static void registerCallbackVt34(t_vt34 cb) {vtable34_callbacks.push_back(cb);}
		static void registerCallbackVt38(t_vt38 cb) {vtable38_callbacks.push_back(cb);}
		static void registerCallbackVt3C(t_vt3C cb) {vtable3C_callbacks.push_back(cb);}
		static void registerCallbackVt40(t_vt40 cb) {vtable40_callbacks.push_back(cb);}
		static void registerCallbackVt44(t_vt44 cb) {vtable44_callbacks.push_back(cb);}
		static void registerCallbackVt48(t_vt48 cb) {vtable48_callbacks.push_back(cb);}


		static void clearCallbacks() {
			vtable1C_callbacks.clear();
			vtable20_callbacks.clear();
			vtable24_callbacks.clear();
			vtable28_callbacks.clear();
			vtable2C_callbacks.clear();
			vtable30_callbacks.clear();
			vtable34_callbacks.clear();
			vtable38_callbacks.clear();
			vtable3C_callbacks.clear();
			vtable40_callbacks.clear();
			vtable44_callbacks.clear();
			vtable48_callbacks.clear();
		}

		static int __fastcall hookVtable1C(T * This, int EDX, int a2, int a3) {
			int ret = 0;
			for(auto & cb : vtable1C_callbacks) {
				try {
					ret |= cb(This, a2, a3);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int,int)>;
				return ((vPtr)vtable_original[0])(This, EDX, a2, a3);
			}
			return 0;
		}
		static int __fastcall hookVtable20(T * This, int EDX, int a2, int a3) {
			int ret = 0;
			for(auto & cb : vtable20_callbacks) {
				try {
					ret |= cb(This, a2, a3);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int,int)>;
				return ((vPtr)vtable_original[1])(This, EDX, a2, a3);
			}
			return 0;
		}
		static int __fastcall hookVtable24(T * This, int EDX, int a2) {
			int ret = 0;
			for(auto & cb : vtable24_callbacks) {
				try {
					ret |= cb(This, a2);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int)>;
				return ((vPtr)vtable_original[2])(This, EDX, a2);
			}
			return 0;
		}
		static int __fastcall hookVtable28(T * This, int EDX, int a2) {
			int ret = 0;
			for(auto & cb : vtable28_callbacks) {
				try {
					ret |= cb(This, a2);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int)>;
				return ((vPtr)vtable_original[3])(This, EDX, a2);
			}
			return 0;
		}
		static int __fastcall hookVtable2C(T * This, int EDX, int a2, int a3) {
			int ret = 0;
			for(auto & cb : vtable2C_callbacks) {
				try {
					ret |= cb(This, a2, a3);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int,int)>;
				return ((vPtr)vtable_original[4])(This, EDX, a2, a3);
			}
			return 0;
		}
		static int __fastcall hookVtable30(T * This, int EDX) {
			int ret = 0;
			for(auto & cb : vtable30_callbacks) {
				try {
					ret |= cb(This);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int)>;
				return ((vPtr)vtable_original[5])(This, EDX);
			}
			return 0;
		}
		static int __fastcall hookVtable34(T * This, int EDX) {
			int ret = 0;
			for(auto & cb : vtable34_callbacks) {
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
		static int __fastcall hookVtable38(T * This, int EDX, int a2) {
			int ret = 0;
			for(auto & cb : vtable38_callbacks) {
				try {
					ret |= cb(This, a2);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int)>;
				return ((vPtr)vtable_original[7])(This, EDX, a2);
			}
			return 0;
		}
		static int __fastcall hookVtable3C(T * This, int EDX) {
			int ret = 0;
			for(auto & cb : vtable3C_callbacks) {
				try {
					ret |= cb(This);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int)>;
				return ((vPtr)vtable_original[8])(This, EDX);
			}
			return 0;
		}
		static int __fastcall hookVtable40(T * This, int EDX) {
			int ret = 0;
			for(auto & cb : vtable40_callbacks) {
				try {
					ret |= cb(This);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int)>;
				return ((vPtr)vtable_original[9])(This, EDX);
			}
			return 0;
		}
		static int __fastcall hookVtable44(T * This, int EDX, int a2, int a3, int a4) {
			int ret = 0;
			for(auto & cb : vtable44_callbacks) {
				try {
					ret |= cb(This, a2, a3, a4);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int,int,int,int)>;
				return ((vPtr)vtable_original[10])(This, EDX, a2, a3, a4);
			}
			return 0;
		}
		static int __fastcall hookVtable48(T * This, int EDX) {
			int ret = 0;
			for(auto & cb : vtable48_callbacks) {
				try {
					ret |= cb(This);
				} catch(std::exception & e) {
					printf("callback exception: %s\n", e.what());
				}
			}
			if(!ret) {
				using vPtr = std::add_pointer_t<int __fastcall(T*,int)>;
				return ((vPtr)vtable_original[11])(This, EDX);
			}
			return 0;
		}
	};

	template<typename T>
	static T* castCGameTask(CTask *task) {
		return (T*)task;
	}

#define CGameTaskAddVTHooks(classname, vtname) \
	Hooks::hookVtable(#classname, 0x1C, (DWORD)&vtname[7], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable1C, &CGameTask_vtableHooks<classname>::vtable_original[0]); \
	Hooks::hookVtable(#classname, 0x20, (DWORD)&vtname[8], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable20, &CGameTask_vtableHooks<classname>::vtable_original[1]); \
	Hooks::hookVtable(#classname, 0x24, (DWORD)&vtname[9], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable24, &CGameTask_vtableHooks<classname>::vtable_original[2]); \
	Hooks::hookVtable(#classname, 0x28, (DWORD)&vtname[10], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable28, &CGameTask_vtableHooks<classname>::vtable_original[3]); \
	Hooks::hookVtable(#classname, 0x2C, (DWORD)&vtname[11], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable2C, &CGameTask_vtableHooks<classname>::vtable_original[4]); \
	Hooks::hookVtable(#classname, 0x30, (DWORD)&vtname[12], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable30, &CGameTask_vtableHooks<classname>::vtable_original[5]); \
	Hooks::hookVtable(#classname, 0x34, (DWORD)&vtname[13], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable34, &CGameTask_vtableHooks<classname>::vtable_original[6]); \
	Hooks::hookVtable(#classname, 0x38, (DWORD)&vtname[14], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable38, &CGameTask_vtableHooks<classname>::vtable_original[7]); \
	Hooks::hookVtable(#classname, 0x3C, (DWORD)&vtname[15], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable3C, &CGameTask_vtableHooks<classname>::vtable_original[8]); \
	Hooks::hookVtable(#classname, 0x40, (DWORD)&vtname[16], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable40, &CGameTask_vtableHooks<classname>::vtable_original[9]); \
	Hooks::hookVtable(#classname, 0x44, (DWORD)&vtname[17], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable44, &CGameTask_vtableHooks<classname>::vtable_original[10]); \
	Hooks::hookVtable(#classname, 0x48, (DWORD)&vtname[18], (DWORD)&CGameTask_vtableHooks<classname>::hookVtable48, &CGameTask_vtableHooks<classname>::vtable_original[11]);

#define CGameTaskAddLuaVTHooks(classname) \
	lua->set_function(#classname "_RegisterCallback_vtable1C", &CGameTask_vtableHooks<classname>::registerCallbackVt1C); \
	lua->set_function(#classname "_RegisterCallback_vtable20", &CGameTask_vtableHooks<classname>::registerCallbackVt20); \
	lua->set_function(#classname "_RegisterCallback_vtable24", &CGameTask_vtableHooks<classname>::registerCallbackVt24); \
	lua->set_function(#classname "_RegisterCallback_vtable28", &CGameTask_vtableHooks<classname>::registerCallbackVt28); \
	lua->set_function(#classname "_RegisterCallback_vtable2C", &CGameTask_vtableHooks<classname>::registerCallbackVt2C); \
	lua->set_function(#classname "_RegisterCallback_vtable30", &CGameTask_vtableHooks<classname>::registerCallbackVt30); \
	lua->set_function(#classname "_RegisterCallback_vtable34", &CGameTask_vtableHooks<classname>::registerCallbackVt34); \
	lua->set_function(#classname "_RegisterCallback_vtable38", &CGameTask_vtableHooks<classname>::registerCallbackVt38); \
	lua->set_function(#classname "_RegisterCallback_vtable3C", &CGameTask_vtableHooks<classname>::registerCallbackVt3C); \
	lua->set_function(#classname "_RegisterCallback_vtable40", &CGameTask_vtableHooks<classname>::registerCallbackVt40); \
	lua->set_function(#classname "_RegisterCallback_vtable44", &CGameTask_vtableHooks<classname>::registerCallbackVt44); \
	lua->set_function(#classname "_RegisterCallback_vtable48", &CGameTask_vtableHooks<classname>::registerCallbackVt48); \
	lua->set_function(#classname "_CastCGameTask", &castCGameTask<classname>);

	int unknown30; // 0x30
	int unknown34; // 0x34
	int unknown38; // 0x38
	int unknown3C; // 0x3C
	int unknown40; // 0x40
	int unknown44; // 0x44
	int unknown48; // 0x48
	int unknown4C; // 0x4C
	int unknown50; // 0x50
	int unknown54; // 0x54
	int unknown58; // 0x58
	int unknown5C; // 0x5C
	int unknown60; // 0x60
	int unknown64; // 0x64
	int unknown68; // 0x68
	int unknown6C; // 0x6C
	int unknown70; // 0x70
	int unknown74; // 0x74
	int unknown78; // 0x78
	int unknown7C; // 0x7C
	int unknown80; // 0x80
	int posX; // 0x84
	int posY; // 0x88
	int unknown8C; // 0x8C
	int speedX; // 0x90
	int speedY; // 0x94
	int unknown98; // 0x98
	int unknown9C; // 0x9C
	int unknownA0; // 0xA0
	int unknownA4; // 0xA4
	int unknownA8; // 0xA8
	int unknownAC; // 0xAC
	int unknownB0; // 0xB0
	int unknownB4; // 0xB4
	int unknownB8; // 0xB8
	int unknownBC; // 0xBC
	int unknownC0; // 0xC0
	int unknownC4; // 0xC4
	int unknownC8; // 0xC8
	int unknownCC; // 0xCC
	int unknownD0; // 0xD0
	int unknownD4; // 0xD4
	int unknownD8; // 0xD8
	int unknownDC; // 0xDC
	int unknownE0; // 0xE0
	int unknownE4; // 0xE4
	int unknownE8; // 0xE8
	int unknownEC; // 0xEC
	static int install(SignatureScanner & signatureScanner, module mod);
	static int __stdcall hookCGameTaskPhysics(int a1, CGameTask *object, int a3);
};


#endif //WKJELLYWORM_CGAMETASK_H
