#pragma once

#include "ve/object.hpp"
#include "ve/script/a_script_engine.hpp"
#include "ve/script/a_script_object.hpp"
#include "ve/variant.hpp"
#include <vector>

namespace VoidEngine::Scripts::Luau {
	class LuauScriptObject final : public AScriptObject {
		friend class LuauScriptModule;
		VE_CLASS(LuauScriptObject)
	private:
		LuauScriptObject();
	public:
		~LuauScriptObject();
		std::shared_ptr<AScriptEngine> getScriptEngine() override;
		Variant call(std::string fnName, std::vector<Variant> args) override;
		Variant get(std::string name) override;
		void set(std::string name, Variant value) override;

		std::vector<std::string> getFunctions() override;
		std::vector<std::string> getProperties() override;
	};
}