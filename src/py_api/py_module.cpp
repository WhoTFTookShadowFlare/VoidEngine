#include "ve/py_api/py_module.hpp"
#include <glm/ext/vector_float2.hpp>
#include "ve/py_api/io/py_io.hpp"
#include "ve/py_api/math/py_math.hpp"
#include "ve/py_api/py_engine.hpp"
#include <python3.13/Python.h>
#include <python3.13/dictobject.h>
#include <python3.13/listobject.h>
#include <python3.13/structmember.h>
#include <python3.13/exports.h>
#include <python3.13/import.h>
#include <python3.13/methodobject.h>
#include <python3.13/modsupport.h>
#include <python3.13/moduleobject.h>
#include <python3.13/object.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI {
	static PyMethodDef VoidEngine_methods[] = {
		{ nullptr }
	};
	
	static struct PyModuleDef VoidEngine_module {
		.m_base = PyModuleDef_HEAD_INIT,
		.m_name = "VoidEngine",
		.m_doc = "The Python API for VoidEngine and projects using it",
		.m_size = 0,
		.m_methods = VoidEngine_methods,
	};

	PyMODINIT_FUNC PyInit_VoidEngine(void) {
		PyObject* module = PyModule_Create(&VoidEngine_module);
		PyModule_AddObjectRef(module, "__path__", PyList_New(0));
		PyModule_AddStringConstant(module, "__package__", "VoidEngine");

		// TODO: Move this into a dedicated function
		PyObject* engine_module = PyInit_VoidEngine_Engine();
		PyModule_Add(module, "Engine", engine_module);
		PyDict_SetItemString(PyImport_GetModuleDict(), "VoidEngine.Engine", engine_module);
		
		PyObject* math_module = Math::PyInit_VoidEngine_Math();
		PyModule_Add(module, "Math", math_module);
		PyDict_SetItemString(PyImport_GetModuleDict(), "VoidEngine.Math", math_module);

		PyObject* io_module = IO::PyInit_VoidEngine_IO();
		PyModule_Add(module, "IO", io_module);
		PyDict_SetItemString(PyImport_GetModuleDict(), "VoidEngine.IO", io_module);

		return module;
	}

	void initVoidEnginePyAPI(void) {
		PyImport_AppendInittab("VoidEngine", &VoidEngine::PyAPI::PyInit_VoidEngine);
	}
}

