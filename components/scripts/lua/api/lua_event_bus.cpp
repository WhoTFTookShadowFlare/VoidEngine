#include "lua_event_bus.hpp"
#include "lua_object.hpp"

namespace VoidEngine::Scripts::Lua::API {
	LuaEventBusWrapper* lua_pushEventBus(lua_State* state) {
		LuaEventBusWrapper* bus = static_cast<LuaEventBusWrapper*>(lua_newuserdata(state, sizeof(LuaEventBusWrapper)));
		luaL_getmetatable(state, "EventBus");
		lua_setmetatable(state, -2);
		new (bus) LuaEventBusWrapper;
		return bus;
	}
	
	LuaEventBusWrapper* lua_checkEventBus(lua_State* state, int idx) {
		return static_cast<LuaEventBusWrapper*>(
			luaL_checkudata(state, idx, "EventBus")
		);
	}

	int lua_EventBusAddHandler(lua_State* state) {
		LuaEventBusWrapper* busWrapper = lua_checkEventBus(state, 1);
		LuaObjectWrapper* objWrapper = lua_checkObject(state, 2);

		busWrapper->evt->addHandler(objWrapper->object);

		return 0;
	}
	
	int lua_EventBusRemoveHandler(lua_State* state) {
		LuaEventBusWrapper* busWrapper = lua_checkEventBus(state, 1);
		LuaObjectWrapper* objWrapper = lua_checkObject(state, 2);

		busWrapper->evt->removeHandler(objWrapper->object);

		return 0;
	}
	
	int lua_EventBusFireEvent(lua_State* state) {
		LuaEventBusWrapper* busWrapper = lua_checkEventBus(state, 1);
		LuaObjectWrapper* evtWrapper = lua_checkObject(state, 2);

		if(!evtWrapper->object->getClass()->instanceOf(&Event::AEvent::ClassData)) {
			luaL_typeerror(state, 2, "AEvent");
			return 0;
		}

		auto evt = std::static_pointer_cast<Event::AEvent>(evtWrapper->object);
		busWrapper->evt->fireEvent(evt);

		return 0;
	}

	int lua_EventBus__index(lua_State* state) {
		LuaEventBusWrapper* bus = lua_checkEventBus(state, 1);

		std::string idxName = lua_tostring(state, 2);
		lua_getmetatable(state, 1);
		lua_getfield(state, -1, idxName.c_str());
		return 1;
	}
	
	int lua_EventBus__tostring(lua_State* state) {
		LuaEventBusWrapper* bus = lua_checkEventBus(state, 1);
		lua_pushstring(state, std::format("EventBus ({})", bus->evt->getEventClass()->getName()).c_str());
		return 1;
	}
	
	int lua_EventBus__eq(lua_State* state) {
		LuaEventBusWrapper* LHS = lua_checkEventBus(state, 1);
		LuaEventBusWrapper* RHS = lua_checkEventBus(state, 2);
		lua_pushboolean(state, LHS->evt == RHS->evt);
		return 1;
	}
	
	int lua_EventBus__gc(lua_State* state) {
		return 0;
	}

	int luaopen_EventBus(lua_State* state) {
		luaL_newmetatable(state, "EventBus");
		luaL_setfuncs(state, eventBusLib, 0);
		lua_setglobal(state, "EventBus");
		return 0;
	}
}