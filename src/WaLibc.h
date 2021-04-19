
#ifndef WKJELLYWORM_WALIBC_H
#define WKJELLYWORM_WALIBC_H


#include <sigscanner.h>

class WaLibc {
public:
	static void * waMalloc(size_t size);
	static void waFree(void * ptr);

	static int install(SignatureScanner &, module);
};


#endif //WKJELLYWORM_WALIBC_H
