#pragma once

#include "ve/class_db.hpp"
#include <lua.h>
#include <lualib.h>

namespace VoidEngine::Scripts::Luau {
	struct EventHandlerHolder {
		const EventHandlerBase* handler;
	};

	int EventHandlerNew(lua_State* L);

	int EventHandlerToString(lua_State* L);
	int EventHandlerEq(lua_State* L);

	static const luaL_Reg eventHandlerMeth[] = {
		{ "__tostring", EventHandlerToString },
		{ "__eq", EventHandlerEq },
		{ nullptr, nullptr }
	};

	static const luaL_Reg eventHandlerLib[] = {
		{ "new", EventHandlerNew },
		{ nullptr, nullptr }
	};
}
