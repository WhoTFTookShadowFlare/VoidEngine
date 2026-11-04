#pragma once

#include <ve/object.hpp>
#include <ve/event/event_bus.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	struct LuaEventBusWrapper final {
		std::shared_ptr<Object> obj = nullptr;
		Event::EventBus* evt = nullptr;
	};

	LuaEventBusWrapper* lua_pushEventBus(lua_State*);
	LuaEventBusWrapper* lua_checkEventBus(lua_State*, int idx);

	int lua_EventBusAddHandler(lua_State*);
	int lua_EventBusRemoveHandler(lua_State*);
	int lua_EventBusFireEvent(lua_State*);

	int lua_EventBus__index(lua_State*);
	int lua_EventBus__tostring(lua_State*);
	int lua_EventBus__eq(lua_State*);
	int lua_EventBus__gc(lua_State*);

	static luaL_Reg eventBusLib[] = {
		{ "addHandler", lua_EventBusAddHandler },
		{ "removeHandler", lua_EventBusRemoveHandler },
		{ "fireEvent", lua_EventBusFireEvent },

		{ "__index", lua_EventBus__index },
		{ "__tostring", lua_EventBus__tostring },
		{ "__eq", lua_EventBus__eq },
		{ "__gc", lua_EventBus__gc },

		{ nullptr, nullptr }
	};

	int luaopen_EventBus(lua_State*);
}
