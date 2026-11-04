#pragma once

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	int lua_VE_wrapObject(lua_State*);

	static luaL_Reg VELib[] = {
		{ "wrapTable", lua_VE_wrapObject },

		{ nullptr, nullptr }
	};

	int luaopen_VE(lua_State*);
}
