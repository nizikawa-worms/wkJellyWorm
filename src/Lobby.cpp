#include "Lobby.h"
#include <MinHook.h>
#include <json.hpp>
#include "packages/PackageManager.h"

#include "Config.h"
#include "Hooks.h"


void (__fastcall *addrLobbySendGreentext)(char * msg, void * EDX, void* This, int a3, int a4);
int (__fastcall *origLobbyHostCommands)(void* This, void* EDX, char **commandstrptr, char **argstrptr);
int __fastcall Lobby::hookLobbyHostCommands(void *This, void *EDX, char **commandstrptr, char **argstrptr) {
	std::string command = std::string(commandstrptr[0]);
	std::string args = std::string(argstrptr[0]);

	addrLobbyHostObj = (DWORD)This;

	if(command == "help") {
		showGreenText(This,
		"wkJellyWorm commands:\n" \
			"/help - display this help message\n" \
			"/save <name> - save current configuration as a scheme\n" \
			"/load <name> - load existing scheme\n" \
			"/reset - reset configuration\n" \
			"/enable <package> - enable wkJellyWorm lua package\n" \
			"/disable <package> - disable wkJellyWorm lua package\n" \
			"/jelly - show your wkJellyWorm version"
			);
		return 1;
	}
	else if(command == "reset") {
		Config::resetConfig();
		sendConfigString(This);
		sendGreenTextSystem(This, "Cleared wkJellyWorm config");
		return 1;
	}
	else if(command == "save" || command == "load") {
		args.erase(std::remove_if(args.begin(), args.end(), []( auto const& c ) -> bool { return !std::isalnum(c); } ), args.end());
		if(args.length()) {
			if(command == "save") {
				if(!Config::saveConfigToFile(args)) {
					std::string msg = "Saved current config as: " + args;
					showGreenText(This, msg);
				} else {
					std::string msg = "Failed to save current config as: " + args;
					showGreenText(This, msg);
				}
			}
			if(command == "load") {
				if(!Config::loadConfigFromFile(args)) {
					std::string msg = "Loaded config: " + args;
					sendConfigString(This);
					showGreenText(This, msg);
				} else {
					std::string msg = "Failed to load config: " + args;
					showGreenText(This, msg);
				}
			}
		} else {
			std::string usage = "Usage: /" + command + " scheme\n";
			usage += "\tList of available schemes: " + Config::listConfigFiles();
			showGreenText(This, usage);
		}
		return 1;
	}
	if(PackageManager::getInstance().handleLobbyHostCommand(This, command, args))
		return 1;

	return origLobbyHostCommands(This, EDX, commandstrptr, argstrptr);
}

int (__fastcall *origLobbyClientCommands)(void* This, void* EDX, char **commandstrptr, char **argstrptr);
int __fastcall Lobby::hookLobbyClientCommands(void *This, void *EDX, char **commandstrptr, char **argstrptr) {
	std::string command = std::string(commandstrptr[0]);
	std::string args = std::string(argstrptr[0]);

	if(command == "jelly") {
		sendGreenTextMe(This, Config::getJellyVersionMessage());
		return 1;
	}
	if(PackageManager::getInstance().handleLobbyClientCommand(This, command, args))
		return 1;
	return origLobbyClientCommands(This, EDX, commandstrptr, argstrptr);
}

void Lobby::sendGreenTextMe(void *This, std::string msg) {
	std::string buff = (char*)addrMyNickname;
	buff += " ";
	buff += msg;
	addrLobbySendGreentext((char*)buff.c_str(), 0, This, 0, 0);
}

void Lobby::sendGreenTextSystem(void *This, std::string msg) {
	addrLobbySendGreentext((char*)msg.c_str(), 0, This, 0, 0);
}

void Lobby::showGreenText(void *This, std::string msg) {
	std::string buff = "SYS:wkJellyWorm:ALL:" + msg;
	hookLobbyDisplayMessage((int)This + 0x10318, (char*)buff.c_str());
}

