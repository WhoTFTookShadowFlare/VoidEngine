#include "ve/io/gfx/renderer.hpp"
#include "ve/io/gfx/opengl/backend.hpp"
#include <cstdint>
#include <memory>

namespace VoidEngine::IO::GFX {
	using std::shared_ptr;
	shared_ptr<Renderer> Renderer::instance = nullptr;

	Renderer::Renderer() {
		backend = new OpenGL::RendererOpenGL;
	}

	Renderer::~Renderer() {
		if(backend == nullptr) return;
		delete backend;
	}

	shared_ptr<Renderer> Renderer::getInstance() {
		if(instance == nullptr) {
			instance = std::shared_ptr<Renderer>(new Renderer);
		}
		return instance;
	}

	void Renderer::setupWindow(Window *window) {
		if(backend == nullptr) return;
		backend->setupWindow(window);
	}

	void Renderer::destroyWindow(Window *window) {
		if(backend == nullptr) return;
		backend->destroyWindow(window);
	}

	void Renderer::bindRenderTarget(std::shared_ptr<Window> target) {
		if(backend == nullptr) return;
		backend->bindRenderTarget(target);
	}

	void Renderer::clear(glm::vec4 color) {
		if(backend == nullptr) return;
		backend->clear(color);
	}

	void Renderer::swapBuffers(std::shared_ptr<Window> window) {
		if(backend == nullptr) return;
		backend->swapBuffers(window);
	}

	shared_ptr<Mesh> Renderer::createMesh() {
		if(backend == nullptr) return nullptr;
		return backend->createMesh();
	}

	shared_ptr<Shader> Renderer::createShader(ShaderType type, VoidEngine::IO::ResourceProviders::AShaderSourceProvider& sourceCode) {
		if(backend == nullptr) return nullptr;
		return backend->createShader(type, sourceCode);
	}

	shared_ptr<GraphicsProgram> Renderer::createGraphicsProgram(shared_ptr<Shader> vertex, shared_ptr<Shader> fragment) {
		if(backend == nullptr) return nullptr;
		return backend->createGraphicsProgram(vertex, fragment);
	}

	shared_ptr<Texture> Renderer::createTexture(uint8_t slot) {
		if(backend == nullptr) return nullptr;
		return backend->createTexture(slot);
	}
}


