#include <api/lua_object_script.hpp>

#include <lua_script_engine.hpp>

namespace VoidEngine::Scripts::Lua::API {
	LuaObjectScript::LuaObjectScript(int objIdx, const Class* cls) {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		this->cls = cls;
		lua_pushlightuserdata(state, this);
		lua_pushvalue(state, objIdx);
		lua_settable(state, LUA_REGISTRYINDEX);
	}
	
	LuaObjectScript::~LuaObjectScript() {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		lua_pushlightuserdata(state, this);
		lua_pushnil(state);
		lua_settable(state, LUA_REGISTRYINDEX);
	}

	std::shared_ptr<AScriptEngine> LuaObjectScript::getScriptEngine() {
		return LuaScriptEngine::getInstance();
	}

	const Class* LuaObjectScript::getClass() {
		return cls;
	}

	Variant LuaObjectScript::call(std::string fnName, std::vector<Variant> args) {
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
}
