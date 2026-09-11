#include <api/lua_constructor.hpp>

namespace VoidEngine::Scripts::Lua::API {
	LuaConstructor::LuaConstructor(lua_State* state, int funcIdx) {
		lua_pushlightuserdata(state, this);
		lua_pushvalue(state, funcIdx);
		lua_settable(state, LUA_REGISTRYINDEX);
	}

	std::shared_ptr<Object> LuaConstructor::create() const {
		return nullptr;
	}

	int lua_ConstructorNew(lua_State* state) {
		if(!lua_isfunction(state, 1)) {
			lua_pushstring(state, "Arg 0 of Constructor.new must be a lua function");
			lua_error(state);
			return 0;
		}

		LuaConstructorWrapper* wrapper = static_cast<LuaConstructorWrapper*>(
			lua_newuserdata(state, sizeof(LuaConstructorWrapper))
		);
		wrapper->ctor = new LuaConstructor(state, 1);

		luaL_getmetatable(state, "Constructor");
		lua_setmetatable(state, -2);

		return 1;
	}

	int lua_Constructor__tostring(lua_State* state) {
		lua_pushstring(state, "Constructor");
		return 1;
	}

	int lua_Constructor__index(lua_State* state) {
		return 0;
	}

	int lua_Constructor__eq(lua_State* state) {
		LuaConstructorWrapper* RHS = static_cast<LuaConstructorWrapper*>(
			luaL_testudata(state, 2, "Constructor")
		);
		if(RHS == nullptr) {
			lua_pushboolean(state, false);
			return 1;
		}

		LuaConstructorWrapper* LHS = static_cast<LuaConstructorWrapper*>(
			luaL_testudata(state, 1, "Constructor")
		);
		if(LHS == nullptr) {
			lua_pushboolean(state, false);
			return 1;
		}

		lua_pushboolean(state, LHS->ctor == RHS->ctor);
		return 1;
	}

	int luaopen_Constructor(lua_State* state) {
		luaL_newmetatable(state, "Constructor");
		luaL_setfuncs(state, constructorLib, 0);
		lua_setglobal(state, "Constructor");
		return 0;
	}
}