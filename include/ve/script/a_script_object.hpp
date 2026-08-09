#pragma once

#include "ve/variant.hpp"
#include "ve/class_db.hpp"
#include <memory>
#include <string>
#include <vector>

namespace VoidEngine::Scripts {
	class AScriptEngine;

	class AObjectScript {
	private:
	protected:
	public:
		virtual ~AObjectScript() {}
		virtual std::shared_ptr<AScriptEngine> getScriptEngine() = 0;

		virtual const Class* getClass() = 0;

		virtual Variant call(std::string fnName, std::vector<Variant> args) = 0;
		virtual Variant get(std::string name) = 0;
		virtual void set(std::string name, Variant) = 0;

		virtual std::vector<std::string> getFunctions() = 0;
		virtual std::vector<std::string> getProperties() = 0;
	};
}
