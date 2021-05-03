#ifndef WKJELLYWORM_PACKAGE_H
#define WKJELLYWORM_PACKAGE_H


#include <string>
#include <vector>
#include <json.hpp>
#include <tuple>
#include "../Lua.h"
#include <filesystem>

class Package {
public:
	struct Version {
		int major = 0, minor = 0, revision = 0;
		bool operator < (Version& other) {
			if (major < other.major)
				return true;
			if (minor < other.minor)
				return true;
			if (revision < other.revision)
				return true;
			return false;
		}
		void parse(std::string version) {
			std::sscanf(version.c_str(), "%d.%d.%d", &major, &minor, &revision);
		}
		bool operator == (Version& other){
			return major == other.major && minor == other.minor && revision == other.revision;
		}
	};

	bool operator<(Package& other) {
		return other.getVersion() < this->getVersion(); //namecheck is omitted
	}
	bool operator == (Package& other){
		return other.getName() == this->getName() && other.getVersionstr() == this->getVersionstr();
	}

	template<typename ReturnType, typename type_t, typename... Args>
	ReturnType callInterface(std::string luaname, Args ... args) {
		try {
			if(!luaEnv)
				throw std::runtime_error("luaEnv is null");
			auto func = luaEnv->get<type_t>(luaname);
			if(!func)
				throw std::runtime_error("missing lua function: " + luaname);
			return func(args...);
		} catch(std::exception & e) {
			printf("Package(%s)::%s exception: %s\n", getIdentifier().c_str(), luaname.c_str(), e.what());
			return 0;
		}
	}


private:
	std::filesystem::path parentpath;
	std::filesystem::path mainscript;

	nlohmann::json manifest;
	std::string name;
	std::string versionstr;
	Version version;
	std::shared_ptr<sol::environment> luaEnv;

public:
	Package(std::string path);
	nlohmann::json &getManifest();

	Version &getVersion();

	const std::string &getName() const;
	const std::string &getVersionstr() const;
	std::string getIdentifier();

	void enable();
	void disable();


};


#endif //WKJELLYWORM_PACKAGE_H
