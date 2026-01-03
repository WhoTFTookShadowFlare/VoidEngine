#include "ve/py_api/py_engine.hpp"
#include <python3.13/modsupport.h>
#include <python3.13/moduleobject.h>
#include <python3.13/object.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI {
	static PyMethodDef Engine_methods[] = {
		{ nullptr }
	};

	static struct PyModuleDef Engine_module = {
		.m_base = PyModuleDef_HEAD_INIT,
		.m_name = "VoidEngine.Engine",
		.m_doc = "Core engine functions",
		.m_size = 0,
		.m_methods = Engine_methods,
	};

	PyMODINIT_FUNC PyInit_VoidEngine_Engine(void) {
		PyObject* module = PyModule_Create(&Engine_module);
		PyModule_AddStringConstant(module, "__package__", "VoidEngine");

		return module;
	}
}

