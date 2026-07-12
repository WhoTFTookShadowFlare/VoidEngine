#include "luau_script.hpp"
#include "lua.h"
#include "luau_script_engine.hpp"
#include "ve/script/script.hpp"
#include <memory>


namespace VoidEngine::Scripts::Luau {
	LuauScript::LuauScript(ByteCode code) : Script(code) {	}

	std::shared_ptr<LuauScript> LuauScript::create(ByteCode code) {
		return std::shared_ptr<LuauScript>(new LuauScript(code));
	}

	std::shared_ptr<AScriptEngine> LuauScript::getScriptEngine() { return LuauScriptEngine::getInstance(); }

	void LuauScript::execute() {
		auto vmState = LuauScriptEngine::getInstance()->vmState;
		if(!luau_load(vmState, "<unknown>", (const char*) getByteCode().code, getByteCode().size, 0))
			lua_pcall(vmState, 0, 0, 0);
	}
}
