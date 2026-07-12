#pragma once

#include "ve/script/a_script_engine.hpp"
#include "ve/script/script.hpp"

namespace VoidEngine::Scripts::Luau {
	class LuauScript final : public Script {
	private:
		LuauScript(ByteCode);
	public:
		static std::shared_ptr<LuauScript> create(ByteCode);

		void execute();
		std::shared_ptr<AScriptEngine> getScriptEngine();
	};
}
