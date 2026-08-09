#include "luau_property.hpp"
#include "luau_script_engine.hpp"
#include "luau_script_object.hpp"
#include "ve/class_db.hpp"
#include "ve/object.hpp"
#include <memory>
#include <print>

namespace VoidEngine::Scripts::Luau {
	LuauProperty::LuauProperty(std::string name, bool readonly) : PropertyBase(name), readonly(readonly) {}

	Variant LuauProperty::get(std::shared_ptr<Object> object) const {
		if(object == nullptr) return nullptr;
		if(object->getScript() == nullptr) {
			std::println("[ERR] Cannot get property of script class if the object does not have a script");
			return nullptr;
		}

		if(object->getScript()->getScriptEngine() != LuauScriptEngine::getInstance()) {
			std::println("[ERR] Cannot get property, script language differs from engine property implementation");
			return nullptr;
		}

		std::shared_ptr<LuauObjectScript> script = std::static_pointer_cast<LuauObjectScript>(object->getScript());
		return script->get(name);
	}

	void LuauProperty::set(std::shared_ptr<Object> object, Variant value) const {
		if(isReadOnly()) return;

		if(object == nullptr) return;
		if(object->getScript() == nullptr) {
			std::println("[ERR] Cannot set property of script class if the object does not have a script");
			return;
		}

		if(object->getScript()->getScriptEngine() != LuauScriptEngine::getInstance()) {
			std::println("[ERR] Cannot set property, script language differs from engine property implementation");
			return;
		}

		std::shared_ptr<LuauObjectScript> script = std::static_pointer_cast<LuauObjectScript>(object->getScript());
		script->set(name, value);
	}

	bool LuauProperty::isReadOnly() const {
		return readonly;
	}
}
