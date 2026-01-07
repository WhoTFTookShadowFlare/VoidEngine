#include "ve/py_api/math/py_rect2.hpp"
#include "pocketpy.h"
#include "ve/math/rect2.hpp"
#include "ve/py_api/math/py_vec2.hpp"

#include <format>
#include <string>

#include <glm/ext/vector_float2.hpp>

namespace VoidEngine::PyAPI::Math {
	using namespace VoidEngine::Math;

	bool PyRect2__new__(int argc, py_Ref argv);
	bool PyRect2__init__(int argc, py_Ref argv);
	bool PyRect2__repr__(int argc, py_Ref argv);

	bool PyRect2_get_position(int argc, py_Ref argv);
	bool PyRect2_get_size(int argc, py_Ref argv);

	bool PyRect2_set_position(int argc, py_Ref argv);
	bool PyRect2_set_size(int argc, py_Ref argv);

	py_Type rect2Type = 0;
	void initRect2PyType(py_GlobalRef module) {
		rect2Type = py_newtype("Rect2", tp_object, module, nullptr);
		py_bindmethod(rect2Type, "__new__", PyRect2__new__);
		py_bindmethod(rect2Type, "__init__", PyRect2__init__);
		py_bindmethod(rect2Type, "__repr__", PyRect2__repr__);

		py_bindproperty(rect2Type, "position", PyRect2_get_position, PyRect2_set_position);
		py_bindproperty(rect2Type, "size", PyRect2_get_size, PyRect2_set_size);
	}

	bool PyRect2__new__(int argc, py_Ref argv) {
		py_Type cls = py_totype(argv);
		py_newobject(py_retval(), cls, 0, sizeof(Rect2f));
		return true;
	}

	bool PyRect2__init__(int argc, py_Ref argv) {
		if(argc == 3) {
			Rect2f *self = (Rect2f*) py_touserdata(py_arg(0));
			if(!(py_isinstance(py_arg(1), vec2Type) && py_isinstance(py_arg(2), vec2Type))) {
				return TypeError("creating a Rect2 with 2 args requires them to both be of type Vec2");
			}
			self->position = *(glm::vec2*) py_touserdata(py_arg(1));
			self->size = *(glm::vec2*) py_touserdata(py_arg(2));
			return true;
		}
		if(argc != 5) {
			return false;
		}

		Rect2f *self = (Rect2f*) py_touserdata(py_arg(0));

		if(py_castfloat32(py_arg(1), &self->position.x) || py_castfloat32(py_arg(2), &self->position.y) || py_castfloat32(py_arg(3), &self->size.x) || py_castfloat32(py_arg(4), &self->size.y)) {
			return TypeError("Creating a Rect2 with 4 args requires thema ll to be of type float");
		}

		py_newnone(py_retval());
		return true;
	}

	bool PyRect2__repr__(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		Rect2f *self = (Rect2f*) py_touserdata(py_arg(0));
		std::string str = std::format("{{ position: {{ {}, {} }}, size: {{ {}, {} }} }}", self->position.x, self->position.y, self->size.x, self->size.y);
		py_newstr(py_retval(), str.c_str());
		return true;

	}

	bool PyRect2_get_position(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		Rect2f *self = (Rect2f*) py_touserdata(py_arg(0));
		glm::vec2 *position = (glm::vec2*) py_newobject(py_retval(), vec2Type, 0, sizeof(glm::vec2));
		*position = self->position;
		return true;
	}

	bool PyRect2_get_size(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		Rect2f *self = (Rect2f*) py_touserdata(py_arg(0));
		glm::vec2 *size = (glm::vec2*) py_newobject(py_retval(), vec2Type, 0, sizeof(glm::vec2));
		*size = self->size;
		return true;
	}

	bool PyRect2_set_position(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		Rect2f *self = (Rect2f*) py_touserdata(py_arg(0));
		
		if(!py_isinstance(py_arg(1), vec2Type)) {
			return TypeError("Rect2.position must be of type Vec2");
		}

		glm::vec2 *position = (glm::vec2*) py_touserdata(py_arg(1));
		self->position = *position;

		py_newnone(py_retval());
		return true;
	}

	bool PyRect2_set_size(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		Rect2f *self = (Rect2f*) py_touserdata(py_arg(0));
		
		if(!py_isinstance(py_arg(1), vec2Type)) {
			return TypeError("Rect2.size must be of type Vec2");
		}

		glm::vec2 *size = (glm::vec2*) py_touserdata(py_arg(1));
		self->size = *size;

		py_newnone(py_retval());
		return true;
	}
}

