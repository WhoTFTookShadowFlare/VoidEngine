#pragma once

#include "ve/io/gfx/render_target.hpp"
#include "ve/io/gfx/renderer_backend.hpp"
#include <SDL3/SDL_video.h>
#include <cstdint>
#include <map>

namespace VoidEngine::IO::GFX::OpenGL {
	class RendererOpenGL : public ARendererBackend {
		std::map<Window*, SDL_GLContext> contextMap;
	public:
		void setupWindow(Window*);
		void destroyWindow(Window*);
		void setRenderTarget(ARenderTarget*);
		void swapBuffers(Window*);

		Mesh *createMesh();

		Shader *createShader(ShaderType, AShaderSourceProvider&);
		GraphicsProgram *createGraphicsProgram(Shader *vertex, Shader *fragment);

		Texture *createTexture(uint8_t);
	};
}

