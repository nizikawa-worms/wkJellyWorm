
#ifndef WKJELLYWORM_CHAT_H
#define WKJELLYWORM_CHAT_H

#include <sigscanner.h>
#include <string>

class Chat {
private:
	static void __stdcall hookOnChatInput(int a3);
public:
	static int onChatInput(int a1, char * msg, int a3);
	static void callShowChatMessage(std::string msg, int color);
	static int install(SignatureScanner &, module);
};


#endif //WKJELLYWORM_CHAT_H
