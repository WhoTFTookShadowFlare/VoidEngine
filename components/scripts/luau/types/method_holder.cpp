#include "method_holder.hpp"

#include "object_holder.hpp"
#include "../luau_function.hpp"
#include "../luau_script_engine.hpp"
#include <string>
#include <print>

namespace VoidEngine::Scripts::Luau {
	int MethodNew(lua_State* L) {
		if(!lua_isstring(L, 1)) {
			std::println("[ERR] [LUAU] Method.new arg 0 must be a string");
			return 0;
		}

		if(!lua_isfunction(L, 2)) {
			std::println("[ERR] [LUAU] Method.new arg 1 must be a function");
			return 0;
		}

		const char* name = luaL_checkstring(L, 1);
		if(name == nullptr) return 0;

		LuauMethod* ptr = static_cast<LuauMethod*>(lua_newuserdata(L, sizeof(LuauMethod)));
		new (ptr) LuauMethod(name, L, 2);

		if(luaL_newmetatable(L, "Method")) {
			luaL_register(L, nullptr, methodMeth);
			lua_pushliteral(L, "Method");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		return 1;
	}

	int MethodToString(lua_State* L) {
		MethodHolder* meth = static_cast<MethodHolder*>(lua_touserdata(L, 1));
		lua_pushstring(L, meth->meth->name.c_str());
		return 1;
	}

	int MethodIndex(lua_State* L) {
		MethodHolder* meth = static_cast<MethodHolder*>(lua_touserdata(L, 1));
		std::string name = luaL_checkstring(L, 2);

		if(name == "name") {
			lua_pushstring(L, meth->meth->name.c_str());
			return 1;
		}

		return 0;
	}
	
	int MethodCall(lua_State* L) {
		std::string name = lua_namecallatom(L, nullptr);
		
		if(name == "call") {
			MethodHolder* meth = static_cast<MethodHolder*>(lua_touserdata(L, 1));
			ObjectHolder* obj = static_cast<ObjectHolder*>(luaL_checkudata(L, 2, "Object"));

			std::vector<Variant> args;
			auto engine = LuauScriptEngine::getInstance();
			uint32_t* target = new uint32_t(3);
			for(int idx = 3; idx < lua_gettop(L); idx++) {
				*target = idx;
				args.push_back(engine->objectToVariant(target));
			}
			delete target;

			engine->objectFromVariant(meth->meth->call(obj->obj, args));
			return 1;
		}

		return 0;
	}
	
	int MethodEq(lua_State* L) {
		MethodHolder* LHS = static_cast<MethodHolder*>(luaL_checkudata(L, 1, "Method"));
		MethodHolder* RHS = static_cast<MethodHolder*>(luaL_checkudata(L, 2, "Method"));

		lua_pushboolean(L, LHS->meth == RHS->meth);
		return 1;
	}
}
