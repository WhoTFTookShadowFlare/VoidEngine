#include "luau_property.hpp"
#include "luau_script_object.hpp"
#include "ve/class_db.hpp"
#include "ve/object.hpp"
#include <memory>

namespace VoidEngine::Scripts::Luau {
	LuauProperty::LuauProperty(std::string name, bool readonly) : PropertyBase(name), readonly(readonly) {}

	Variant LuauProperty::get(std::shared_ptr<Object> object) const {
		if(object == nullptr) return nullptr;
		if(!object->getClass()->instanceOf(&LuauScriptObject::ClassData)) return nullptr;

		std::shared_ptr<LuauScriptObject> script = std::static_pointer_cast<LuauScriptObject>(object);
		return script->get(name);
	}

	void LuauProperty::set(std::shared_ptr<Object> object, Variant value) const {
		if(isReadOnly()) return;

		if(object == nullptr) return;
		if(!object->getClass()->instanceOf(&LuauScriptObject::ClassData)) return;

		std::shared_ptr<LuauScriptObject> script = std::static_pointer_cast<LuauScriptObject>(object);
		script->set(name, value);
	}

	bool LuauProperty::isReadOnly() const {
		return readonly;
	}
}
