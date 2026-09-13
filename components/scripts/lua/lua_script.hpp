#pragma once

#include <ve/script/script.hpp>

namespace VoidEngine::Scripts::Lua {
	class LuaScript final : public Script {
		friend class LuaScriptEngine;
	private:
		LuaScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>);
	public:
		virtual ~LuaScript();

		void execute();
		std::shared_ptr<AScriptEngine> getScriptEngine();
	};
}
