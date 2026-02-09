#pragma once

#include "ve/io/gfx/renderer_backend.hpp"
#include <SDL3/SDL_video.h>
#include <cstdint>
#include <map>
#include <memory>

namespace VoidEngine::IO::GFX::OpenGL {
	using std::shared_ptr;
	class RendererOpenGL : public ARendererBackend {
		std::map<Window*, SDL_GLContext> contextMap;
	public:
		void setupWindow(Window*);
		void destroyWindow(Window*);
		void bindRenderTarget(Window*);
		void clear(glm::vec4 color);
		void swapBuffers(Window*);

		shared_ptr<Mesh> createMesh();

		shared_ptr<Shader> createShader(ShaderType, AShaderSourceProvider&);
		shared_ptr<GraphicsProgram> createGraphicsProgram(shared_ptr<Shader> vertex, shared_ptr<Shader> fragment);

		shared_ptr<Texture> createTexture(uint8_t);
	};
}

