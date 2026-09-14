#pragma once

#include "ve/object.hpp"
#include <memory>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	struct LuaObjectWrapper final {
		std::shared_ptr<Object> object;
	};

	LuaObjectWrapper* lua_pushObjectWrapper(lua_State*);

	int lua_Object__index(lua_State*);
	int lua_Object__newindex(lua_State*);
	int lua_Object__tostring(lua_State*);
	int lua_Object__eq(lua_State*);
	int lua_Object__gc(lua_State*);

	static luaL_Reg objectLib[] = {
		{ "__index", lua_Object__index },
		{ "__newindex", lua_Object__newindex },
		{ "__tostring", lua_Object__tostring },
		{ "__eq", lua_Object__eq },
		{ "__gc", lua_Object__gc },

		{ nullptr, nullptr }
	};

	int luaopen_Object(lua_State*);
}