#include "ve/io/gfx/renderer.hpp"
#include "ve/io/gfx/opengl/backend.hpp"
#include "ve/io/gfx/render_target.hpp"
#include <memory>

namespace VoidEngine::IO::GFX {
	std::shared_ptr<Renderer> Renderer::instance = nullptr;

	Renderer::Renderer() {
		backend = new OpenGL::RendererOpenGL;
	}

	Renderer::~Renderer() {
		if(backend == nullptr) return;
		delete backend;
	}

	std::shared_ptr<Renderer> Renderer::getInstance() {
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

	void Renderer::setRenderTarget(ARenderTarget *target) {
		if(backend == nullptr) return;
		backend->setRenderTarget(target);
	}

	void Renderer::swapBuffers(Window *window) {
		if(backend == nullptr) return;
		backend->swapBuffers(window);
	}

	Mesh *Renderer::createMesh() {
		if(backend == nullptr) return nullptr;
		return backend->createMesh();
	}

	Shader *Renderer::createShader(ShaderType type, AShaderSourceProvider& sourceCode) {
		if(backend == nullptr) return nullptr;
		return backend->createShader(type, sourceCode);
	}

	GraphicsProgram *Renderer::createGraphicsProgram(Shader *vertex, Shader *fragment) {
		if(backend == nullptr) return nullptr;
		return backend->createGraphicsProgram(vertex, fragment);
	}
}


