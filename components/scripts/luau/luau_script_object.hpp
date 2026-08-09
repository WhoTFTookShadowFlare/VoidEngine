#pragma once

#include "ve/script/a_script_engine.hpp"
#include "ve/script/a_script_object.hpp"
#include "ve/variant.hpp"
#include <vector>

namespace VoidEngine::Scripts::Luau {
	class LuauObjectScript final : public AObjectScript {
		friend class LuauScriptModule;
	private:
		LuauObjectScript();
	public:
		~LuauObjectScript();
		std::shared_ptr<AScriptEngine> getScriptEngine() override;
		const Class* getClass() override;
		Variant call(std::string fnName, std::vector<Variant> args) override;
		Variant get(std::string name) override;
		void set(std::string name, Variant value) override;

		std::vector<std::string> getFunctions() override;
		std::vector<std::string> getProperties() override;
	};
}