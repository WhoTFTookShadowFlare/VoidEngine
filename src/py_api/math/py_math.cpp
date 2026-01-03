#include "ve/py_api/math/py_math.hpp"

#include "ve/py_api/math/py_rect2.hpp"
#include "ve/py_api/math/py_vec2.hpp"
#include "ve/py_api/math/py_vec3.hpp"
#include "ve/py_api/math/py_vec4.hpp"
#include <python3.13/modsupport.h>
#include <python3.13/object.h>
#include <python3.13/pytypedefs.h>

namespace VoidEngine::PyAPI::Math {
	static PyMethodDef Math_methods[] = {
		{ nullptr }
	};

	static struct PyModuleDef Math_module = {
		.m_base = PyModuleDef_HEAD_INIT,
		.m_name = "Math",
		.m_doc = "Im sure you can figure this out",
		.m_size = 0,
		.m_methods = Math_methods
	};

	PyMODINIT_FUNC PyInit_VoidEngine_Math(void) {
		PyTypeObject* modTypes[] = {
			&Vec2TypeObject,
			&Vec3TypeObject,
			&Vec4TypeObject,
			&Rect2TypeObject,
		};

		for(PyTypeObject* type : modTypes) {
			if(PyType_Ready(type) < 0) [[unlikely]] {
				for(PyTypeObject* toDec : modTypes) {
					Py_DecRef((PyObject*) toDec);
				}
				return nullptr;
			}
		}

		PyObject* module = PyModule_Create(&Math_module);

		for(PyTypeObject* type : modTypes) {
			if(PyModule_AddType(module, type) < 0) [[unlikely]] {
				for(PyTypeObject* toDec : modTypes) {
					Py_DecRef((PyObject*) toDec);
				}
				Py_DecRef(module);
				return nullptr;
			}
		}

		return module;
	}
}

