#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/renderer_backend.hpp"
#include "ve/io/gfx/shader.hpp"
#include "ve/io/gfx/shader_source_provider.hpp"
#include "ve/io/gfx/texture.hpp"
#include <cstdint>
#include <glm/ext/vector_float4.hpp>
#include <memory>

namespace VoidEngine::IO::GFX {
	using std::shared_ptr;
	class Renderer {
		friend class ::VoidEngine::IO::Window;
		static shared_ptr<Renderer> instance;
		ARendererBackend *backend = nullptr;
	
		void setupWindow(Window*);
		void destroyWindow(Window*);

		Renderer();

	public:
		~Renderer();
		static std::shared_ptr<Renderer> getInstance();

		void bindRenderTarget(Window*);
		void clear(glm::vec4 color = { 0.1, 0.1, 0.1, 1.0 });
		void swapBuffers(Window*);

		shared_ptr<Mesh> createMesh();

		shared_ptr<Shader> createShader(ShaderType, AShaderSourceProvider&);
		shared_ptr<GraphicsProgram> createGraphicsProgram(shared_ptr<Shader> vertex, shared_ptr<Shader> fragment);
		
		shared_ptr<Texture> createTexture(uint8_t slot);
	};
}

