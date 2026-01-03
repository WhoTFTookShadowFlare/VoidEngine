#include "ve/py_api/math/py_vec4.hpp"
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
	static PyMethodDef vec4Methods[] = {

		{ nullptr, nullptr, 0, nullptr }
	};

	static PyMemberDef vec4Members[] = {
		{ "x", T_FLOAT, offsetof(PyVec4, value.x), 0, "The x component" },
		{ "y", T_FLOAT, offsetof(PyVec4, value.y), 0, "The x component" },
		{ "z", T_FLOAT, offsetof(PyVec4, value.z), 0, "The x component" },
		{ "w", T_FLOAT, offsetof(PyVec4, value.x), 0, "The x component" },
		{ nullptr, 0, 0, 0, nullptr }
	};

	PyTypeObject Vec4TypeObject = {
		.ob_base = { _PyObject_EXTRA_INIT 1, (0) },
		.tp_name = "VoidEngine.Math.Vec4",
		.tp_basicsize = sizeof(PyVec4),
		.tp_itemsize = 0,
		.tp_str = PyVec4_repr,
		.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
		.tp_doc = "",
		.tp_methods = vec4Methods,
		.tp_members = vec4Members,
		.tp_init = PyVec4_init,
		.tp_new = PyVec4_new,
	};

	PyVec4* PyVec4_create(glm::vec4 value) {
		PyTypeObject* type = &Vec4TypeObject;
		PyVec4* instance = (PyVec4*) type->tp_alloc(type, 0);

		PyObject* args = PyTuple_New(0);
		type->tp_init((PyObject*) instance, args, nullptr);
		Py_DecRef(args);

		instance->value = value;
		return instance;
	}

	PyObject* PyVec4_new(PyTypeObject* subtype, PyObject* args, PyObject* kwds) {
		PyVec4* self = (PyVec4*) subtype->tp_alloc(subtype, 0);

		if(self != nullptr) [[unlikely]] {
			self->value = { 0, 0, 0, 0 };
		}

		return (PyObject*) self;
	}

	int PyVec4_init(PyObject* self, PyObject* args, PyObject* kwds) {
		PyVec4* vec4 = (PyVec4*) self;
		
		Py_ssize_t argc = PyTuple_Size(args);
		if(argc == 4)
			PyArg_ParseTuple(args, "ffff", &vec4->value.x, &vec4->value.y, &vec4->value.z, &vec4->value.w);
		else if(argc == 0)
			vec4->value = { 0, 0, 0, 0 };
		else [[unlikely]]
			PyErr_BadArgument();

		return 0;
	}

	PyObject* PyVec4_repr(PyObject* self) {
		PyVec4* vec4 = (PyVec4*) self;
		std::string str = std::format("{{ {}, {}, {}, {} }}", vec4->value.x, vec4->value.y, vec4->value.z, vec4->value.w);
		return PyUnicode_FromString(str.c_str());
	}
}
