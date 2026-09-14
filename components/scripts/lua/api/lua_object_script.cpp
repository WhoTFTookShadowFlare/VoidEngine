#include <api/lua_object_script.hpp>

#include <lua_script_engine.hpp>
#include <print>

namespace VoidEngine::Scripts::Lua::API {
	LuaObjectScript::LuaObjectScript(int objIdx, const Class* cls) {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		this->cls = cls;
		lua_pushlightuserdata(state, this);
		lua_pushvalue(state, (objIdx < 0) ? objIdx - 1: objIdx);
		lua_settable(state, LUA_REGISTRYINDEX);
	}
	
	LuaObjectScript::~LuaObjectScript() {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		//lua_pushlightuserdata(state, this);
		//lua_pushnil(state);
		//lua_settable(state, LUA_REGISTRYINDEX);
	}

	std::shared_ptr<AScriptEngine> LuaObjectScript::getScriptEngine() {
		return LuaScriptEngine::getInstance();
	}

	const Class* LuaObjectScript::getClass() {
		return cls;
	}

	Variant LuaObjectScript::call(std::string fnName, std::vector<Variant> args) {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		return nullptr;
	}
	
	Variant LuaObjectScript::get(std::string name) {
		return nullptr;
	}
	
	void LuaObjectScript::set(std::string name, Variant) {
		return;
	}

	std::vector<std::string> LuaObjectScript::getFunctions() {
		return {};
	}
	
	std::vector<std::string> LuaObjectScript::getProperties() {
		return {};
	}

	void LuaObjectScript::pushObject(lua_State* state) {
		lua_pushlightuserdata(state, this);
		lua_gettable(state, LUA_REGISTRYINDEX);
	}
}
