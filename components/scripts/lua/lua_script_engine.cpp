#include <lua_script_engine.hpp>

#include <print>
#include <lua_script.hpp>
#include <lua_module.hpp>

namespace VoidEngine::Scripts::Lua {
	std::shared_ptr<LuaScriptEngine> LuaScriptEngine::instance = nullptr;

	LuaScriptEngine::LuaScriptEngine() {
		assert(instance == nullptr);

		std::println("[WARN] The lua script engine is still in development, expect issues");
		state = luaL_newstate();

		setupNativeTypes();

		luaL_openlibs(state);
		//luaL_sandbox(state); // TODO: sandbox lua
	}

	LuaScriptEngine::~LuaScriptEngine() {
		lua_close(state);
	}

	std::shared_ptr<LuaScriptEngine> LuaScriptEngine::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<LuaScriptEngine>(new LuaScriptEngine);
		return instance;
	}

	void LuaScriptEngine::setupNativeTypes() {}

	std::string LuaScriptEngine::getLanguage() { return "lua"; }

	std::shared_ptr<Script> LuaScriptEngine::compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider> src) {
		return std::shared_ptr<LuaScript>(new LuaScript(src));
	}

	std::shared_ptr<AScriptModule> LuaScriptEngine::compileModuleScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider> src) {
		return std::shared_ptr<LuaModule>(new LuaModule(src));
	}

	Variant LuaScriptEngine::objectToVariant(void*) {
		std::println("[WARN] Cannot convert lua object to a Variant, NYI");
		return nullptr;
	}

	void* LuaScriptEngine::objectFromVariant(Variant value) {
		switch(value.getType()) {
		case VariantType::NIL:
			lua_pushnil(state);
			break;
		case VariantType::INT:
			lua_pushinteger(state, value.asInt().value());
			break;
		case VariantType::FLOAT:
			lua_pushnumber(state, value.asFloat().value());
			break;
		case VariantType::BOOL:
			lua_pushboolean(state, value.asBool().value());
			break;
		case VariantType::STRING:
			lua_pushstring(state, value.asString().value().c_str());
			break;
			//ARRAY,
			//MAP,
		default:
			std::println("[ERR] [Lua] Cannot convert Variant type {}, pushing nil", (int) value.getType());
			lua_pushnil(state);
		}
		return nullptr;
	}
}
