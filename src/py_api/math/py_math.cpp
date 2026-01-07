#include "ve/py_api/math/py_math.hpp"

#include "pocketpy.h"
#include "ve/py_api/math/py_rect2.hpp"
#include "ve/py_api/math/py_vec2.hpp"
#include "ve/py_api/math/py_vec3.hpp"
#include "ve/py_api/math/py_vec4.hpp"

namespace VoidEngine::PyAPI::Math {
	void PyInit_VoidEngine_Math(void) {
		py_GlobalRef module = py_newmodule("VoidEngine.Math");
		initVec2PyType(module);
		initVec3PyType(module);
		initVec4PyType(module);

		initRect2PyType(module);
	}
}

