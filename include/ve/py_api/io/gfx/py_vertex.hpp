#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/py_api/math/py_vec3.hpp"
#include "ve/py_api/math/py_vec4.hpp"
#include <python3.13/Python.h>

namespace VoidEngine::PyAPI::IO::GFX {
	typedef struct {
		PyObject_HEAD;
		Math::PyVec3* position;
		Math::PyVec4* color;
	} PyVertex;

	extern PyTypeObject VertexTypeObject;

	[[nodiscard]] PyVertex* PyRect2_create(VoidEngine::IO::GFX::Vertex value);
	[[nodiscard]] VoidEngine::IO::GFX::Vertex PyVertex_toCXX(PyObject* self);

	PyObject* PyVertex_new(PyTypeObject *subtype, PyObject *args, PyObject *kwds);
	int PyVertex_init(PyObject *self, PyObject *args, PyObject *kwds); 

	// PyObject* PyVertex_repr(PyObject* self);
}
