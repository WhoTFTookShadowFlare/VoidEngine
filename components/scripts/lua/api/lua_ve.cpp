#include "lua_ve.hpp"

#include "lua_class.hpp"
#include "lua_object.hpp"
#include "lua_object_script.hpp"

namespace VoidEngine::Scripts::Lua::API {
	int lua_VE_wrapObject(lua_State* state) {
		if(!lua_istable(state, 1)) {
			luaL_argerror(state, 1, "Table expected");
			return 0;
		}
		const Class* cls = lua_checkClass(state, 2)->cls;

		if (cls->getSuper()->isAbstract()) {
			luaL_argerror(state, 2, "Parent class is missing a constructor");
			return 0;
		}

		std::shared_ptr<Object> obj = cls->getSuper()->constructor->create();
		LuaObjectWrapper* objWrap = lua_pushObjectWrapper(state);
		objWrap->object = obj;
		obj->setScript(std::shared_ptr<LuaObjectScript>(new LuaObjectScript(1, cls)));

		return 1;
	}

	int luaopen_VE(lua_State* state) {
		luaL_newmetatable(state, "VE");
		luaL_setfuncs(state, VELib, 0);
		lua_setglobal(state, "VE");
		return 0;
	}
}
