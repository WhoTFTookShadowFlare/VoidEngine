#include "ve/py_api/math/py_rect2.hpp"
#include "ve/math/rect2.hpp"
#include "ve/py_api/math/py_vec2.hpp"

#include <cstddef>
#include <cstdint>
#include <format>
#include <glm/ext/vector_float2.hpp>
#include <python3.13/Python.h>
#include <python3.13/abstract.h>
#include <python3.13/boolobject.h>
#include <python3.13/floatobject.h>
#include <python3.13/listobject.h>
#include <python3.13/methodobject.h>
#include <python3.13/modsupport.h>
#include <python3.13/object.h>
#include <python3.13/pyerrors.h>
#include <python3.13/pyport.h>
#include <python3.13/pytypedefs.h>
#include <python3.13/structmember.h>
#include <python3.13/tupleobject.h>
#include <python3.13/unicodeobject.h>

namespace VoidEngine::PyAPI::Math {
	static PyMethodDef rect2Methods[] = {
		{ "equals", PyRect2_equals, METH_VARARGS, "Checks equality" },
		{ "get_end_position", PyRect2_getEndPosition, METH_NOARGS, "returns the bottom right vertex position" },
		{ "collides_with", PyRect2_collidesWith, METH_VARARGS, "Checks if the provided rect is overlapping this" },
		{ "contains_point", PyRect2_containsPoint, METH_VARARGS, "Checks if the provided point is in the center" },
		{ "get_center", PyRect2_getCenter, METH_NOARGS, "Returns the center" },
		{ "get_vertical_center", PyRect2_getVerticalCenter, METH_NOARGS, "Returns the y position of the center" },
		{ "get_horizontal_center", PyRect2_getHorizontalCenter, METH_NOARGS, "Returns the x position of the center" },
		{ "get_rect_vertices", PyRect2_getRectVertices, METH_NOARGS, "Returns the 4 vertices of the rect" },
		{ "split_horizontally", PyRect2_splitHorizontally, METH_VARARGS, "Splits rect horizontally by point" },
		{ "split_vertically", PyRect2_splitVertically, METH_VARARGS, "Splits rect vertically by point" },
		{ "round", PyRect2_round, METH_NOARGS, "Rounds all values" },
		{ "floor", PyRect2_floor, METH_NOARGS, "Floors all values" },
		{ "ceil", PyRect2_ceil, METH_NOARGS, "Ceils all values" },
		{ nullptr, nullptr, 0, nullptr }
	};

	static PyMemberDef rect2Members[] = {
		{ "position", T_OBJECT, offsetof(PyRect2, position), 0, "The position" },
		{ "size", T_OBJECT, offsetof(PyRect2, size), 0, "The size" },
		{ nullptr, 0, 0, 0, nullptr }
	};

	PyTypeObject Rect2TypeObject = {
		.ob_base = { _PyObject_EXTRA_INIT 1, (0) },
		.tp_name = "VoidEngine.Math.Rect2",
		.tp_basicsize = sizeof(PyRect2),
		.tp_itemsize = 0,
		.tp_str = PyRect2_repr,
		.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
		.tp_doc = "An 2 dimensional axis-aligned rectangle",
		.tp_methods = rect2Methods,
		.tp_members = rect2Members,
		.tp_init = PyRect2_init,
		.tp_new = PyRect2_new,
	};

	PyRect2* PyRect2_create(VoidEngine::Math::Rect2f value) {
		PyTypeObject* type = &Rect2TypeObject;
		PyRect2* instance = (PyRect2*) type->tp_alloc(type, 0);

		PyObject* args = PyTuple_New(0);
		type->tp_init((PyObject*) instance, args, nullptr);
		Py_DecRef(args);

		instance->position->value = value.position;
		instance->size->value = value.size;

		return instance;
	}

