#include "ve/py_api/io/gfx/py_vertex.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/py_api/math/py_vec3.hpp"
#include "ve/py_api/math/py_vec4.hpp"
#include <cstddef>
#include <python3.13/object.h>
#include <python3.13/pytypedefs.h>
#include <python3.13/structmember.h>

namespace VoidEngine::PyAPI::IO::GFX {
	static PyMethodDef vertexMethods[] = {
		{ nullptr, nullptr, 0, nullptr }
	};

	static PyMemberDef vertexMembers[] = {
		{ "position", T_OBJECT, offsetof(PyVertex, position), 0, "The vertex position" },
		{ "color", T_OBJECT, offsetof(PyVertex, color), 0, "The vertex color" },
		{ nullptr, 0, 0, 0, nullptr }
	};

	PyTypeObject VertexTypeObject = {
		.ob_base = { _PyObject_EXTRA_INIT 1, (0) },
		.tp_name = "VoidEngine.IO.GFX.Vertex",
		.tp_basicsize = sizeof(PyVertex),
		.tp_itemsize = 0,
		// .tp_str = PyVertex_repr,
		.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
		.tp_doc = "A vertex for a Mesh",
		.tp_methods = vertexMethods,
		.tp_members = vertexMembers,
		.tp_init = PyVertex_init,
		.tp_new = PyVertex_new,
	};

	PyVertex* PyVertex_create(VoidEngine::IO::GFX::Vertex value) {
		PyTypeObject* type = &VertexTypeObject;
		PyVertex* instance = (PyVertex*) type->tp_alloc(type, 0);

		PyObject* args = PyTuple_New(0);
		type->tp_init((PyObject*) instance, args, nullptr);
		Py_DecRef(args);

		instance->position->value = value.position;
		instance->color->value = value.color;

		return instance;
	}
	
	VoidEngine::IO::GFX::Vertex PyVertex_toCXX(PyObject* self) {
		PyVertex* vertex = (PyVertex*) self;
		return {
			vertex->position->value,
			vertex->color->value
		};
	}

	PyObject* PyVertex_new(PyTypeObject* subtype, PyObject* args, PyObject* kwds) {
		PyVertex* self = (PyVertex*) subtype->tp_alloc(subtype, 0);

		if(self != nullptr) [[unlikely]] {
			self->position = Math::PyVec3_create({ 0, 0, 0 });
			self->color = Math::PyVec4_create({ 0, 0, 0, 1 });
		}

		return (PyObject*) self;
	}

	int PyVertex_init(PyObject* self, PyObject* args, PyObject* kwds) {
		PyVertex* vtx = (PyVertex*) self;

		vtx->position = Math::PyVec3_create({ 0, 0, 0 });
		vtx->color = Math::PyVec4_create({ 0, 0, 0, 1 });

		return 0;
	}
}

