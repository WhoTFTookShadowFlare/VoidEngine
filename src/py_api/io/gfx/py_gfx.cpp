#include "ve/py_api/io/gfx/py_gfx.hpp"

#include "ve/py_api/io/gfx/py_vertex.hpp"

#include <python3.13/exports.h>
#include <python3.13/modsupport.h>
#include <python3.13/moduleobject.h>
#include <python3.13/object.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI::IO::GFX {
	static PyMethodDef GFX_methods[] = {
		{ nullptr, nullptr, 0, nullptr }
	};

	static struct PyModuleDef GFX_module = {
		.m_base = PyModuleDef_HEAD_INIT,
		.m_name = "VoidEngine.IO.GFX",
		.m_doc = "All the things related to graphics",
		.m_size = 0,
		.m_methods = GFX_methods
	};

	PyMODINIT_FUNC PyInit_VoidEngine_IO_GFX(void) {
		PyTypeObject* modTypes[] = {
			&VertexTypeObject
		};

		for(PyTypeObject* type : modTypes) {
			if(PyType_Ready(type) < 0) [[unlikely]] {
				for(PyTypeObject* toDec : modTypes) {
					Py_DecRef((PyObject*) toDec);
				}
				return nullptr;
			}
		}

		PyObject* module = PyModule_Create(&GFX_module);

		for(PyTypeObject* type : modTypes) {
			if(PyModule_AddType(module, type) < 0) [[unlikely]] {
				for(PyTypeObject* toDec : modTypes) {
					Py_DecRef((PyObject*) toDec);
				}
				Py_DecRef(module);
			}
		}

		return module;
	}
}