	VoidEngine::Math::Rect2f PyRect2_toCXX(PyObject *self) {
		if(!PyObject_IsInstance(self, (PyObject*) &Rect2TypeObject)) [[unlikely]] {
			PyErr_BadArgument();
			return { { 0, 0 }, { 0, 0 } };
		}

		PyRect2* rect = (PyRect2*) self;
		return {
			rect->position->value,
			rect->size->value
		};
	}

	PyObject* PyRect2_new(PyTypeObject* subtype, PyObject* args, PyObject* kwds) {
		PyRect2* self = (PyRect2*) subtype->tp_alloc(subtype, 0);

		if(self != nullptr) [[unlikely]] {
			self->position = PyVec2_create({ 0, 0 });
			self->size = PyVec2_create({ 0, 0 });
		}

		return (PyObject*) self;
	}

	int PyRect2_init(PyObject *self, PyObject *args, PyObject *kwds) {
		PyRect2* rect2 = (PyRect2*) self;

		Py_ssize_t argc = PyTuple_Size(args);
		if(argc == 0) {
			rect2->position->value = { 0, 0 };
			rect2->size->value = { 0, 0 };
		}
		else if(argc == 4)
			PyArg_ParseTuple(args, "ffff", &rect2->position->value.x, &rect2->position->value.y, &rect2->size->value.x, &rect2->size->value.y);
		else if(argc == 2) {
			PyObject *arg1 = nullptr, *arg2 = nullptr;
			PyArg_ParseTuple(args, "OO", &arg1, &arg2);
			
			if(!(PyObject_IsInstance(arg1, (PyObject*) &Vec2TypeObject) &&
				PyObject_IsInstance(arg2, (PyObject*) &Vec2TypeObject))) {
				PyErr_BadArgument();
				return -1;
			}
			
			PyVec2 *vec1 = (PyVec2*) arg1, *vec2 = (PyVec2*) arg2;
			rect2->position = vec1;
			rect2->size = vec2;
		} else [[unlikely]]
			PyErr_BadArgument();
		
		return 0;
	}

	PyObject* PyRect2_repr(PyObject* self) {
		PyRect2* rect = (PyRect2*) self;
		std::string str = std::format("{{ position: {{ {}, {} }}, size: {{ {}, {} }} }}",
				rect->position->value.x,
				rect->position->value.y,
				rect->size->value.x,
				rect->size->value.y
				);
		return PyUnicode_FromString(str.c_str());
	}

	// Operators
	PyObject* PyRect2_equals(PyObject* self, PyObject* args) {
		if(!(PyTuple_Size(args) != 1)) [[unlikely]] {
			PyErr_BadArgument();
			return Py_False;
		}

		PyObject* RHS_unchecked = nullptr;
		PyArg_ParseTuple(args, "O", &RHS_unchecked);
		if(!PyObject_IsInstance(RHS_unchecked, (PyObject*) &Rect2TypeObject)) [[unlikely]] {
			PyErr_BadArgument();
			return Py_False;
		}

		PyRect2 *LHS = (PyRect2*) self, *RHS = (PyRect2*) RHS_unchecked;
		VoidEngine::Math::Rect2f
			LHSRect = PyRect2_toCXX((PyObject*) LHS),
			RHSRect = PyRect2_toCXX((PyObject*) RHS);

		return LHSRect == RHSRect ? Py_True : Py_False;
	}

	// Py -> C
	PyObject* PyRect2_getEndPosition(PyObject* self, PyObject* args) {
		return (PyObject*) PyVec2_create(PyRect2_toCXX(self).getEndPosition());
	}

	PyObject* PyRect2_collidesWith(PyObject* self, PyObject* args) {
		if(PyTuple_Size(args) != 1) [[unlikely]] {
			PyErr_BadInternalCall();
			return Py_False;
		}

		PyObject* arg = PyTuple_GetItem(args, 0);
		if(!PyObject_IsInstance(arg, (PyObject*) &Rect2TypeObject)) [[unlikely]] {
			PyErr_BadArgument();
			return Py_False;
		}

		VoidEngine::Math::Rect2f
			selfRect = PyRect2_toCXX(self),
			rect = PyRect2_toCXX(arg);

		return selfRect.collidesWith(rect) ? Py_True : Py_False;
	}

