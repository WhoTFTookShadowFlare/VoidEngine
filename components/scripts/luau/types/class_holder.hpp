#pragma once

#include "ve/class_db.hpp"
#include "lua.h"
#include "lualib.h"

namespace VoidEngine::Scripts::Luau {
	struct ClassHolder {
		const Class* cls;
	};

	int ClassNew(lua_State* L);
	int GetClass(lua_State* L);
	int RegisterClass(lua_State* L);

	int ClassToString(lua_State* L);
	int ClassGet(lua_State* L);
	int ClassSet(lua_State* L);
	int ClassCall(lua_State* L);
	int ClassEq(lua_State* L);

	int ClassAddMethod(lua_State* L);
	int ClassAddProperty(lua_State* L);
	int ClassAddEventHandler(lua_State* L);
	int ClassFindProperty(lua_State* L);
	int ClassFindMethod(lua_State* L);
	int ClassFindEventHandler(lua_State* L);
	int ClassIsAbstract(lua_State* L);
	int ClassInstanceOf(lua_State* L);
	int ClassCreate(lua_State* L);

	static const luaL_Reg classMeth[] = {
		{ "__tostring", ClassToString },
		{ "__index", ClassGet },
		{ "__newindex", ClassSet },
		{ "__namecall", ClassCall },
		{ "__eq", ClassEq },
		{ nullptr, nullptr }
	};

	static const luaL_Reg classLib[] = {
		{ "new", ClassNew },
		{ "get", GetClass },
		{ "registerclass", RegisterClass },
		{ nullptr, nullptr }
	};
}
