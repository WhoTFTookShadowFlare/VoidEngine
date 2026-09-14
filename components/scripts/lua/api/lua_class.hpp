#pragma once

#include <ve/class_db.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	struct LuaClassWrapper {
		const Class* cls;
	};

	LuaClassWrapper* lua_pushClassWrapper(lua_State*);
	LuaClassWrapper* lua_checkClass(lua_State*, int);

	int lua_ClassNew(lua_State*);
	int lua_ClassGet(lua_State*);

	int lua_Class__index(lua_State*);
	int lua_Class__tostring(lua_State*);
	int lua_Class__eq(lua_State*);
	
	int lua_ClassRegister(lua_State*);
	int lua_ClassCreate(lua_State*);
	int lua_ClassIsAbstract(lua_State*);
	int lua_ClassSetConstructor(lua_State*);
	int lua_ClassGetConstructor(lua_State*);
	int lua_ClassInstanceOf(lua_State*);
	int lua_ClassGetSuper(lua_State*);
	int lua_ClassGetName(lua_State*);

	int lua_ClassGetProperties(lua_State*);
	int lua_ClassGetFunctions(lua_State*);
	int lua_ClassGetEventHandlers(lua_State*);

	int lua_ClassFindProperty(lua_State*);
	int lua_ClassFindFunction(lua_State*);
	int lua_ClassFindEventHandler(lua_State*);

	int lua_ClassAddProperty(lua_State*);
	int lua_ClassAddFunction(lua_State*);
	int lua_ClassAddEventHandler(lua_State*);

	static luaL_Reg classLib[] = {
		{ "new", lua_ClassNew },
		{ "get", lua_ClassGet },

		{ "__index", lua_Class__index },
		{ "__tostring", lua_Class__tostring },
		{ "__eq", lua_Class__eq },

		{ "register", lua_ClassRegister },
		{ "create", lua_ClassCreate },
		{ "isAbstract", lua_ClassIsAbstract },
		{ "setConstructor", lua_ClassSetConstructor },
		{ "getConstructor", lua_ClassGetConstructor },
		{ "instanceOf", lua_ClassInstanceOf },
		{ "getSuper", lua_ClassGetSuper },
		{ "getName", lua_ClassGetName },
		{ "getProperties", lua_ClassGetProperties },
		{ "getFunctions", lua_ClassGetProperties },
		{ "getEventHandlers", lua_ClassGetEventHandlers },
		{ "findProperty", lua_ClassFindProperty },
		{ "findFunction", lua_ClassFindFunction },
		{ "findEventHandler", lua_ClassFindEventHandler },
		{ "addProperty", lua_ClassAddProperty },
		{ "addFunction", lua_ClassAddFunction },
		{ "addEventHandler", lua_ClassAddEventHandler },

		{ nullptr, nullptr }
	};

	int luaopen_Class(lua_State*);
}
