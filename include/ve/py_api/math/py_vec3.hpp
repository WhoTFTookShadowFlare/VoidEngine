#pragma once

#include <glm/ext/vector_float3.hpp>
#include <python3.13/Python.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI::Math {
	typedef struct {
		PyObject_HEAD;
		glm::vec3 value;
	} PyVec3;

	extern PyTypeObject Vec3TypeObject;

	[[nodiscard]] PyVec3* PyVec3_create(glm::vec3 value);

	PyObject* PyVec3_new(PyTypeObject *subtype, PyObject *args, PyObject *kwds);
	int PyVec3_init(PyObject *self, PyObject *args, PyObject *kwds); 

	PyObject* PyVec3_repr(PyObject* self);
}

