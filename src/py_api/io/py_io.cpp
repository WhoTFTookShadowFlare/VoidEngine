#include "ve/py_api/io/py_io.hpp"
#include "ve/py_api/io/gfx/py_gfx.hpp"

#include <python3.13/exports.h>
#include <python3.13/modsupport.h>
#include <python3.13/moduleobject.h>
#include <python3.13/object.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI::IO {
	static PyMethodDef IO_methods[] = {
		{ nullptr, nullptr, 0, nullptr }
	};

	static struct PyModuleDef IO_module = {
		.m_base = PyModuleDef_HEAD_INIT,
		.m_name = "VoidEngine.IO",
		.m_doc = "",
		.m_size = 0,
		.m_methods = IO_methods
	};

	PyMODINIT_FUNC PyInit_VoidEngine_IO(void) {
		PyTypeObject* modTypes[] = {

		};

		for(PyTypeObject* type : modTypes) {
			if(PyType_Ready(type) < 0) [[unlikely]] {
				for(PyTypeObject* toDec : modTypes) {
					Py_DecRef((PyObject*) toDec);
				}
				return nullptr;
			}
		}

		PyObject* module = PyModule_Create(&IO_module);
		PyModule_AddStringConstant(module, "__package__", "VoidEngine");

		for(PyTypeObject* type : modTypes) {
			if(PyModule_AddType(module, type) < 0) [[unlikely]] {
				for(PyTypeObject* toDec : modTypes) {
					Py_DecRef((PyObject*) toDec);
				}
				Py_DecRef(module);
				return nullptr;
			}
		}

		PyObject* gfx_module = GFX::PyInit_VoidEngine_IO_GFX();
		PyModule_Add(module, "GFX", gfx_module);
		PyDict_SetItemString(PyImport_GetModuleDict(), "VoidEngine.IO", gfx_module);

		return module;
	}
}

