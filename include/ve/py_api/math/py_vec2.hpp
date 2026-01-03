#pragma once

#include <glm/ext/vector_float2.hpp>
#include <python3.13/Python.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI::Math {
	typedef struct {
		PyObject_HEAD;
		glm::vec2 value;
	} PyVec2;

	extern PyTypeObject Vec2TypeObject;

	[[nodiscard]] PyVec2* PyVec2_create(glm::vec2 value);

	PyObject* PyVec2_new(PyTypeObject *subtype, PyObject *args, PyObject *kwds);
	int PyVec2_init(PyObject *self, PyObject *args, PyObject *kwds); 

	PyObject* PyVec2_repr(PyObject* self);
}

