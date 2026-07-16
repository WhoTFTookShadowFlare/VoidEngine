#include "backend_opengl.hpp"
#include "glbinding/gl/bitfield.h"
#include "glbinding/gl/enum.h"
#include "glbinding/gl/functions.h"
#include "ve/io/gfx/mesh.hpp"
#include "graphics_program_opengl.hpp"
#include "window_opengl.hpp"
#include "mesh_opengl.hpp"
#include "shader_opengl.hpp"
#include "texture_opengl.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/io/res_providers/source/a_provider.hpp"
#include "ve/io/window.hpp"
#include "ve/math/rect2.hpp"
#include <cstdint>
#include <glbinding/glbinding.h>
#include <SDL3/SDL_video.h>
#include <glbinding/gl46core/gl.h>

namespace VoidEngine::IO::GFX::OpenGL {
	using namespace gl;

	void RendererOpenGL::bindRenderTarget(std::shared_ptr<IRenderTarget> target) {
		target->bindRenderTarget();
	}

	void RendererOpenGL::clear(glm::vec4 color) {
		glClearColor(color.x, color.y, color.z, color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererOpenGL::swapBuffers(std::shared_ptr<Window> window) {
		window->swapBuffers();
	}

	void RendererOpenGL::setViewport(VoidEngine::Math::Rect2i viewport) {
		glViewport(
			viewport.position.x, viewport.position.y,
			viewport.size.x, viewport.size.y
		);
	}

	void RendererOpenGL::setDrawArea(std::optional<VoidEngine::Math::Rect2i> area) {
		if(area.has_value()) {
			glEnable(gl::GLenum::GL_SCISSOR_TEST);
			auto value = area.value();
			glScissor(
				value.position.x, value.position.y,
				value.size.x, value.size.y
			);
		} else {
			glDisable(gl::GLenum::GL_SCISSOR_TEST);
		}
	}

	void RendererOpenGL::useDepth(bool value) {
		(value ? glEnable : glDisable)(GL_DEPTH_TEST);
	}

	shared_ptr<Window> RendererOpenGL::createWindow(Window::CreationOptions& options) {
		return GLWindow::create(options);
	}

	shared_ptr<Mesh> RendererOpenGL::createMesh() {
		return shared_ptr<Mesh>(new GLMesh);
	}

	shared_ptr<Shader> RendererOpenGL::createShader(ShaderType type, VoidEngine::IO::ResourceProviders::ASourceProvider& sourceCode) {
		return shared_ptr<Shader>(new GLShader(type, sourceCode));
	}

	shared_ptr<GraphicsProgram> RendererOpenGL::createGraphicsProgram(shared_ptr<Shader> vertex, shared_ptr<Shader> fragment) {
		return shared_ptr<GraphicsProgram>(new GLGraphicsProgram(vertex, fragment));
	}

	shared_ptr<Texture> RendererOpenGL::createTexture(uint8_t slot) {
		return shared_ptr<Texture>(new GLTexture(slot));
	}
}

