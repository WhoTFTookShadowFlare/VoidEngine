#pragma once

#include "pocketpy.h"

namespace VoidEngine::PyAPI::Math {
	extern py_Type rect2Type;
	void initRect2PyType(py_GlobalRef module);
	
	// Operators
	// PyObject* PyRect2_equals(PyObject* self, PyObject* args);

	// Py -> C
	// PyObject* PyRect2_getEndPosition(PyObject* self, PyObject* args);
	// PyObject* PyRect2_collidesWith(PyObject* self, PyObject* args);
	// PyObject* PyRect2_containsPoint(PyObject* self, PyObject* args);
	// PyObject* PyRect2_getCenter(PyObject* self, PyObject* args);
	// PyObject* PyRect2_getVerticalCenter(PyObject* self, PyObject* args);
	// PyObject* PyRect2_getHorizontalCenter(PyObject* self, PyObject* args);
	// PyObject* PyRect2_getRectVertices(PyObject* self, PyObject* args);
	// PyObject* PyRect2_splitHorizontally(PyObject* self, PyObject* args);
	// PyObject* PyRect2_splitVertically(PyObject* self, PyObject* args);
	// PyObject* PyRect2_round(PyObject* self, PyObject* args);
	// PyObject* PyRect2_floor(PyObject* self, PyObject* args);
	// PyObject* PyRect2_ceil(PyObject* self, PyObject* args);
}

