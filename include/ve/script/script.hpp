#pragma once

#include "ve/script/a_script_engine.hpp"
#include <memory>

namespace VoidEngine::Scripts {
	class Script {
	private:
		ByteCode code;
	protected:
		Script(ByteCode);
		ByteCode getByteCode();
	public:
		virtual ~Script();
		virtual void execute() = 0;
		virtual std::shared_ptr<AScriptEngine> getScriptEngine() = 0;
	};
}
