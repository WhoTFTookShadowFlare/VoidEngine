#pragma once

#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::CS::Scene {
	void initModule_Engine_Scene(void);

	MonoClass *getSceneClass(void);
	MonoClass *getGameObjectClass(void);
	MonoClass *getComponentUpdaterClass(void);
	MonoClass *getAObjectComponentClass(void);
	MonoClass *getTransformComponentClass(void);
	MonoClass *getMeshComponentClass(void);
}

