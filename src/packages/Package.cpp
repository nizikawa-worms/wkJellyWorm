#include "Package.h"

#include <fstream>
#include <json.hpp>
#include <filesystem>
#include "../Lua.h"
#include <sol/sol.hpp>

namespace fs = std::filesystem;

Package::Package(std::string manifestname) : version({0, 0, 0}){
	std::ifstream ifs(manifestname);
	manifest = nlohmann::json::parse(ifs);

	static std::vector<std::string> requiredFields = {"name", "description", "version", "author", "scripts", "sprites", "imgs", "dependencies"};
	std::string missingFields;
	for(auto & field : requiredFields) {
		if(manifest.find(field) == manifest.end())
			missingFields+= field + " ";
	}
	if(!missingFields.empty())
		throw std::runtime_error("Package manifest is missing fields: " + missingFields);

	name = manifest["name"];
	versionstr= manifest["version"];
	version.parse(versionstr);

	if(manifest["scripts"].empty())
		throw std::runtime_error("Package " + name + " does not include any lua scripts");

	std::string missingFiles;
	parentpath = fs::path(manifestname).parent_path();
	static std::vector<std::string> checkFiles = {"scripts", "sprites", "imgs"};
	for(auto & check : checkFiles) {
		for(std::string filename : manifest[check]) {
			auto path = parentpath / filename;
			if(!fs::exists(path))
				missingFiles += "\n" + filename;
		}
	}
	if(!missingFiles.empty())
		throw std::runtime_error("Package " + name + " is missing files: " + missingFiles);

	mainscript = parentpath / std::string(manifest["scripts"][0]);

	enable();
}

nlohmann::json &Package::getManifest() {
	return manifest;
}

Package::Version &Package::getVersion()  {
	return version;
}

const std::string &Package::getName() const {
	return name;
}

const std::string &Package::getVersionstr() const {
	return versionstr;
}

std::string Package::getIdentifier() {
	return name + ":" + versionstr;
}

void Package::enable() {
	luaEnv = Lua::getInstance().spawnEnv(mainscript.string());
}

void Package::disable() {
	luaEnv = nullptr;
}