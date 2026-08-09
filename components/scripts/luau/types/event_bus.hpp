#pragma once

#include "ve/event/event_bus.hpp"
#include <lua.h>
#include <lualib.h>

namespace VoidEngine::Scripts::Luau {
	struct EventBusHolder {
		Event::EventBus* bus;
	};

	int EventBusNew(lua_State* L);

	int EventBusCall(lua_State* L);

	int EventBusAddHandler(lua_State* L);
	int EventBusRemoveHandler(lua_State* L);
	int EventBusHasHandler(lua_State* L);
	int EventBusFireEvent(lua_State* L);

	static const luaL_Reg eventBusMeth[] = {
		{ "__namecall", EventBusCall },
		{ nullptr, nullptr }
	};

	static const luaL_Reg eventBusLib[] = {
		{ "new", EventBusNew },
		{ nullptr, nullptr }
	};
}
