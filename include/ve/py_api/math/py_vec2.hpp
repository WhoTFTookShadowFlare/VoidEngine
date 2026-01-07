#pragma once

#include "pocketpy.h"
#include <glm/ext/vector_float2.hpp>

namespace VoidEngine::PyAPI::Math {
	extern py_Type vec2Type;
	void initVec2PyType(py_GlobalRef module);
}

