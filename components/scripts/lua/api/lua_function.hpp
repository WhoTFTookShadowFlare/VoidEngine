#pragma once

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


#include "ve/object.hpp"
#include "ve/variant.hpp"
#include <memory>
#include <ve/class_db.hpp>
#include <vector>

namespace VoidEngine::Scripts::Lua::API {
	struct LuaFunction final : public MethodBase {
		public:
			virtual ~LuaFunction();
			LuaFunction(std::string name, int funcIdx);

			Variant call(std::shared_ptr<Object> obj, std::vector<Variant> args) const;
	};

	struct LuaFunctionWrapper final {
		const MethodBase* method;
	};

	LuaFunctionWrapper* lua_pushfunctionwrapper(lua_State*);

	int lua_FunctionNew(lua_State*);

	int lua_Function__index(lua_State*);
	int lua_Function__tostring(lua_State*);
	int lua_Function__eq(lua_State*);
	int lua_Function__call(lua_State*);

	static luaL_Reg functionLib[] = {
		{ "new", lua_FunctionNew },

		{ "__index", lua_Function__index },
		{ "__tostring", lua_Function__tostring },
		{ "__eq", lua_Function__eq },
		{ "__call", lua_Function__call },

		{ nullptr, nullptr }
	};

	int luaopen_Function(lua_State* state);
}