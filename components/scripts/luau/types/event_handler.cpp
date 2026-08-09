#include "event_handler_holder.hpp"

#include "class_holder.hpp"
#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "../luau_event_handler.hpp"
#include <lua.h>
#include <lualib.h>
#include <print>
#include <format>

namespace VoidEngine::Scripts::Luau {
	int EventHandlerNew(lua_State* L) {
		const Class* evtCls = nullptr;
		if(lua_isstring(L, 1)) {
			evtCls = ClassDB::getInstance()->getClassByName(luaL_checkstring(L, 1));
		} else {
			ClassHolder* clsHolder = static_cast<ClassHolder*>(luaL_checkudata(L, 1, "Class"));
			evtCls = clsHolder->cls;
		}

		if(!evtCls->instanceOf(&Event::AEvent::ClassData)) {
			std::println("[ERR] [LUAU] EventHandler.new arg 0 must be a class of type AEvent");
			return 0;
		}

		if(!lua_isfunction(L, 2)) {
			std::println("[ERR] [LUAU] EventHandler.new arg 1 must be a function");
			return 0;
		}

		EventHandlerHolder* ptr = static_cast<EventHandlerHolder*>(
			lua_newuserdata(L, sizeof(EventHandlerHolder))
		);
		ptr->handler = new LuauEventHandler(evtCls, L, 2);

		if(luaL_newmetatable(L, "EventHandler")) {
			luaL_register(L, nullptr, eventHandlerMeth);
			lua_pushliteral(L, "EventHandler");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		return 1;
	}

	int EventHandlerToString(lua_State* L) {
		EventHandlerHolder* evt = static_cast<EventHandlerHolder*>(luaL_checkudata(L, 1, "EventHandler"));
		lua_pushstring(L, std::format("EventHandler ({})", evt->handler->event->getName()).c_str());
		return 1;
	}

	int EventHandlerEq(lua_State* L) {
		EventHandlerHolder* LHS = static_cast<EventHandlerHolder*>(luaL_checkudata(L, 1, "EventHandler"));
		EventHandlerHolder* RHS = static_cast<EventHandlerHolder*>(luaL_checkudata(L, 2, "EventHandler"));
		lua_pushboolean(L, LHS->handler == RHS->handler);
		return 1;
	}
}