int Lobby::sendConfigString(void * This) {
	std::string config = "wkJellyWormConfigStr:" + Config::getConfigString(-1, true);
	sendGreenTextSystem(This, config);
	return 0;
}


int (__stdcall *origLobbyDisplayMessage)(int a1, char *msg);
int __stdcall Lobby::hookLobbyDisplayMessage(int a1, char *msg) {
	char * pos[6];
	pos[0] = msg;
	for(size_t i=1; i < 6; i++) {
		pos[i] = strstr(pos[i-1] + 1, ":");
		if(!pos[i]) break;
		if(i==1 && strncmp(pos[i-1], "SYS:", 4)) break;
		else if(i==3 && strncmp(pos[i-1], ":ALL:", 5)) break;
		else if(i==4 && strncmp(pos[i-1], ":wkJellyWormConfigStr:", 22)) break;
		else if(i==5) {
			if(!addrLobbyHostObj) { //host should not read config
				Config::parseConfigString(pos[i-1] + 1);
			}
			return 1;
		}
	}
	return origLobbyDisplayMessage(a1, msg);
}
void (__stdcall *origFrontendChangeScreen)(int screen);
void __stdcall Lobby::hookFrontendChangeScreen(int screen) {
	int sesi;
	_asm mov sesi, esi

	switch(screen) {
		case 10:	// main screen
		case 11:	// local multiplayer
		case 21:	// single player
		case 1700:	// network
		case 1702:	// lan network
		case 1703:  // wormnet
		case 1704: 	// lobby host
		case 1706:	// lobby client
			addrLobbyHostObj = 0;
			Config::resetConfig();
			break;
		default:
			break;
	}

	_asm mov esi, sesi
	_asm push screen
	_asm call origFrontendChangeScreen
}


// this sucks
int flagCwndEnableWindow = 0;
int (__fastcall *origLobbyPrintUsedVersion)(void * This, int EDX);
int __fastcall hookLobbyPrintUsedVersion(void * This, int EDX) {
	flagCwndEnableWindow = 1;
	int ret = origLobbyPrintUsedVersion(This, EDX);
	flagCwndEnableWindow = 0;
	return ret;
}

int (__fastcall *origCwndEnableWindow)(void * This, int EDX, int enable);
int __fastcall Lobby::hookCwndEnableWindow(void * This, int EDX, int enable) {
	if (flagCwndEnableWindow && enable && addrLobbyHostObj) {
		sendConfigString((void*)addrLobbyHostObj);
	}
	return origCwndEnableWindow(This, EDX, enable);
}



