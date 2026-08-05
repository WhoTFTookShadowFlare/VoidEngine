#include "ve/script/a_script_object.hpp"
#include "ve/object.hpp"

namespace VoidEngine::Scripts {
	const Class AScriptObject::ClassData = {
		.name = "AScriptObject",
		.super = &Object::ClassData
	};
}
