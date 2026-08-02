#include "luau_function.hpp"
#include "lua.h"
#include "luau_script_engine.hpp"
#include "luau_script_object.hpp"
#include "ve/class_db.hpp"
#include "ve/variant.hpp"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <print>

namespace VoidEngine::Scripts::Luau {
	LuauMethod::LuauMethod(std::string name, lua_State* L, uint32_t stackIdx) : MethodBase(name) {
		this->L = L;

		if(!lua_isfunction(L, stackIdx)) {
			std::println("[ERR] [LUAU] Provided entry was not a function");
		}

		lua_pushlightuserdata(L, this);
		lua_pushvalue(L, stackIdx);
		lua_settable(L, LUA_REGISTRYINDEX);
	}

	LuauMethod::~LuauMethod() {
		lua_pushlightuserdata(L, this);
		lua_pushnil(L);
		lua_settable(L, LUA_REGISTRYINDEX);
	}

	Variant LuauMethod::call(std::shared_ptr<Object> obj, std::vector<Variant> args) const {
		lua_pushlightuserdata(L, const_cast<LuauMethod*>(this));
		lua_gettable(L, LUA_REGISTRYINDEX);

		auto engine = LuauScriptEngine::getInstance();
		if(obj != nullptr && obj->getClass()->instanceOf(&LuauScriptObject::ClassData)) {
			std::shared_ptr<LuauScriptObject> script = std::static_pointer_cast<LuauScriptObject>(obj);
			lua_pushlightuserdata(L, script.get());
			lua_gettable(L, LUA_REGISTRYINDEX);
		}

		std::for_each(args.cbegin(), args.cend(), [&engine](const auto& arg) {
			engine->objectFromVariant(arg);
		});

		lua_pcall(L, args.size() + (obj != nullptr ? 1 : 0), 1, 0);

		uint32_t* target = new uint32_t(lua_gettop(L));
		Variant retVal = engine->objectToVariant(target);
		delete target;

		return retVal;
	}
}
