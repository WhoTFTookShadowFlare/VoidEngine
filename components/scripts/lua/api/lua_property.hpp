#pragma once

#include <cstdint>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <ve/object.hpp>
#include "ve/class_db.hpp"

namespace VoidEngine::Scripts::Lua::API {
	struct LuaProperty final : PropertyBase {
	private:
	public:
		const uint8_t SETTER_OFFSET = 1;

		LuaProperty(std::string name, int getIdx, int setIdx = 0);

		Variant get(std::shared_ptr<Object>) const;
		void set(std::shared_ptr<Object>, Variant) const;
		bool isReadOnly() const;
	};

	struct LuaPropertyWrapper final {
		const PropertyBase* property;
	};

	LuaPropertyWrapper* lua_pushpropertywrapper(lua_State*);

	int lua_PropertyNew(lua_State*);

	int lua_Property__index(lua_State*);
	int lua_Property__tostring(lua_State*);
	int lua_Property__eq(lua_State*);

	int lua_PropertyGetName(lua_State*);
	int lua_PropertyIsReadOnly(lua_State*);

	static luaL_Reg propertyLib[] = {
		{ "new", lua_PropertyNew },
		
		{ "__index", lua_Property__index },
		{ "__tostring", lua_Property__tostring },
		{ "__eq", lua_Property__eq },

		{ "getName", lua_PropertyGetName },
		{ "isReadOnly", lua_PropertyIsReadOnly },

		{ nullptr, nullptr }
	};

	int luaopen_Property(lua_State*);
}