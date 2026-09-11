#pragma once

#include <ve/class_db.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	struct LuaClass {
		const Class* cls;
	};

	int lua_ClassNew(lua_State*);
	int lua_ClassGet(lua_State*);

	int lua_Class__tostring(lua_State*);
	int lua_Class__index(lua_State*);
	int lua_Class__eq(lua_State*);
	
	int lua_ClassRegister(lua_State* state);
	int lua_ClassIsAbstract(lua_State* state);
	int lua_ClassSetConstructor(lua_State* state);
	int lua_ClassInstanceOf(lua_State* state);
	int lua_ClassGetSuper(lua_State* state);
	int lua_ClassGetName(lua_State* state);

	static luaL_Reg classLib[] = {
		{ "new", lua_ClassNew },
		{ "get", lua_ClassGet },

		{ "__tostring", lua_Class__tostring },
		{ "__index", lua_Class__index },
		{ "__eq", lua_Class__eq },

		{ nullptr, nullptr }
	};

	int luaopen_Class(lua_State*);
}
