#pragma once

#include <ve/struct_db.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	struct LuaStructWrapper final {
		std::shared_ptr<Struct> struc = nullptr;
	};

	LuaStructWrapper* lua_pushStructWrapper(lua_State*);
	LuaStructWrapper* lua_checkStruct(lua_State*, int);

	int lua_Struct__index(lua_State*);
	int lua_Struct__newindex(lua_State*);
	int lua_Struct__tostring(lua_State*);
	int lua_Struct__eq(lua_State*);

	static luaL_Reg structLib[] = {

		{ "__index", lua_Struct__index },
		{ "__newindex", lua_Struct__newindex },
		{ "__tostring", lua_Struct__tostring },
		{ "__eq", lua_Struct__eq },

		{ nullptr, nullptr }
	};

	int luaopen_Struct(lua_State*);
}
