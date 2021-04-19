#ifndef WKJELLYWORM_LOBBY_H
#define WKJELLYWORM_LOBBY_H

#include <sigscanner.h>
#include <string>

class Lobby {
private:
	inline static DWORD addrMyNickname = 0;
	inline static DWORD addrLobbyHostObj = 0;
	static int __fastcall hookLobbyHostCommands(void* This, void* EDX, char **commandstrptr, char **argstrptr);
	static int __fastcall hookLobbyClientCommands(void* This, void* EDX, char **commandstrptr, char **argstrptr);
	static int __stdcall hookLobbyDisplayMessage(int a1, char *msg);
	static int __fastcall hookCwndEnableWindow(void * This, int EDX, int enable);
	static void __stdcall hookFrontendChangeScreen(int screen);

public:
	static void sendGreenTextSystem(void * This, std::string msg);
	static void sendGreenTextMe(void * This, std::string msg);
	static void showGreenText(void * This, std::string msg);

	static int install(SignatureScanner &, module);

	static int sendConfigString(void * This);
};


#endif //WKJELLYWORM_LOBBY_H
