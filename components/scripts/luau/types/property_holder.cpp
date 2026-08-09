#include "property_holder.hpp"

#include <print>
#include <string>
#include "object_holder.hpp"
#include "ve/variant.hpp"
#include "../luau_script_engine.hpp"
#include "../luau_property.hpp"

namespace VoidEngine::Scripts::Luau {
	int PropertyNew(lua_State* L) {
		if(!lua_isstring(L, 1)) {
			std::println("[ERR] [LUAU] Property.new arg 0 must be a string");
			return 0;
		}

		if(!lua_isboolean(L, 2)) {
			std::println("[ERR] [LUAU] Property.new arg 1 must be a boolean");
			return 0;
		}

		const char* name = luaL_checkstring(L, 1);
		if(name == nullptr) return 0;

		LuauProperty* ptr = static_cast<LuauProperty*>(lua_newuserdata(L, sizeof(LuauProperty)));
		new (ptr) LuauProperty(name, luaL_checkboolean(L, 2));

		if(luaL_newmetatable(L, "Property")) {
			luaL_register(L, nullptr, propertyMeth);
			lua_pushliteral(L, "Property");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		return 1;
	}

	int PropertyToString(lua_State* L) {
		PropertyHolder* prop = (PropertyHolder*) lua_touserdata(L, 1);
		lua_pushstring(L, prop->prop->name.c_str());
		return 1;
	}

	int PropertyIndex(lua_State* L) {
		PropertyHolder* prop = static_cast<PropertyHolder*>(lua_touserdata(L, 1));
		std::string name = luaL_checkstring(L, 2);
		if(name == "name") {
			lua_pushstring(L, prop->prop->name.c_str());
			return 1;
		}

		return 0;
	}
	
	int PropertyCall(lua_State* L) {
		std::string fnName = lua_namecallatom(L, nullptr);

		if(fnName == "get") return PropertyGet(L);
		if(fnName == "set") return PropertySet(L);
		if(fnName == "isreadonly") return PropertyIsReadOnly(L);

		std::println("[ERR] [LUAU] No function named \"{}\" on Property", fnName);
		return 0;
	}
	
	int PropertyEq(lua_State* L) {
		PropertyHolder* LHS = static_cast<PropertyHolder*>(luaL_checkudata(L, 1, "Property"));
		PropertyHolder* RHS = static_cast<PropertyHolder*>(luaL_checkudata(L, 2, "Property"));

		lua_pushboolean(L, LHS->prop == RHS->prop);
		return 1;
	}

	int PropertyGet(lua_State* L) {
		PropertyHolder* prop = static_cast<PropertyHolder*>(lua_touserdata(L, 1));
		ObjectHolder* obj = static_cast<ObjectHolder*>(luaL_checkudata(L, 2, "Object"));

		Variant retVal = prop->prop->get(obj->obj);
		LuauScriptEngine::getInstance()->objectFromVariant(retVal);
		return 1;
	}

	int PropertySet(lua_State* L) {
		PropertyHolder* prop = static_cast<PropertyHolder*>(lua_touserdata(L, 1));
		ObjectHolder* obj = static_cast<ObjectHolder*>(luaL_checkudata(L, 2, "Object"));

		uint32_t* val = new uint32_t(3);
		Variant value = LuauScriptEngine::getInstance()->objectToVariant(val);
		delete val;

		prop->prop->set(obj->obj, value);
		return 0;
	}
	
	int PropertyIsReadOnly(lua_State* L) {
		PropertyHolder* prop = static_cast<PropertyHolder*>(lua_touserdata(L, 1));
		lua_pushboolean(L, prop->prop->isReadOnly());
		return 1;
	}

}
