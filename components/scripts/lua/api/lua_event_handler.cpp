#include <api/lua_event_handler.hpp>
#include <api/lua_class.hpp>
#include <api/lua_object.hpp>

#include <lua_script_engine.hpp>

namespace VoidEngine::Scripts::Lua::API {
	LuaEventHandler::LuaEventHandler(const Class* event, int handlerFuncIdx)
		: EventHandlerBase(event)
	{
		lua_State* state = LuaScriptEngine::getInstance()->state;
		lua_pushlightuserdata(state, this);
		lua_pushvalue(state, (handlerFuncIdx < 0) ? handlerFuncIdx - 1 : handlerFuncIdx);
		lua_settable(state, LUA_REGISTRYINDEX);
	}

	void LuaEventHandler::handleEvent(std::shared_ptr<Object> object, std::shared_ptr<Object> event) const {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		lua_pushlightuserdata(state, const_cast<LuaEventHandler*>(this));
		lua_gettable(state, LUA_REGISTRYINDEX);

		LuaObjectWrapper* objectWrapper = lua_pushObjectWrapper(state);
		objectWrapper->object = object;

		LuaObjectWrapper* eventWrapper = lua_pushObjectWrapper(state);
		eventWrapper->object = event;

		if(lua_pcall(state, 2, 0, 0) != 0) {
			std::string err = luaL_checkstring(state, -1);
			std::println("[ERR] [Lua] {}", err);
		}
	}

	LuaEventHandlerWrapper* lua_pushEventHandlerWrapper(lua_State* state) {
		LuaEventHandlerWrapper* handler = static_cast<LuaEventHandlerWrapper*>(
			lua_newuserdata(state, sizeof(LuaEventHandlerWrapper))
		);
		luaL_getmetatable(state, "EventHandler");
		lua_setmetatable(state, -2);
		return handler;
	}

	LuaEventHandlerWrapper* lua_checkEventHandler(lua_State* state, int idx) {
		return static_cast<LuaEventHandlerWrapper*>(luaL_checkudata(state, idx, "EventHandler"));
	}

	int lua_EventHandlerNew(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);
		luaL_checktype(state, 2, LUA_TFUNCTION);

		LuaEventHandlerWrapper* handler = lua_pushEventHandlerWrapper(state);
		handler->handler = new LuaEventHandler(cls->cls, 2);
		return 1;
	}

	int lua_EventHandler__index(lua_State* state) {
		LuaEventHandlerWrapper* handler = lua_checkEventHandler(state, 1);

		std::string idxName = lua_tostring(state, 2);
		lua_getmetatable(state, 1);
		lua_getfield(state, -1, idxName.c_str());
		return 1;
	}

	int lua_EventHandlerGetEventClass(lua_State* state) {
		LuaEventHandlerWrapper* handler = static_cast<LuaEventHandlerWrapper*>(
			luaL_checkudata(state, 1, "EventHandler")
		);

		LuaClassWrapper* cls = lua_pushClassWrapper(state);
		cls->cls = handler->handler->getEventClass();
		return 1;
	}

	int luaopen_EventHandler(lua_State* state) {
		luaL_newmetatable(state, "EventHandler");
		luaL_setfuncs(state, eventHandlerLib, 0);
		lua_setglobal(state, "EventHandler");
		return 0;
	}
}
