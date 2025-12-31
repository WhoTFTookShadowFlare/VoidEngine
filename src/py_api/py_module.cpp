#include "ve/py_api/py_module.hpp"
#include <glm/ext/vector_float2.hpp>
#include "ve/py_api/math/py_vec2.hpp"
#include <python3.13/Python.h>
#include <python3.13/structmember.h>
#include <python3.13/exports.h>
#include <python3.13/import.h>
#include <python3.13/methodobject.h>
#include <python3.13/modsupport.h>
#include <python3.13/moduleobject.h>
#include <python3.13/object.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI {
	namespace Math {
		static PyMethodDef Math_methods[] = {
			{ nullptr }
		};

		static struct PyModuleDef Math_module = {
			.m_base = PyModuleDef_HEAD_INIT,
			.m_name = "VoidEngine.Math",
			.m_doc = "Im sure you can figure this out",
			.m_size = 0,
			.m_methods = Math_methods
		};
		
		PyMODINIT_FUNC PyInit_VoidEngine_Math(void) {
			PyObject* module = PyModule_Create(&Math_module);

			if(PyType_Ready(&Vec2TypeObject) < 0)
				return nullptr;

			if(PyModule_AddType(module, &Vec2TypeObject) < 0) {
				Py_DECREF(&Vec2TypeObject);
				Py_DECREF(module);
				return nullptr;
			}

			return module;
		}
	}

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

		PyModule_AddObject(module, "Math", Math::PyInit_VoidEngine_Math());

		return module;
	}

	void initVoidEnginePyAPI(void) {
		PyImport_AppendInittab("VoidEngine", &VoidEngine::PyAPI::PyInit_VoidEngine);
	}
}
