#pragma once

#include "lua.h"
#include "ve/script/a_script_engine.hpp"
#include <memory>

namespace VoidEngine::Scripts::Luau {
	class LuauScriptEngine final : public AScriptEngine {
		friend class LuauScript;
	private:
		static std::shared_ptr<LuauScriptEngine> instance;

		lua_State* vmState = nullptr;

		LuauScriptEngine();
	public:
		~LuauScriptEngine();
		static std::shared_ptr<LuauScriptEngine> getInstance();

		std::shared_ptr<Script> compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>);

		Variant objectToVariant(void*);
		void* objectFromVariant(Variant);
	};
}
