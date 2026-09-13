#include "api/lua_function.hpp"
#include "lauxlib.h"
#include "ve/class_db.hpp"
#include <api/lua_class.hpp>
#include <api/lua_constructor.hpp>

#include <ve/object.hpp>

#include <print>
#include <vector>

namespace VoidEngine::Scripts::Lua::API {
	int lua_ClassNew(lua_State* state) {
		if(!lua_isstring(state, 1)) {
			lua_pushstring(state, "Arg 0 of Class.new must be a string");
			lua_error(state);
			return 0;
		}

		LuaClassWrapper* super = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 2, "Class"));

		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(lua_newuserdata(state, sizeof(LuaClassWrapper)));
		luaL_getmetatable(state, "Class");
		lua_setmetatable(state, -2);

		cls->cls = new Class;
		const_cast<Class*>(cls->cls)->name = luaL_checkstring(state, 1);
		const_cast<Class*>(cls->cls)->super = super->cls;
		return 1;
	}

	int lua_ClassGet(lua_State* state) {
		if(!lua_isstring(state, 1)) {
			lua_pushstring(state, "Arg 0 of Class.get must be a string");
			lua_error(state);
			return 0;
		}

		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(lua_newuserdata(state, sizeof(LuaClassWrapper)));
		luaL_getmetatable(state, "Class");
		lua_setmetatable(state, -2);

		std::string clsName = luaL_checkstring(state, 1);

		cls->cls = ClassDB::getInstance()->getClassByName(clsName);
		return 1;
	}

	int lua_ClassRegister(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		ClassDB::getInstance()->registerClass(cls->cls);
		return 0;
	}

	int lua_ClassIsAbstract(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		lua_pushboolean(state, cls->cls->isAbstract());
		return 1;
	}
	
	int lua_ClassSetConstructor(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaConstructorWrapper* ctor = static_cast<LuaConstructorWrapper*>(luaL_checkudata(state, 2, "Constructor"));
		const_cast<LuaConstructor*>(static_cast<const LuaConstructor*>(ctor->ctor))->cls = cls->cls;
		const_cast<Class*>(cls->cls)->constructor = ctor->ctor;
		return 0;
	}

	int lua_ClassGetConstructor(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		if(cls->cls->constructor == nullptr) {
			lua_pushnil(state);
			return 1;
		}

		LuaConstructorWrapper* wrapper = static_cast<LuaConstructorWrapper*>(lua_newuserdata(state, sizeof(LuaConstructorWrapper)));
		wrapper->ctor = cls->cls->constructor;

		luaL_getmetatable(state, "Constructor");
		lua_setmetatable(state, -2);
		
		return 1;
	}

	int lua_ClassInstanceOf(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaClassWrapper* other = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 2, "Class"));
		lua_pushboolean(state, cls->cls->instanceOf(other->cls));
		return 1;
	}

	int lua_ClassGetSuper(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaClassWrapper* super = static_cast<LuaClassWrapper*>(lua_newuserdata(state, sizeof(LuaClassWrapper)));
		super->cls = cls->cls->getSuper();
		luaL_getmetatable(state, "Class");
		lua_setmetatable(state, -2);
		return 1;
	}

	int lua_ClassGetName(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		lua_pushstring(state, cls->cls->getName());
		return 1;
	}

	int lua_ClassAddFunction(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaFunctionWrapper* function = static_cast<LuaFunctionWrapper*>(luaL_checkudata(state, 2, "Function"));

		auto methods = const_cast<std::vector<const MethodBase*>*>(&self->cls->methods);
		methods->push_back(function->method);

		std::println("Added function");

		return 0;
	}

	int lua_ClassAddProperty(lua_State* state) {
		std::println("[WARN] [Lua] NYI");
		return 0;
	}

	int lua_ClassAddEventHandler(lua_State* state) {
		std::println("[WARN] [Lua] NYI");
		return 0;
	}

	int lua_Class__tostring(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_testudata(state, 1, "Class"));
		if(cls == nullptr) {
			lua_pushstring(state, "how?");
			lua_error(state);
			return 0;
		}

		lua_pushstring(state, std::format("Class: {}", cls->cls->getName()).c_str());
		return 1;
	}

	int lua_Class__index(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_testudata(state, 1, "Class"));
		if (cls == nullptr) {
			lua_pushstring(state, "how?");
			lua_error(state);
			return 0;
		}

		std::string idxName = lua_tostring(state, 2);
		if(idxName == "register") lua_pushcfunction(state, lua_ClassRegister);
		else if(idxName == "isAbstract") lua_pushcfunction(state, lua_ClassIsAbstract);
		else if(idxName == "setConstructor") lua_pushcfunction(state, lua_ClassSetConstructor);
		else if(idxName == "getConstructor") lua_pushcfunction(state, lua_ClassGetConstructor);
		else if(idxName == "instanceOf") lua_pushcfunction(state, lua_ClassInstanceOf);
		else if(idxName == "getSuper") lua_pushcfunction(state, lua_ClassGetSuper);
		else if(idxName == "getName") lua_pushcfunction(state, lua_ClassGetName);
		else if(idxName == "addProperty") lua_pushcfunction(state, lua_ClassAddProperty);
		else if(idxName == "addFunction") lua_pushcfunction(state, lua_ClassAddFunction);
		else if(idxName == "addEventHandler") lua_pushcfunction(state, lua_ClassAddEventHandler);
		else {
			lua_pushstring(state, std::format("Class does not have entry: {}", idxName).c_str());
			lua_error(state);
			return 0;
		}

		return 1;
	}

	int lua_Class__eq(lua_State* state) {
		LuaClassWrapper* RHS = static_cast<LuaClassWrapper*>(luaL_testudata(state, 2, "Class"));
		if(RHS == nullptr) {
			lua_pushboolean(state, false);
			return 1;
		}

		LuaClassWrapper* LHS = static_cast<LuaClassWrapper*>(luaL_testudata(state, 1, "Class"));
		if(LHS == nullptr) {
			lua_pushboolean(state, false);
			return 1;
		}

		lua_pushboolean(state, LHS->cls == RHS->cls);
		return 1;
	}

	int luaopen_Class(lua_State* state) {
		luaL_newmetatable(state, "Class");
		luaL_setfuncs(state, classLib, 0);
		lua_setglobal(state, "Class");
		return 0;
	}
}