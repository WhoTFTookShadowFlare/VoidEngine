#include "ve/py_api/math/py_vec3.hpp"

#include <format>
#include <string>
#include "pocketpy.h"
#include <glm/ext/vector_float3.hpp>

namespace VoidEngine::PyAPI::Math {
	bool PyVec3__new__(int argc, py_Ref argv);
	bool PyVec3__init__(int argc, py_Ref argv);
	bool PyVec3__repr__(int argc, py_Ref argv);

	bool PyVec3_get_x(int argc, py_Ref argv);
	bool PyVec3_get_y(int argc, py_Ref argv);
	bool PyVec3_get_z(int argc, py_Ref argv);

	bool PyVec3_set_x(int argc, py_Ref argv);
	bool PyVec3_set_y(int argc, py_Ref argv);
	bool PyVec3_set_z(int argc, py_Ref argv);

	py_Type vec3Type = 0;
	void initVec3PyType(py_GlobalRef module) {
		vec3Type = py_newtype("Vec3", tp_object, module, nullptr);
		py_bindmethod(vec3Type, "__new__", PyVec3__new__);
		py_bindmethod(vec3Type, "__init__", PyVec3__init__);
		py_bindmethod(vec3Type, "__repr__", PyVec3__repr__);

		py_bindproperty(vec3Type, "x", PyVec3_get_x, PyVec3_set_x);
		py_bindproperty(vec3Type, "y", PyVec3_get_y, PyVec3_set_y);
		py_bindproperty(vec3Type, "z", PyVec3_get_z, PyVec3_set_z);
	}
	
	bool PyVec3__new__(int argc, py_Ref argv) {
		py_Type cls = py_totype(argv);
		py_newobject(py_retval(), cls, 0, sizeof(glm::vec3));
		return true;
	}

	bool PyVec3__init__(int argc, py_Ref argv) {
		if(argc == 1) {
			glm::vec3 *self = (glm::vec3*) py_touserdata(py_arg(0));
			self->x = 0.0;
			self->y = 0.0;
			self->z = 0.0;
			return true;
		}
		if(argc != 4) {
			return false;
		}

		glm::vec3 *self = (glm::vec3*) py_touserdata(py_arg(0));

		if(py_castfloat32(py_arg(1), &self->x) || py_castfloat32(py_arg(2), &self->y) || py_castfloat32(py_arg(3), &self->z)) {
			return TypeError("A value passed to a Vec3 was not a float");
		}

		py_newnone(py_retval());
		return true;
	}

	bool PyVec3__repr__(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec3 *self = (glm::vec3*) py_touserdata(py_arg(0));
		std::string str = std::format("{{ {}, {}, {} }}", self->x, self->y, self->z);
		py_newstr(py_retval(), str.c_str());
		return true;
	}

	bool PyVec3_get_x(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec3 *self = (glm::vec3*) py_touserdata(py_arg(0));
		py_newfloat(py_retval(), self->x);
		return true;
	}

	bool PyVec3_get_y(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec3 *self = (glm::vec3*) py_touserdata(py_arg(0));
		py_newfloat(py_retval(), self->y);
		return true;
	}

	bool PyVec3_get_z(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		glm::vec3 *self = (glm::vec3*) py_touserdata(py_arg(0));
		py_newfloat(py_retval(), self->z);
		return true;
	}

	bool PyVec3_set_x(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		glm::vec3 *self = (glm::vec3*) py_touserdata(py_arg(0));
		if(!py_castfloat32(py_arg(1), &self->x)) {
			return TypeError(std::format("Expected float, got {}", py_tpname(py_typeof(py_arg(1)))).c_str());
		}
		py_newnone(py_retval());
		return true;
	}

	bool PyVec3_set_y(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		glm::vec3 *self = (glm::vec3*) py_touserdata(py_arg(0));
		if(!py_castfloat32(py_arg(1), &self->y)) {
			return TypeError(std::format("Expected float, got {}", py_tpname(py_typeof(py_arg(1)))).c_str());
		}
		py_newnone(py_retval());
		return true;
	}

	bool PyVec3_set_z(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		glm::vec3 *self = (glm::vec3*) py_touserdata(py_arg(0));
		if(!py_castfloat32(py_arg(1), &self->z)) {
			return TypeError(std::format("Expected float, got {}", py_tpname(py_typeof(py_arg(1)))).c_str());
		}
		py_newnone(py_retval());
		return true;
	}
}

