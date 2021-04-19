#ifndef WKJELLYWORM_PACKETS_H
#define WKJELLYWORM_PACKETS_H


#include <sigscanner.h>

class Packets {
public:

	static int install(SignatureScanner &, module);
};


#endif //WKJELLYWORM_PACKETS_H
