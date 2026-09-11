#pragma once

#include <ve/script/a_object_script.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	class LuaObjectScript final : public AObjectScript {
	private:
		const Class* cls = nullptr;
		lua_State* state = nullptr;
	public:
		LuaObjectScript(lua_State* state, int objIdx, const Class* cls);
		~LuaObjectScript();

		std::shared_ptr<AScriptEngine> getScriptEngine();

		const Class* getClass();

		Variant call(std::string fnName, std::vector<Variant> args);
		Variant get(std::string name);
		void set(std::string name, Variant);

		std::vector<std::string> getFunctions();
		std::vector<std::string> getProperties();
	};
}