	PyObject* PyRect2_containsPoint(PyObject* self, PyObject* args) {
		if(PyTuple_Size(args) != 1) [[unlikely]] {
			PyErr_BadArgument();
			return Py_False;
		}

		PyObject* arg = PyTuple_GetItem(args, 0);
		if(!PyObject_IsInstance(arg, (PyObject*) &Vec2TypeObject)) [[unlikely]] {
			PyErr_BadArgument();
			return Py_False;
		}

		VoidEngine::Math::Rect2f selfRect = PyRect2_toCXX(self);
	
		return selfRect.containsPoint(((PyVec2*) arg)->value) ? Py_True : Py_False;
	}

	PyObject* PyRect2_getCenter(PyObject* self, PyObject* args) {
		return (PyObject*) PyVec2_create(PyRect2_toCXX(self).getCenter());
	}

	PyObject* PyRect2_getVerticalCenter(PyObject* self, PyObject* args) {
		return PyFloat_FromDouble(PyRect2_toCXX(self).getVerticalCenter());
	}

	PyObject* PyRect2_getHorizontalCenter(PyObject* self, PyObject* args) {
		return PyFloat_FromDouble(PyRect2_toCXX(self).getHorizontalCenter());
	}

	PyObject* PyRect2_getRectVertices(PyObject* self, PyObject* args) {
		PyObject* vertices = PyList_New(4);

		auto cVertices = PyRect2_toCXX(self).getRectVertices();

		for(uint8_t idx = 0; idx < 4; idx++) {
			PyList_SetItem(vertices, idx, (PyObject*) PyVec2_create(cVertices[idx]));
		}

		return vertices;
	}
	
	PyObject* PyRect2_splitHorizontally(PyObject* self, PyObject* args) {
		if(!(PyTuple_Size(args) != 1)) [[unlikely]] {
			PyErr_BadArgument();
			return Py_None;
		}

		PyObject* arg = PyTuple_GetItem(args, 0);
		if(!PyObject_IsInstance(arg, (PyObject*) &PyFloat_Type)) [[unlikely]] {
			PyErr_BadArgument();
			return Py_None;
		}

		PyObject* rects = PyTuple_New(2);

		PyFloatObject* point = (PyFloatObject*) arg;
		auto split = PyRect2_toCXX(self).splitHorizontally(point->ob_fval);

		for(uint8_t idx = 0; idx < 2; idx++) {
			PyTuple_SetItem(rects, idx, (PyObject*) PyRect2_create(split[idx]));
		}

		return rects;
	}

	PyObject* PyRect2_splitVertically(PyObject* self, PyObject* args) {
		if(PyTuple_Size(args) != 1) [[unlikely]] {
			PyErr_BadArgument();
			return Py_None;
		}

		PyObject* arg = PyTuple_GetItem(args, 0);
		if(!PyObject_IsInstance(arg, (PyObject*) &PyFloat_Type)) [[unlikely]] {
			PyErr_BadArgument();
			return Py_None;
		}

		PyFloatObject* point = (PyFloatObject*) arg;
		auto split = PyRect2_toCXX(self).splitVertically(point->ob_fval);

		PyObject* rects = PyTuple_New(2);
		for(uint8_t idx = 0; idx < 2; idx++) {
			PyTuple_SetItem(rects, idx, (PyObject*) PyRect2_create(split[idx]));
		}

		return rects;
	}

	PyObject* PyRect2_round(PyObject* self, PyObject* args) {
		return (PyObject*) PyRect2_create(PyRect2_toCXX(self).round<float>());
	}

	PyObject* PyRect2_floor(PyObject* self, PyObject* args) {
		return (PyObject*) PyRect2_create(PyRect2_toCXX(self).floor<float>());
	}

	PyObject* PyRect2_ceil(PyObject* self, PyObject* args) {
		return (PyObject*) PyRect2_create(PyRect2_toCXX(self).ceil<float>());
	}
}

