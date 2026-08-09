#pragma once

#include <lua.h>
#include <lualib.h>
#include <memory>
#include <ve/object.hpp>

namespace VoidEngine::Scripts::Luau {
	struct ObjectHolder {
		std::shared_ptr<Object> obj;
	};

	int ObjectNew(lua_State* L);

	int ObjectToString(lua_State* L);
	int ObjectGet(lua_State* L);
	int ObjectSet(lua_State* L);
	int ObjectCall(lua_State* L);
	int ObjectEq(lua_State* L);

	static const luaL_Reg objectMeth[] = {
		{ "__tostring", ObjectToString },
		{ "__index", ObjectGet },
		{ "__newindex", ObjectSet },
		{ "__namecall", ObjectCall },
		{ "__eq", ObjectEq },
		{ nullptr, nullptr }
	};

	static const luaL_Reg objectLib[] = {
		{ "new", ObjectNew },
		{ nullptr, nullptr }
	};
}
