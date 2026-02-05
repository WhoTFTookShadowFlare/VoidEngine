#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/io/gfx/renderer_backend.hpp"
#include "ve/io/gfx/shader.hpp"
#include "ve/io/gfx/shader_source_provider.hpp"
#include <memory>

namespace VoidEngine::IO::GFX {
	class Renderer {
		friend class ::VoidEngine::IO::Window;
		static std::shared_ptr<Renderer> instance;
		ARendererBackend *backend = nullptr;
	
		void setupWindow(Window*);
		void destroyWindow(Window*);

		Renderer();

	public:
		~Renderer();
		static std::shared_ptr<Renderer> getInstance();

		void setRenderTarget(ARenderTarget*);

		void swapBuffers(Window*);

		Mesh *createMesh();

		Shader *createShader(ShaderType, AShaderSourceProvider&);
		GraphicsProgram *createGraphicsProgram(Shader *vertex, Shader *fragment);
	};
}

