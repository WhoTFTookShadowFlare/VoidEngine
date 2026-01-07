#include "ve/py_api/io/gfx/py_gfx.hpp"

#include "pocketpy.h"
#include "ve/py_api/io/gfx/py_vertex.hpp"

namespace VoidEngine::PyAPI::IO::GFX {
	void PyInit_VoidEngine_IO_GFX(void) {
		py_GlobalRef module = py_newmodule("VoidEngine.IO.GFX");
		initVertexPyType(module);
	}
}

