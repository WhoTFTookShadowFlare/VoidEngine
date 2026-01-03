#pragma once

#include <glm/ext/vector_float4.hpp>
#include <python3.13/Python.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI::Math {
	typedef struct {
		PyObject_HEAD;
		glm::vec4 value;
	} PyVec4;

	extern PyTypeObject Vec4TypeObject;

	[[nodiscard]] PyVec4* PyVec4_create(glm::vec4 value);

	PyObject* PyVec4_new(PyTypeObject *subtype, PyObject *args, PyObject *kwds);
	int PyVec4_init(PyObject *self, PyObject *args, PyObject *kwds); 

	PyObject* PyVec4_repr(PyObject* self);
}

