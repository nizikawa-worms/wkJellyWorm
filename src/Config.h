#ifndef WKJELLYWORM_CONFIG_H
#define WKJELLYWORM_CONFIG_H

#include <sigscanner.h>
#include <json.hpp>


class Config {
private:
	static void saveConfigReplay(char * basepath);
	static void loadConfigReplay(char * basepath);

	inline static nlohmann::json currentConfig;

	inline static const std::string jellyVersionStr = "0.0.1";
	inline static const int jellyVersionInt = 0x00000001;
	static const std::string jellyBuildTime;

public:
	inline static const std::string jellyDir = "jelly";
	inline static const std::string schemeDir = jellyDir + "\\schemes";
	inline static const std::string schemeExt = ".jelly";
	inline static const std::string luaLibDir = jellyDir + "\\lualibs";
	inline static const std::string packageDir = jellyDir + "\\packages";
	inline static const std::string iniFile = ".\\wkJellyWorm.ini";
	inline static const std::string offsetsFile = jellyDir +"\\offsetcache.json";



	static void onConstructGlobalContext(int a1);

	static std::string getConfigString(int indent=-1, bool host=false);
	static bool parseConfigString(char *config);
	static int install(SignatureScanner &, module);
	static void resetConfig();

	static std::string listConfigFiles();
	static int saveConfigToFile(std::string & filename);
	static int loadConfigFromFile(std::string & filename);

	static std::string getJellyVersionMessage();
	static int getJellyVersionInt();
	static std::string getJellyVersionStr();
	static int writeVersionToJson(nlohmann::json & config, std::string type);

	inline static int devConsoleEnabled = 0;
	inline static int moduleEnabled = 0;
	inline static int useOffsetCache = 0;
	inline static int signatureMismatchWarning = 0;

	inline static int rendererEnabled = 0;
	inline static int rendererDebugContext = 0;
	inline static int rendererGLMajor = 0;
	inline static int rendererGLMinor = 0;
	inline static int rendererDebugPoints = 0;

	static void readPrivateProfile();
	static void createJellyDirs();
};


#endif //WKJELLYWORM_CONFIG_H
