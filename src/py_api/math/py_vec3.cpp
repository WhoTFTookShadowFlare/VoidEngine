#include "ve/py_api/math/py_vec3.hpp"
#include <cstddef>
#include <format>
#include <glm/ext/vector_float3.hpp>
#include <python3.13/Python.h>
#include <python3.13/structmember.h>
#include <python3.13/modsupport.h>
#include <python3.13/object.h>
#include <python3.13/pyerrors.h>
#include <python3.13/pyport.h>
#include <python3.13/pytypedefs.h>
#include <python3.13/tupleobject.h>
#include <python3.13/unicodeobject.h>

namespace VoidEngine::PyAPI::Math {
	static PyMethodDef vec3Methods[] = {

		{ nullptr, nullptr, 0, nullptr }
	};

	static PyMemberDef vec3Members[] = {
		{ "x", T_FLOAT, offsetof(PyVec3, value.x), 0, "The x component" },
		{ "y", T_FLOAT, offsetof(PyVec3, value.y), 0, "The x component" },
		{ "z", T_FLOAT, offsetof(PyVec3, value.z), 0, "The x component" },
		{ nullptr, 0, 0, 0, nullptr }
	};

	PyTypeObject Vec3TypeObject = {
		.ob_base = { _PyObject_EXTRA_INIT 1, (0) },
		.tp_name = "VoidEngine.Math.Vec3",
		.tp_basicsize = sizeof(PyVec3),
		.tp_itemsize = 0,
		.tp_str = PyVec3_repr,
		.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
		.tp_doc = "",
		.tp_methods = vec3Methods,
		.tp_members = vec3Members,
		.tp_init = PyVec3_init,
		.tp_new = PyVec3_new,
	};

	PyVec3* PyVec3_create(glm::vec3 value) {
		PyTypeObject* type = &Vec3TypeObject;
		PyVec3* instance = (PyVec3*) type->tp_alloc(type, 0);

		PyObject* args = PyTuple_New(0);
		type->tp_init((PyObject*) instance, args, nullptr);
		Py_DecRef(args);

		instance->value = value;
		return instance;
	}

	PyObject* PyVec3_new(PyTypeObject* subtype, PyObject* args, PyObject* kwds) {
		PyVec3* self = (PyVec3*) subtype->tp_alloc(subtype, 0);

		if(self != nullptr) [[unlikely]] {
			self->value = { 0, 0, 0 };
		}

		return (PyObject*) self;
	}

	int PyVec3_init(PyObject* self, PyObject* args, PyObject* kwds) {
		PyVec3* vec3 = (PyVec3*) self;
		
		Py_ssize_t argc = PyTuple_Size(args);
		if(argc == 3)
			PyArg_ParseTuple(args, "fff", &vec3->value.x, &vec3->value.y, &vec3->value.z);
		else if(argc == 0)
			vec3->value = { 0, 0, 0 };
		else [[unlikely]]
			PyErr_BadArgument();

		return 0;
	}

	PyObject* PyVec3_repr(PyObject* self) {
		PyVec3* vec3 = (PyVec3*) self;
		std::string str = std::format("{{ {}, {}, {} }}", vec3->value.x, vec3->value.y, vec3->value.z);
		return PyUnicode_FromString(str.c_str());
	}
}

