#include "ve/py_api/math/py_vec4.hpp"
#include "pocketpy.h"
#include <glm/ext/vector_float4.hpp>
#include <string>
#include <format>
#include <glm/ext/vector_float3.hpp>

namespace VoidEngine::PyAPI::Math {
	bool PyVec4__new__(int argc, py_Ref argv);
	bool PyVec4__init__(int argc, py_Ref argv);
	bool PyVec4__repr__(int argc, py_Ref argv);

	bool PyVec4_get_x(int argc, py_Ref argv);
	bool PyVec4_get_y(int argc, py_Ref argv);
	bool PyVec4_get_z(int argc, py_Ref argv);
	bool PyVec4_get_w(int argc, py_Ref argv);

	bool PyVec4_set_x(int argc, py_Ref argv);
	bool PyVec4_set_y(int argc, py_Ref argv);
	bool PyVec4_set_z(int argc, py_Ref argv);
	bool PyVec4_set_w(int argc, py_Ref argv);

	py_Type vec4Type = 0;
	void initVec4PyType(py_GlobalRef module) {
		vec4Type = py_newtype("Vec4", tp_object, module, nullptr);
		py_bindmethod(vec4Type, "__new__", PyVec4__new__);
		py_bindmethod(vec4Type, "__init__", PyVec4__init__);
		py_bindmethod(vec4Type, "__repr__", PyVec4__repr__);

		py_bindproperty(vec4Type, "x", PyVec4_get_x, PyVec4_set_x);
		py_bindproperty(vec4Type, "y", PyVec4_get_y, PyVec4_set_y);
		py_bindproperty(vec4Type, "z", PyVec4_get_z, PyVec4_set_z);
		py_bindproperty(vec4Type, "w", PyVec4_get_w, PyVec4_set_w);
	}

	bool PyVec4__new__(int argc, py_Ref argv) {
		py_Type cls = py_totype(argv);
		py_newobject(py_retval(), cls, 0, sizeof(glm::vec4));
		return true;
	}

	bool PyVec4__init__(int argc, py_Ref argv) {
		if(argc == 1) {
			glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
			self->x = 0.0;
			self->y = 0.0;
			return true;
		}
		if(argc != 5) {
			return false;
		}

		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));

		if(py_castfloat32(py_arg(1), &self->x) || py_castfloat32(py_arg(2), &self->y) || py_castfloat32(py_arg(3), &self->z) || py_castfloat32(py_arg(4), &self->w)) {
			return TypeError("A value passed to a Vec4 was not a float");
		}

		py_newnone(py_retval());
		return true;
	}

	bool PyVec4__repr__(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
		std::string str = std::format("{{ {}, {}, {}, {} }}", self->x, self->y, self->z, self->w);
		py_newstr(py_retval(), str.c_str());
		return true;

	}

	bool PyVec4_get_x(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
		py_newfloat(py_retval(), self->x);
		return true;
	}

	bool PyVec4_get_y(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
		py_newfloat(py_retval(), self->y);
		return true;
	}

	bool PyVec4_get_z(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
		py_newfloat(py_retval(), self->z);
		return true;
	}

	bool PyVec4_get_w(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
		py_newfloat(py_retval(), self->w);
		return true;
	}

	bool PyVec4_set_x(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
		if(!py_castfloat32(py_arg(1), &self->x)) {
			return TypeError(std::format("Expected float, got {}", py_tpname(py_typeof(py_arg(1)))).c_str());
		}
		py_newnone(py_retval());
		return true;
	}

	bool PyVec4_set_y(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
		if(!py_castfloat32(py_arg(1), &self->y)) {
			return TypeError(std::format("Expected float, got {}", py_tpname(py_typeof(py_arg(1)))).c_str());
		}
		py_newnone(py_retval());
		return true;
	}

	bool PyVec4_set_z(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
		if(!py_castfloat32(py_arg(1), &self->z)) {
			return TypeError(std::format("Expected float, got {}", py_tpname(py_typeof(py_arg(1)))).c_str());
		}
		py_newnone(py_retval());
		return true;
	}

	bool PyVec4_set_w(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		glm::vec4 *self = (glm::vec4*) py_touserdata(py_arg(0));
		if(!py_castfloat32(py_arg(1), &self->w)) {
			return TypeError(std::format("Expected float, got {}", py_tpname(py_typeof(py_arg(1)))).c_str());
		}
		py_newnone(py_retval());
		return true;
	}
}
