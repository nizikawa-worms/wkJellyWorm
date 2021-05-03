#ifndef WKJELLYWORM_LUA_H
#define WKJELLYWORM_LUA_H

#include <sol/forward.hpp>
#include <memory>
#include <map>


class Lua {
private:
	sol::state * state;
	Lua();
	static inline std::map<std::string, std::string> knownLibraries;
	static int luaRequire(lua_State * L);
public:
	static void install();
	static Lua & getInstance();

	void resetState();
	sol::state *getState() const;

	std::shared_ptr<sol::environment> spawnEnv(std::string path);

	static void onConstructGlobalContext(int a1);
};


#endif //WKJELLYWORM_LUA_H
