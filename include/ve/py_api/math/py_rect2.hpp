#pragma once

#include "ve/math/rect2.hpp"
#include "ve/py_api/math/py_vec2.hpp"

#include <python3.13/Python.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI::Math {
	typedef struct {
		PyObject_HEAD;
		PyVec2 *position, *size;
	} PyRect2;

	extern PyTypeObject Rect2TypeObject;

	[[nodiscard]] PyRect2* PyRect2_create(VoidEngine::Math::Rect2f value);
	[[nodiscard]] VoidEngine::Math::Rect2f PyRect2_toCXX(PyObject* self);

	PyObject* PyRect2_new(PyTypeObject* subtype, PyObject* args, PyObject* kwds);
	int PyRect2_init(PyObject *self, PyObject *args, PyObject *kwds);

	PyObject* PyRect2_repr(PyObject* self);

	// Operators
	PyObject* PyRect2_equals(PyObject* self, PyObject* args);

	// Py -> C
	PyObject* PyRect2_getEndPosition(PyObject* self, PyObject* args);
	PyObject* PyRect2_collidesWith(PyObject* self, PyObject* args);
	PyObject* PyRect2_containsPoint(PyObject* self, PyObject* args);
	PyObject* PyRect2_getCenter(PyObject* self, PyObject* args);
	PyObject* PyRect2_getVerticalCenter(PyObject* self, PyObject* args);
	PyObject* PyRect2_getHorizontalCenter(PyObject* self, PyObject* args);
	PyObject* PyRect2_getRectVertices(PyObject* self, PyObject* args);
	PyObject* PyRect2_splitHorizontally(PyObject* self, PyObject* args);
	PyObject* PyRect2_splitVertically(PyObject* self, PyObject* args);
	PyObject* PyRect2_round(PyObject* self, PyObject* args);
	PyObject* PyRect2_floor(PyObject* self, PyObject* args);
	PyObject* PyRect2_ceil(PyObject* self, PyObject* args);
}

