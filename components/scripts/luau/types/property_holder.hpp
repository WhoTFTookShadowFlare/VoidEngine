#pragma once

#include <lua.h>
#include <lualib.h>
#include "ve/class_db.hpp"

namespace VoidEngine::Scripts::Luau {
	struct PropertyHolder {
		const PropertyBase* prop;
	};

	int PropertyNew(lua_State* L);

	int PropertyToString(lua_State* L);
	int PropertyIndex(lua_State* L);
	int PropertyCall(lua_State* L);
	int PropertyEq(lua_State* L);

	int PropertyGet(lua_State* L);
	int PropertySet(lua_State* L);
	int PropertyIsReadOnly(lua_State* L);

	static const luaL_Reg propertyMeth[] = {
		{ "__tostring", PropertyToString },
		{ "__index", PropertyIndex },
		{ "__namecall", PropertyCall },
		{ "__eq", PropertyEq },
		{ nullptr, nullptr }
	};

	static const luaL_Reg propertyLib[] = {
		{ "new", PropertyNew },
		{ nullptr, nullptr }
	};
}
