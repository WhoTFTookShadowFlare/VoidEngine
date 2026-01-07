#pragma once

#include "pocketpy.h"

namespace VoidEngine::PyAPI::IO::GFX {
	extern py_Type vertexType;
	void initVertexPyType(py_GlobalRef module);
}
