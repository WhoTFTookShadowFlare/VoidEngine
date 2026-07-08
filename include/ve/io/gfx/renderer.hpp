#pragma once

#include "glm/ext/vector_int2.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/io/gfx/renderer_backend.hpp"
#include "ve/io/gfx/shader.hpp"
#include "ve/io/res_providers/source/a_provider.hpp"
#include "ve/io/gfx/texture.hpp"
#include "ve/io/window.hpp"
#include "ve/math/rect2.hpp"
#include <cstdint>
#include <glm/ext/vector_float4.hpp>
#include <memory>
#include <optional>

namespace VoidEngine::IO::GFX {
	using std::shared_ptr;
	class Renderer final {
		friend class ::VoidEngine::IO::Window;
		static shared_ptr<Renderer> instance;
		ARendererBackend *backend = nullptr;
	
		void setupWindow(Window*);
		void destroyWindow(Window*);

		Renderer();

	public:
		~Renderer();
		static std::shared_ptr<Renderer> getInstance();

		void bindRenderTarget(shared_ptr<IRenderTarget>);
		void clear(glm::vec4 color = { 0.1, 0.1, 0.1, 1.0 });
		void swapBuffers(shared_ptr<Window>);

		void setViewport(VoidEngine::Math::Rect2i);
		void setDrawArea(std::optional<VoidEngine::Math::Rect2i>);

		shared_ptr<Window> createWindow(Window::CreationOptions&);

		shared_ptr<Mesh> createMesh();

		shared_ptr<Shader> createShader(ShaderType, VoidEngine::IO::ResourceProviders::ASourceProvider&);
		shared_ptr<GraphicsProgram> createGraphicsProgram(shared_ptr<Shader> vertex, shared_ptr<Shader> fragment);
		
		shared_ptr<Texture> createTexture(uint8_t slot);
	};
}

