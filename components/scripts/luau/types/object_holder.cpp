#include "object_holder.hpp"

#include "../luau_script_engine.hpp"
#include <lua.h>
#include <lualib.h>
#include <print>
#include "ve/variant.hpp"

namespace VoidEngine::Scripts::Luau {
	int ObjectNew(lua_State* L) {
		if(!lua_isstring(L, 1)) {
			std::println("[ERR] [LUAU] Object.new takes only a string for class type");
			return 0;
		}

		const char* type = luaL_checkstring(L, 1);
		if(type == nullptr) return 0;

		auto cls = ClassDB::getInstance()->getClassByName(type);
		if(cls == nullptr) return 0;
		if(cls->isAbstract()) return 0;
		
		ObjectHolder* ptr = static_cast<ObjectHolder*>(lua_newuserdatadtor(L, sizeof(ObjectHolder), [](void* ptr) {
			ObjectHolder* self = static_cast<ObjectHolder*>(ptr);
			self->obj.~shared_ptr<Object>();
		}));

		if(luaL_newmetatable(L, "Object")) {
			luaL_register(L, nullptr, objectMeth);
			lua_pushliteral(L, "Object");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		new(&ptr->obj) std::shared_ptr<Object>(cls->constructor->create());

		return 1;
	}

	int ObjectToString(lua_State* L) {
		ObjectHolder* obj = static_cast<ObjectHolder*>(lua_touserdata(L, 1));
		lua_pushstring(L, obj->obj->getClass()->name);
		return 1;
	}

	int ObjectGet(lua_State* L) {
		ObjectHolder* obj = static_cast<ObjectHolder*>(lua_touserdata(L, 1));
		const char* key = luaL_checkstring(L, 2);
		if(key == nullptr) return 0;

		auto cls = obj->obj->getClass();
		if(cls == nullptr) return 0;
		auto property = cls->findProperty(key);
		if(property == nullptr) return 0;
		LuauScriptEngine::getInstance()->objectFromVariant(property->get(obj->obj));

		return 1;
	}

	int ObjectSet(lua_State* L) {
		ObjectHolder* obj = static_cast<ObjectHolder*>(lua_touserdata(L, 1));
		const char* key = luaL_checkstring(L, 2);
		if(key == nullptr) return 0;

		auto cls = obj->obj->getClass();
		if(cls == nullptr) return 0;
		auto property = cls->findProperty(key);
		if(property == nullptr) return 0;
		if(property->isReadOnly()) return 0;

		int32_t* idx = new int32_t(3);
		Variant value = LuauScriptEngine::getInstance()->objectToVariant(idx);
		delete idx;

		property->set(obj->obj, value);
		return 0;
	}

	int ObjectCall(lua_State* L) {
		ObjectHolder* obj = static_cast<ObjectHolder*>(lua_touserdata(L, 1));
		const char* key = lua_namecallatom(L, nullptr);
		if(key == nullptr) return 0;

		auto meth = obj->obj->getClass()->findMethod(key);
		if(meth == nullptr) return 0;

		auto engine = LuauScriptEngine::getInstance();
		int32_t* stackIndex = new int32_t(1);
		std::vector<Variant> args;
		for(int32_t arg = 1; arg < lua_gettop(L); arg++) {
			*stackIndex = arg + 1;
			args.push_back(engine->objectToVariant(stackIndex));
		}
		delete stackIndex;

		Variant retVal = meth->call(obj->obj, args);
		if(retVal.isNil()) return 0;
		engine->objectFromVariant(retVal);
		return 1;
	}

	int ObjectEq(lua_State* L) {
		if(!lua_istable(L, 2)) {
			lua_pushboolean(L, false);
			return 1;
		}

		try {
			ObjectHolder* LHS = static_cast<ObjectHolder*>(luaL_checkudata(L, 1, "Object"));
			ObjectHolder* RHS = static_cast<ObjectHolder*>(luaL_checkudata(L, 2, "Object"));
			lua_pushboolean(L, LHS->obj == RHS->obj);
			return 1;
		} catch(std::exception& ex) {	}

		lua_pushboolean(L, false);
		return 1;
	}
}
