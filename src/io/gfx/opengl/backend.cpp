#include "ve/io/gfx/opengl/backend.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/opengl/graphics_program.hpp"
#include "ve/io/gfx/opengl/mesh.hpp"
#include "ve/io/gfx/opengl/shader.hpp"
#include "ve/io/gfx/opengl/texture.hpp"
#include "ve/io/window.hpp"
#include <cstdint>
#include <glbinding/glbinding.h>
#include <SDL3/SDL_video.h>
#include <glbinding/gl46core/gl.h>

namespace VoidEngine::IO::GFX::OpenGL {
	using namespace gl;
	void RendererOpenGL::setupWindow(Window *window) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

		SDL_GLContext context = SDL_GL_CreateContext(window->window);
		SDL_GL_MakeCurrent(window->window, context);
		glbinding::initialize(SDL_GL_GetProcAddress);
		SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, true);

		contextMap[window] = context;
	}

	void RendererOpenGL::destroyWindow(Window *window) {
		SDL_GL_DestroyContext(contextMap[window]);
		contextMap.erase(window);
	}

	void RendererOpenGL::bindRenderTarget(Window *window) {
		SDL_GL_MakeCurrent(window->window, contextMap[window]);
	}

	void RendererOpenGL::clear(glm::vec4 color) {
		glClearColor(color.x, color.y, color.z, color.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RendererOpenGL::swapBuffers(Window *window) {
		SDL_GL_SwapWindow(window->window);
	}

	shared_ptr<Mesh> RendererOpenGL::createMesh() {
		return shared_ptr<Mesh>(new GLMesh);
	}

	shared_ptr<Shader> RendererOpenGL::createShader(ShaderType type, AShaderSourceProvider& sourceCode) {
		return shared_ptr<Shader>(new GLShader(type, sourceCode));
	}

	shared_ptr<GraphicsProgram> RendererOpenGL::createGraphicsProgram(shared_ptr<Shader> vertex, shared_ptr<Shader> fragment) {
		return shared_ptr<GraphicsProgram>(new GLGraphicsProgram(vertex, fragment));
	}

	shared_ptr<Texture> RendererOpenGL::createTexture(uint8_t slot) {
		return shared_ptr<Texture>(new GLTexture(slot));
	}
}

