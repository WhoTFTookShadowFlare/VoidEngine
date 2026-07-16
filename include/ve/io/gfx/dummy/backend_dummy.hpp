#pragma once

#include "ve/io/gfx/renderer_backend.hpp"

namespace VoidEngine::IO::GFX::Dummy {
	class DummyBackend final : public ARendererBackend {
	public:
		void bindRenderTarget(shared_ptr<IRenderTarget>);
		void clear(glm::vec4 color);
		void swapBuffers(shared_ptr<Window>);

		void setViewport(VoidEngine::Math::Rect2i);
		void setDrawArea(std::optional<VoidEngine::Math::Rect2i>);

		void useDepth(bool);

		shared_ptr<Window> createWindow(Window::CreationOptions&);

		shared_ptr<Mesh> createMesh();
		
		shared_ptr<Shader> createShader(ShaderType, VoidEngine::IO::ResourceProviders::ASourceProvider&);
		shared_ptr<GraphicsProgram> createGraphicsProgram(shared_ptr<Shader> vertex, shared_ptr<Shader> fragment);

		shared_ptr<Texture> createTexture(uint8_t slot);
	};
}
