#pragma once

#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::CS::Math {
	void initModule_Engine_Math(void);

	MonoClass *getRect2fClass(void);
	MonoClass *getRect2iClass(void);

	MonoClass *getVec2fClass(void);
	MonoClass *getVec3fClass(void);
	MonoClass *getVec4fClass(void);
	MonoClass *getVec2iClass(void);
	MonoClass *getVec3iClass(void);
	MonoClass *getVec4iClass(void);
}
