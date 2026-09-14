#pragma once

#include <ve/class_db.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	/*struct EventHandlerBase {
	protected:
		EventHandlerBase(const Class* event) : event(event) {}
	public:
		virtual ~EventHandlerBase() = default;

		const Class* event;
		virtual void handleEvent(std::shared_ptr<Object> obj, std::shared_ptr<Object> event) const = 0;
	};*/
	struct LuaEventHandler final : public EventHandlerBase {
	public:
		LuaEventHandler(const Class* event, int handlerFuncIdx);

		void handleEvent(std::shared_ptr<Object>, std::shared_ptr<Object> event) const;
	};

	struct LuaEventHandlerWrapper final {
		const EventHandlerBase* handler;
	};

	LuaEventHandlerWrapper* lua_pushEventHandlerWrapper(lua_State*);
	LuaEventHandlerWrapper* lua_checkEventHandler(lua_State*, int);

	int lua_EventHandlerNew(lua_State*);

	int lua_EventHandler__index(lua_State*);

	int lua_EventHandlerGetEventClass(lua_State*);

	static luaL_Reg eventHandlerLib[] = {
		{ "new", lua_EventHandlerNew },
		
		{ "__index", lua_EventHandler__index },

		{ "getEventClass", lua_EventHandlerGetEventClass },

		{ nullptr, nullptr }
	};

	int luaopen_EventHandler(lua_State*);
}
