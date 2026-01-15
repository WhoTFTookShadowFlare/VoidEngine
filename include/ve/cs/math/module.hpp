#pragma once

#include "ve/math/rect2.hpp"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::CS::Math {
	void initModule_Engine_Math(void);

	MonoObject *vec2fToMonoObject(glm::vec2);
	MonoObject *rect2fToMonoObject(VoidEngine::Math::Rect2f);

	MonoObject *vec2iToMonoObject(glm::ivec2);
	MonoObject *rect2iToMonoObject(VoidEngine::Math::Rect2i);

	glm::vec2 vec2fFromMonoObject(MonoObject *);
	VoidEngine::Math::Rect2f rect2fFromMonoObject(MonoObject *);

	glm::ivec2 vec2iFromMonoObject(MonoObject *);
	VoidEngine::Math::Rect2i rect2iFromMonoObject(MonoObject *);

	MonoClass *getVec2fClass();
	MonoClass *getRect2fClass();
	MonoClass *getVec2iClass();
	MonoClass *getRect2iClass();
}
