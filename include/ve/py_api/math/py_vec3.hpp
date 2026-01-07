#pragma once

#include "pocketpy.h"
#include <glm/ext/vector_float3.hpp>

namespace VoidEngine::PyAPI::Math {
	extern py_Type vec3Type;
	void initVec3PyType(py_GlobalRef module);
}

