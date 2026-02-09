#pragma once

#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::CS::IO::GFX {
	void initModule_Engine_IO_GFX(void);

	MonoClass *getRendererClass(void);

	MonoClass *getVertexClass(void);
	MonoClass *getMeshClass(void);
	MonoClass *getMeshProviderClass(void);

	MonoClass *getFileShaderSourceProviderClass(void);
	MonoClass *getShaderSourceProviderClass(void);
	MonoClass *getShaderClass(void);

	MonoClass *getGraphicsProgramClass(void);
	MonoClass *getUniformClass(void);

	MonoClass *getTextureClass(void);
	MonoClass *getTextureProviderClass(void);
}

