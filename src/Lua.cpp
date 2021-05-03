#include "Lua.h"
#include "Config.h"
#include <lua/lua.hpp>
#include <sol/sol.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>

std::vector<std::string> unsafeFuncs = {"collectgarbage", "dofile", "getfenv", "getmetatable", "load", "loadfile", "loadstring", "rawequal", "rawget", "rawset", "setfenv", "setmetatable", "coroutine", "module", "package", "require", "package.loaded", "package.loaders", "package.loadlib", "package.path", "package.cpath", "package.preload", "package.seeall", "table", "io", "os", "os.date", "os.execute", "os.exit", "os.getenv", "os.remove", "os.rename", "os.setlocale", "os.tmpname", "debug", "newproxy"};

namespace fs = std::filesystem;

Lua::Lua() : state(new sol::state()) {
	state->open_libraries(sol::lib::base,
					   sol::lib::package,
					   sol::lib::string,
					   sol::lib::math,
					   sol::lib::io,
					   sol::lib::table,
					   sol::lib::bit32,
					   sol::lib::debug);

	(*state)["package"]["searchers"] = state->create_table_with(1, luaRequire);

	for (const auto & entry : fs::directory_iterator(Config::luaLibDir)) {
		if(!entry.is_regular_file()) continue;
		if(entry.path().extension().string() == ".lua") {
			std::string name = entry.path().stem().string();
			knownLibraries[name] = entry.path().string();
		}
	}

}

Lua &Lua::getInstance() {
	static Lua instance;
	return instance;
}

sol::state *Lua::getState() const {
	return state;
}

void Lua::install() {

}

void Lua::onConstructGlobalContext(int a1) {

}

std::shared_ptr<sol::environment> Lua::spawnEnv(std::string path) {
	auto ptr = std::make_shared<sol::environment>(*state, sol::create, state->globals());
	auto & env = *ptr;
	for(auto & func : unsafeFuncs) {
		env[func] = nullptr;
	}
	state->script_file(path, env);
	return ptr;
}

int Lua::luaRequire(lua_State *L) {
	std::string name = sol::stack::get<std::string>(L);
	std::string path;
	if (knownLibraries.find(name) != knownLibraries.end()) {
		path = knownLibraries[name];
	} else {
		//todo: find in enabled packages
	}
	if(!path.empty()) {
		std::ifstream in(path);
		std::stringstream buffer;
		buffer << in.rdbuf();
		in.close();
		std::string script = std::move(buffer.str());
		luaL_loadbuffer(L, script.data(), script.size(), path.c_str());
		return 1;
	} else {
		sol::stack::push(L, "These are not the modules you're looking for!");
		return 1;
	}
}
