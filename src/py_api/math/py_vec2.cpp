#include "ve/py_api/math/py_vec2.hpp"
#include "pocketpy.h"
#include <format>
#include <glm/ext/vector_float2.hpp>
#include <string>

namespace VoidEngine::PyAPI::Math {
	bool PyVec2__new__(int argc, py_Ref argv);
	bool PyVec2__init__(int argc, py_Ref argv);
	bool PyVec2__repr__(int argc, py_Ref argv);

	bool PyVec2_get_x(int argc, py_Ref argv);
	bool PyVec2_get_y(int argc, py_Ref argv);

	bool PyVec2_set_x(int argc, py_Ref argv);
	bool PyVec2_set_y(int argc, py_Ref argv);

	py_Type vec2Type = 0;
	void initVec2PyType(py_GlobalRef module) {
		vec2Type = py_newtype("Vec2", tp_object, module, nullptr);
		py_bindmethod(vec2Type, "__new__", PyVec2__new__);
		py_bindmethod(vec2Type, "__init__", PyVec2__init__);
		py_bindmethod(vec2Type, "__repr__", PyVec2__repr__);

		py_bindproperty(vec2Type, "x", PyVec2_get_x, PyVec2_set_x);
		py_bindproperty(vec2Type, "y", PyVec2_get_y, PyVec2_set_y);
	}
	
	bool PyVec2__new__(int argc, py_Ref argv) {
		py_Type cls = py_totype(argv);
		py_newobject(py_retval(), cls, 0, sizeof(glm::vec2));
		return true;
	}

	bool PyVec2__init__(int argc, py_Ref argv) {
		if(argc == 1) {
			glm::vec2 *self = (glm::vec2*) py_touserdata(py_arg(0));
			self->x = 0.0;
			self->y = 0.0;
			return true;
		}
		if(argc != 3) {
			return false;
		}

		glm::vec2 *self = (glm::vec2*) py_touserdata(py_arg(0));

		if(!(py_castfloat32(py_arg(1), &self->x) || py_castfloat32(py_arg(2), &self->y))) {
			return TypeError("A value passed to a Vec2 was not a float");
		}

		py_newnone(py_retval());
		return true;
	}

	bool PyVec2__repr__(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec2 *self = (glm::vec2*) py_touserdata(py_arg(0));
		std::string str = std::format("{{ {}, {} }}", self->x, self->y);
		py_newstr(py_retval(), str.c_str());
		return true;
	}

	bool PyVec2_get_x(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec2 *self = (glm::vec2*) py_touserdata(py_arg(0));
		py_newfloat(py_retval(), self->x);
		return true;
	}

	bool PyVec2_get_y(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec2 *self = (glm::vec2*) py_touserdata(py_arg(0));
		py_newfloat(py_retval(), self->y);
		return true;
	}

	bool PyVec2_set_x(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		glm::vec2 *self = (glm::vec2*) py_touserdata(py_arg(0));
		if(!py_castfloat32(py_arg(1), &self->x)) {
			return TypeError(std::format("Expected float, got {}", py_tpname(py_typeof(py_arg(1)))).c_str());
		}
		py_newnone(py_retval());
		return true;
	}

	bool PyVec2_set_y(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		glm::vec2 *self = (glm::vec2*) py_touserdata(py_arg(0));
		if(!py_castfloat32(py_arg(1), &self->y)) {
			return TypeError(std::format("Expected float, got {}", py_tpname(py_typeof(py_arg(1)))).c_str());
		}
		py_newnone(py_retval());
		return true;
	}
}

