#include "ve/py_api/py_module.hpp"
#include <glm/ext/vector_float2.hpp>
#include "ve/py_api/io/py_io.hpp"
#include "ve/py_api/math/py_math.hpp"
#include "ve/py_api/py_engine.hpp"

#include <pocketpy.h>

namespace VoidEngine::PyAPI {
	bool isInitialized = false;

	void PyInit_VoidEngine(void) {
		py_GlobalRef module = py_newmodule("VoidEngine");
		
		PyInit_VoidEngine_Engine();
		Math::PyInit_VoidEngine_Math();
		IO::PyInit_VoidEngine_IO();
	}

	void initVoidEnginePyAPI(void) {
		if(isInitialized) return;
		py_initialize();
		PyInit_VoidEngine();
		isInitialized = true;
	}
}

