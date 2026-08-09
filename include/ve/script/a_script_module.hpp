#pragma once

#include "ve/script/a_script_engine.hpp"
#include "ve/script/a_script_object.hpp"
#include "ve/variant.hpp"
#include <memory>
#include <vector>

namespace VoidEngine::Scripts {
	class AScriptEngine;

	class AScriptModule {
	private:
		ByteCode code;
	protected:
		AScriptModule(ByteCode code) : code(code) {}
		ByteCode getByteCode() { return code; }
	public:
		virtual ~AScriptModule() {}
		virtual std::shared_ptr<AScriptEngine> getScriptEngine() = 0;

		virtual std::vector<std::string> getFunctions() = 0;
		virtual Variant call(std::string fnName, std::vector<Variant> args) = 0;
		virtual std::shared_ptr<AObjectScript> instanceObject() = 0;
	};
}
