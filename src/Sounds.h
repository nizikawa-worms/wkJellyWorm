#ifndef WKJELLYWORM_SOUNDS_H
#define WKJELLYWORM_SOUNDS_H

#include <sigscanner.h>
#include <vector>
#include <string>
#include <src/entities/CTask.h>

class Sounds {
private:
	static inline std::vector<std::string> customSounds;

public:
	static const int customSoundStartingId = 451; //maybe 451, first team: <127-180>, last team: <397-450>


	static void onConstructGlobalContext(int a1);
	static int install(SignatureScanner &, module);
	static int callPlaySoundLocal(int a1, int a2, CTask * object, Constants::SoundIds id, int a5);
	static int registerCustomSound(std::string filename);
	static void resetConfig();
};


#endif //WKJELLYWORM_SOUNDS_H
