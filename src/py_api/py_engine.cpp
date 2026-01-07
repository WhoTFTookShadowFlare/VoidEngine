#include "ve/py_api/py_engine.hpp"
#include "pocketpy.h"

namespace VoidEngine::PyAPI {
	void PyInit_VoidEngine_Engine(void) {
		py_GlobalRef module = py_newmodule("VoidEngine.Engine");

	}
}

