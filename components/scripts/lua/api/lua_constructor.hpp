#pragma once

#include <ve/class_db.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	struct LuaClassWrapper;

	struct LuaConstructor final : public ConstructorBase {
	private:
	public:
		const Class* cls = nullptr;
		LuaConstructor(int funcIdx);

		std::shared_ptr<Object> create() const;
	};

	struct LuaConstructorWrapper final {
		const ConstructorBase* ctor;
	};

	LuaConstructorWrapper* lua_pushConstructorWrapper(lua_State*);
	LuaConstructorWrapper* lua_checkConstructor(lua_State*, int);

	int lua_ConstructorNew(lua_State*);

	int lua_Constructor__tostring(lua_State*);
	int lua_Constructor__index(lua_State*);
	int lua_Constructor__eq(lua_State*);
	int lua_Constructor__call(lua_State*);

	static luaL_Reg constructorLib[] = {
		{ "new", lua_ConstructorNew },

		{ "__tostring", lua_Constructor__tostring },
		{ "__index", lua_Constructor__index },
		{ "__eq", lua_Constructor__eq },
		{ "__call", lua_Constructor__call },

		{ nullptr, nullptr }
	};

	int luaopen_Constructor(lua_State*);
}
