#pragma once

#include "ve/class_db.hpp"
#include <lua.h>
#include <lualib.h>

namespace VoidEngine::Scripts::Luau {
	struct MethodHolder {
		const MethodBase* meth;
	};

	int MethodNew(lua_State* L);
	
	int MethodToString(lua_State* L);
	int MethodIndex(lua_State* L);
	int MethodCall(lua_State* L);
	int MethodEq(lua_State* L);

	static const luaL_Reg methodMeth[] = {
		{ "__tostring", MethodToString },
		{ "__index", MethodIndex },
		{ "__namecall", MethodCall },
		{ "__eq", MethodEq },
		{ nullptr, nullptr }
	};

	static const luaL_Reg methodLib[] = {
		{ "new", MethodNew },
		{ nullptr, nullptr }
	};
}