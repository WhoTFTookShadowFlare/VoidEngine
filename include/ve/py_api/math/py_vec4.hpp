#pragma once

#include "pocketpy.h"
#include <glm/ext/vector_float4.hpp>

namespace VoidEngine::PyAPI::Math {
	extern py_Type vec4Type;
	void initVec4PyType(py_GlobalRef module);
}

