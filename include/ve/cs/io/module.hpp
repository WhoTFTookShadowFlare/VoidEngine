#pragma once

#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::CS::IO {
	void initModule_Engine_IO(void);

	MonoClass *getWindowCreationOptionsClass(void);
	MonoClass *getWindowClass(void);
}

