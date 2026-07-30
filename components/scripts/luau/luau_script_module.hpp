#pragma once

#include "ve/script/a_script_engine.hpp"
#include "ve/script/a_script_module.hpp"
#include <memory>
#include <vector>

namespace VoidEngine::Scripts::Luau {
	class LuauScriptModule final : public AScriptModule {
	private:
		LuauScriptModule(ByteCode);
	public:
		static std::shared_ptr<LuauScriptModule> create(ByteCode);

		std::shared_ptr<AScriptEngine> getScriptEngine();
		std::vector<std::string> getFunctions();
		Variant call(std::string fnName, std::vector<Variant> args);
		std::shared_ptr<AScriptObject> instanceObject();
	};
}
