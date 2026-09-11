#include <api/lua_object_script.hpp>

#include <lua_script_engine.hpp>

namespace VoidEngine::Scripts::Lua::API {
	LuaObjectScript::LuaObjectScript(lua_State* state, int objIdx, const Class* cls) {
		this->cls = cls;
		this->state = lua_newthread(state);
		lua_pushlightuserdata(this->state, this);
		lua_pushvalue(state, objIdx);
		lua_xmove(state, this->state, 1);
		lua_settable(this->state, LUA_REGISTRYINDEX);
	}
	
	LuaObjectScript::~LuaObjectScript() {
		lua_pushlightuserdata(state, this);
		lua_pushnil(state);
		lua_settable(state, LUA_REGISTRYINDEX);
		lua_close(state);
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
