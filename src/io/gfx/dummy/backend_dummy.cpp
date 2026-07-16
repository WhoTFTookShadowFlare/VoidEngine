#include "ve/io/gfx/dummy/backend_dummy.hpp"
#include "ve/io/gfx/dummy/graphics_program_dummy.hpp"
#include "ve/io/gfx/dummy/mesh_dummy.hpp"
#include "ve/io/gfx/dummy/shader_dummy.hpp"
#include "ve/io/gfx/dummy/texture_dummy.hpp"
#include "ve/io/gfx/dummy/window_dummy.hpp"

namespace VoidEngine::IO::GFX::Dummy {
	void DummyBackend::bindRenderTarget(shared_ptr<IRenderTarget>) {}
	void DummyBackend::clear(glm::vec4 color) {}
	void DummyBackend::swapBuffers(shared_ptr<Window> win) { win->swapBuffers(); }

	void DummyBackend::setViewport(VoidEngine::Math::Rect2i) {}
	void DummyBackend::setDrawArea(std::optional<VoidEngine::Math::Rect2i>) {}

	void DummyBackend::useDepth(bool) {}

	shared_ptr<Window> DummyBackend::createWindow(Window::CreationOptions& opts) {
		return DummyWindow::create(opts);
	}

	shared_ptr<Mesh> DummyBackend::createMesh() {
		return DummyMesh::create();
	}
	
	shared_ptr<Shader> DummyBackend::createShader(ShaderType type, VoidEngine::IO::ResourceProviders::ASourceProvider&) {
		return DummyShader::create(type);
	}

	shared_ptr<GraphicsProgram> DummyBackend::createGraphicsProgram(shared_ptr<Shader> vertex, shared_ptr<Shader> fragment) {
		return DummyGraphicsProgram::create();
	}

	shared_ptr<Texture> DummyBackend::createTexture(uint8_t slot) {
		return DummyTexture::create();
	}
}