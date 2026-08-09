#include "event_bus.hpp"

#include "class_holder.hpp"
#include "ve/class_db.hpp"
#include <print>
#include <string>

namespace VoidEngine::Scripts::Luau {
	int EventBusNew(lua_State* L) {
		const Class* cls = nullptr;
		if(lua_isstring(L, 1)) {
			cls = ClassDB::getInstance()->getClassByName(luaL_checkstring(L, 1));
		} else {
			cls = static_cast<ClassHolder*>(luaL_checkudata(L, 1, "Class"))->cls;
		}

		if(cls == nullptr) {
			std::println("[ERR] [LUAU] Cannot make an EventBus without a class of type AEvent");
			return 0;
		}

		if(!cls->instanceOf(&Event::AEvent::ClassData)) {
			std::println("[ERR] [LUAU] Cannot make an EventBus without a class of type AEvent");
			return 0;
		}

		EventBusHolder* holder = static_cast<EventBusHolder*>(lua_newuserdatadtor(L, sizeof(EventBusHolder), [](void* ptr) {
			EventBusHolder* busHolder = static_cast<EventBusHolder*>(ptr);
			delete busHolder->bus;
		}));

		holder->bus = new Event::EventBus(cls);
		
		if(luaL_newmetatable(L, "EventBus")) {
			luaL_register(L, nullptr, eventBusMeth);
			lua_pushliteral(L, "EventBus");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		return 1;
	}

	int EventBusCall(lua_State* L) {
		std::string fnName = lua_namecallatom(L, nullptr);

		if(fnName == "addhandler") return EventBusAddHandler(L);
		if(fnName == "removehandler") return EventBusRemoveHandler(L);
		if(fnName == "hashandler") return EventBusHasHandler(L);
		if(fnName == "fireevent") return EventBusFireEvent(L);

		return 0;
	}

	int EventBusAddHandler(lua_State* L) {
		return 0;
	}

	int EventBusRemoveHandler(lua_State* L) {
		return 0;
	}

	int EventBusHasHandler(lua_State* L) {
		lua_pushboolean(L, false);
		return 1;
	}

	int EventBusFireEvent(lua_State* L) {
		return 0;
	}
}