int Lobby::install(SignatureScanner & signatureScanner, module mod) {
	DWORD addrLobbyHostCommands = Hooks::scanPattern("LobbyHostCommands", "\x55\x8B\xEC\x83\xE4\xF8\x64\xA1\x00\x00\x00\x00\x6A\xFF\x68\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\x53\x56\x8B\x75\x08\x8B\x06\x57\x68\x00\x00\x00\x00\x50\x8B\xF9\xE8\x00\x00\x00\x00\x83\xC4\x08\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x06\x68\x00\x00\x00\x00\x50\xE8\x00\x00\x00\x00", "??????xx????xxx????xxxx????xx????xxxxxxxxx????xxxx????xxxxxxx????xxx????xx????", 0x4B9B00);
	DWORD addrLobbyClientCommands = Hooks::scanPattern("LobbyClientCommands", "\x55\x8B\xEC\x83\xE4\xF8\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x40\x53\x56\x8B\x75\x08\x8B\x06\x57\x8B\xD9\x68\x00\x00\x00\x00\x50\x89\x5C\x24\x1C\xE8\x00\x00\x00\x00\x83\xC4\x08\x85\xC0", "??????xxx????xx????xxxx????xxxxxxxxxxxxxx????xxxxxx????xxxxx", 0x4AABB0);
	DWORD addrLobbyDisplayMessage = Hooks::scanPattern("LobbyDisplayMessage", "\x55\x8B\xEC\x83\xE4\xF8\x64\xA1\x00\x00\x00\x00\x6A\xFF\x68\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x30\x53\x56\x57\xE8\x00\x00\x00\x00\x33\xC9\x85\xC0\x0F\x95\xC1\x85\xC9\x75\x0A\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00", "??????xx????xxx????xxxx????xxxxxxx????xxxxxxxxxxxx????x????", 0x493CB0);
	DWORD addrFrontendChangeScreen = Hooks::scanPattern("FrontendChangeScreen", "\x83\x3D\x00\x00\x00\x00\x00\x53\x8B\x5C\x24\x08\x75\x14\x8B\x46\x3C\xA8\x18\x74\x59\x83\xE0\xEF\x89\x5E\x44\x89\x46\x3C\x5B\xC2\x04\x00\x6A\x00\x8B\xCE\xE8\x00\x00\x00\x00\x8B\x86\x00\x00\x00\x00\x50\x8B\x86\x00\x00\x00\x00\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x33\xC0\x57", "???????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xx????xxx????x????x????xxx", 0x447A20);
	DWORD addrLobbyPrintUsedVersion = Hooks::scanPattern("LobbyPrintUsedVersion", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\x53\x55\x56\x57\xBF\x00\x00\x00\x00\x89\x4C\x24\x70\xC7\x44\x24\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xC0\x89\x84\x24\x00\x00\x00\x00", "???????xx????xxxx????xx????xxxxx????xxxxxxx?????x????xxxxx????", 0x4B7E20);
	DWORD addrCwndEnableWindow = Hooks::scanPattern("CwndEnableWindow", "\x83\x79\x50\x00\x75\x10\xFF\x74\x24\x04\xFF\x71\x20\xFF\x15\x00\x00\x00\x00\xC2\x04\x00\x8B\x49\x50\x8B\x01\xFF\xA0\xA8\x00\x00\x00", "??????xxxxxxxxx????xxxxxxxxxxxxxx", 0x5C647A);

	addrLobbySendGreentext =
			(void (__fastcall *)(char*,void *,void *,int, int))
			Hooks::scanPattern("LobbySendGreentext", "\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x51\x56\x57\x8B\xF1\x68\x00\x00\x00\x00\x8D\x4C\x24\x0C\xE8\x00\x00\x00\x00\x80\x7C\x24\x00\x00", "???????xx????xxxx????xxxxxx????xxxxx????xxx??", 0x4AA990);
	addrMyNickname = *(DWORD*)((DWORD)addrLobbySendGreentext + 0x4D);

	Hooks::polyhook("LobbyHostCommands", addrLobbyHostCommands, (DWORD *) &hookLobbyHostCommands, (DWORD *) &origLobbyHostCommands);
	Hooks::polyhook("LobbyClientCommands", addrLobbyClientCommands, (DWORD *) &hookLobbyClientCommands, (DWORD *) &origLobbyClientCommands);
	Hooks::polyhook("LobbyDisplayMessage", addrLobbyDisplayMessage, (DWORD *) &hookLobbyDisplayMessage, (DWORD *) &origLobbyDisplayMessage);
	Hooks::polyhook("FrontendChangeScreen", addrFrontendChangeScreen, (DWORD *) &hookFrontendChangeScreen, (DWORD *) &origFrontendChangeScreen);
	Hooks::polyhook("LobbyPrintUsedVersion", addrLobbyPrintUsedVersion, (DWORD *) &hookLobbyPrintUsedVersion, (DWORD *) &origLobbyPrintUsedVersion);
	Hooks::polyhook("CwndEnableWindow", addrCwndEnableWindow, (DWORD *) &hookCwndEnableWindow, (DWORD *) &origCwndEnableWindow);

	return 0;
}
