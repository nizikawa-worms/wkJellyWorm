#include <MinHook.h>
#include "Packets.h"
#include "Constants.h"

#include "CustomWeapons.h"
#include "Hooks.h"


int (__stdcall *origSendGamePacketWrapped)(Constants::TaskMessage a3, void *data);
int __stdcall hookSendGamePacketWrapped(Constants::TaskMessage a3, void *data) {
	int seax, secx, retv;
	_asm mov seax, eax
	_asm mov secx, ecx

//	CustomWeapons::onSendGamePacketWrapped(seax, secx, y, data);

	_asm push data
	_asm push a3
	_asm mov ecx, secx
	_asm mov eax, seax
	_asm call origSendGamePacketWrapped
	_asm mov retv, eax

	return retv;
}


int Packets::install(SignatureScanner & signatureScanner, module mod) {
	DWORD addrSendGamePacketWrapped = Hooks::scanPattern("SendGamePacketWrapped", "\x56\x8B\xF1\x83\xC6\x03\x83\xE6\xFC\x8D\x4E\x04\xE8\x00\x00\x00\x00\x85\xC0\x75\x04","??????xxxxxxx????xxxx", 0x541130);
	Hooks::minhook("SendGamePacketWrapped", addrSendGamePacketWrapped, (DWORD*)&hookSendGamePacketWrapped, (DWORD*)&origSendGamePacketWrapped);
	return 0;
}