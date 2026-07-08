#pragma once

#include "glm/ext/vector_int2.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/io/gfx/shader.hpp"
#include "ve/io/res_providers/source/a_provider.hpp"
#include "ve/io/gfx/texture.hpp"
#include "ve/io/window.hpp"
#include "ve/math/rect2.hpp"
#include <cstdint>
#include <glm/ext/vector_float4.hpp>
#include <memory>
#include <optional>

namespace VoidEngine::IO {
	class Window;
	namespace GFX {
		using std::shared_ptr;
		class ARendererBackend {
		public:
			virtual ~ARendererBackend() {}
			// virtual void setupWindow(Window*) = 0;
			// virtual void destroyWindow(Window*) = 0;
			virtual void bindRenderTarget(shared_ptr<IRenderTarget>) = 0;
			virtual void clear(glm::vec4 color) = 0;
			virtual void swapBuffers(shared_ptr<Window>) = 0;

			virtual void setViewport(VoidEngine::Math::Rect2i) = 0;
			virtual void setDrawArea(std::optional<VoidEngine::Math::Rect2i>) = 0;

			virtual shared_ptr<Window> createWindow(Window::CreationOptions&) = 0;

			virtual shared_ptr<Mesh> createMesh() = 0;
			
			virtual shared_ptr<Shader> createShader(ShaderType, VoidEngine::IO::ResourceProviders::ASourceProvider&) = 0;
			virtual shared_ptr<GraphicsProgram> createGraphicsProgram(shared_ptr<Shader> vertex, shared_ptr<Shader> fragment) = 0;

			virtual shared_ptr<Texture> createTexture(uint8_t slot) = 0;
		};
	}
}

