#include <api/lua_struct.hpp>

#include <lua_script_engine.hpp>

namespace VoidEngine::Scripts::Lua::API {
	LuaStructWrapper* lua_pushStructWrapper(lua_State* state) {
		LuaStructWrapper* struc = static_cast<LuaStructWrapper*>(lua_newuserdata(state, sizeof(LuaStructWrapper)));
		luaL_getmetatable(state, "Struct");
		lua_setmetatable(state, -2);
		new (struc) LuaStructWrapper;
		return struc;
	}

	LuaStructWrapper* lua_checkStruct(lua_State* state, int idx) {
		return static_cast<LuaStructWrapper*>(luaL_checkudata(state, idx, "Struct"));
	}

	int lua_Struct__index(lua_State* state) {
		LuaStructWrapper* struc = lua_checkStruct(state, 1);
		std::string idxName = luaL_checkstring(state, 2);

		LuaScriptEngine::getInstance()->objectFromVariant(struc->struc->get(idxName));
		return 1;
	}
	
	int lua_Struct__newindex(lua_State* state) {
		LuaStructWrapper* struc = lua_checkStruct(state, 1);
		std::string idxName = luaL_checkstring(state, 2);

		int target = 3;
		Variant value = LuaScriptEngine::getInstance()->objectToVariant(&target);
		struc->struc->set(idxName, value);
		return 0;
	}
	
	int lua_Struct__tostring(lua_State* state) {
		LuaStructWrapper* struc = lua_checkStruct(state, 1);
		lua_pushstring(state, struc->struc->getData()->name.c_str());
		return 1;
	}
	
	int lua_Struct__eq(lua_State* state) {
		LuaStructWrapper* LHS = lua_checkStruct(state, 1);
		LuaStructWrapper* RHS = lua_checkStruct(state, 2);
		//lua_pushboolean(state, LHS->struc == RHS->struc);
		lua_pushstring(state, "operator == is not implemented");
		lua_error(state);
		return 1;
	}

	int luaopen_Struct(lua_State* state) {
		luaL_newmetatable(state, "Struct");
		luaL_setfuncs(state, structLib, 0);
		lua_setglobal(state, "Struct");
		return 0;
	}
}
