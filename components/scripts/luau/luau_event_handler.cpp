#include "luau_event_handler.hpp"
#include "luau_script_engine.hpp"
#include "luau_script_object.hpp"
#include "ve/class_db.hpp"
#include "lua.h"
#include "ve/event/event.hpp"
#include <lua.h>
#include <print>

namespace VoidEngine::Scripts::Luau {
	LuauEventHandler::LuauEventHandler(const Class* eventType, lua_State* L, int32_t stackIdx) : EventHandlerBase(eventType) {
		if(L == nullptr) {
			std::println("[ERR] [LUAU] Failed to make EventHandler, no lua_State was provided (please report)");
			return;
		}

		if(lua_gettop(L) < stackIdx) {
			std::println("[ERR] [LUAU] Index {} of out of stack range ({})", stackIdx, lua_gettop(L));
			return;
		}

		if(!lua_isfunction(L, stackIdx)) {
			std::println("[ERR] [LUAU] Failed to make EventHandler, no function provided");
			return;
		}

		if(eventType == nullptr) {
			std::println("[ERR] [LUAU] Failed to make EventHandler, invalid event class (got nullptr)");
			return;
		}

		if(!eventType->instanceOf(&Event::AEvent::ClassData)) {
			std::println("[ERR] [LUAU] Failed to make EventHandler, invalid event class (not child of AEvent)");
			return;
		}

		lua_pushlightuserdata(L, this);
		lua_pushvalue(L, stackIdx);
		lua_settable(L, LUA_REGISTRYINDEX);

		this->L = L;
	}

	LuauEventHandler::~LuauEventHandler() {
		lua_pushlightuserdata(L, this);
		lua_pushnil(L);
		lua_settable(L, LUA_REGISTRYINDEX);
	}

	void LuauEventHandler::handleEvent(std::shared_ptr<Object> obj, std::shared_ptr<Object> event) const {
		if(!obj->getClass()->instanceOf(&LuauScriptObject::ClassData)) {
			std::println("[ERR] [LUAU] Could not fire event, obj is not a LuauScriptObject");
			return;
		}

		auto engine = LuauScriptEngine::getInstance();

		lua_pushlightuserdata(L, const_cast<LuauEventHandler*>(this));
		lua_gettable(L, LUA_REGISTRYINDEX);

		lua_pushlightuserdata(L, obj.get());
		engine->objectFromVariant(event);
		lua_pcall(L, 2, 0, 0);

		lua_pop(L, 1);
	}
}
