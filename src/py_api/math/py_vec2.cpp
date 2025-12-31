#include "ve/py_api/math/py_vec2.hpp"
#include <glm/ext/vector_float2.hpp>
#include <python3.13/Python.h>
#include <python3.13/structmember.h>
#include <python3.13/floatobject.h>
#include <python3.13/modsupport.h>
#include <python3.13/object.h>
#include <python3.13/pyerrors.h>
#include <python3.13/pyport.h>
#include <python3.13/pytypedefs.h>
#include <python3.13/tupleobject.h>

namespace VoidEngine::PyAPI::Math {
	static PyMethodDef vec2Methods[] = {
		{ nullptr, nullptr, 0, nullptr }
	};

	static PyMemberDef vec2Members[] = {
		{ "x", T_FLOAT, offsetof(PyVec2, value.x), 0, "The x component" },
		{ "y", T_FLOAT, offsetof(PyVec2, value.y), 0, "The y component" },
		{ nullptr }
	};

	PyTypeObject Vec2TypeObject = {
		.ob_base = { _PyObject_EXTRA_INIT 1, (0) },
		.tp_name = "VoidEngine.Math.Vec2",
		.tp_basicsize = sizeof(PyVec2),
		.tp_itemsize = 0,
		.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
		.tp_doc = "A 2 dimensional vector",
		.tp_methods = vec2Methods,
		.tp_members = vec2Members,
		.tp_init = PyVec2_init,
		.tp_new = PyVec2_new,
	};
	
	PyVec2* PyVec2_create(glm::vec2 value) {
		PyTypeObject* type = &Vec2TypeObject;
		PyVec2* instance = (PyVec2*) type->tp_alloc(type, 0);
		
		PyObject* args = PyTuple_New(0);
		type->tp_init((PyObject*) instance, args, nullptr);
		Py_DecRef(args);

		instance->value = value;

		return instance;
	}

	PyObject* PyVec2_new(PyTypeObject *subtype, PyObject *args, PyObject *kwds) {
		PyVec2* self = (PyVec2*) subtype->tp_alloc(subtype, 0);

		if(self != nullptr) {
			self->value = { 0, 0 };
		}

		return (PyObject*) self;
	}

	int PyVec2_init(PyObject *self, PyObject *args, PyObject *kwds) {
		PyVec2* vec2 = (PyVec2*) self;
		
		Py_ssize_t argc = PyTuple_Size(args);
		if(argc == 2)
			PyArg_ParseTuple(args, "ff", &vec2->value.x, &vec2->value.y);
		else if(argc == 0)
			vec2->value = { 0, 0 };
		else
			PyErr_BadArgument();

		return 0;
	}
}

