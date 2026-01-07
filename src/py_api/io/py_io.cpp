#include "ve/py_api/io/py_io.hpp"
#include "ve/py_api/io/gfx/py_gfx.hpp"

#include "pocketpy.h"

namespace VoidEngine::PyAPI::IO {
	void PyInit_VoidEngine_IO(void) {
		py_GlobalRef module = py_newmodule("VoidEngine.IO");

		GFX::PyInit_VoidEngine_IO_GFX();
	}
}

