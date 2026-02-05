#include "ve/io/gfx/opengl/backend.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/opengl/graphics_program.hpp"
#include "ve/io/gfx/opengl/mesh.hpp"
#include "ve/io/gfx/opengl/shader.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/io/window.hpp"
#include <glbinding/glbinding.h>
#include <SDL3/SDL_video.h>

namespace VoidEngine::IO::GFX::OpenGL {
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

	void RendererOpenGL::setRenderTarget(ARenderTarget *target) {
		Window *window = static_cast<Window*>(target);
		SDL_GL_MakeCurrent(window->window, contextMap[window]);
	}

	void RendererOpenGL::swapBuffers(Window *window) {
		SDL_GL_SwapWindow(window->window);
	}

	Mesh *RendererOpenGL::createMesh() {
		return new GLMesh;
	}

	Shader *RendererOpenGL::createShader(ShaderType type, AShaderSourceProvider& sourceCode) {
		return new GLShader(type, sourceCode);
	}

	GraphicsProgram *RendererOpenGL::createGraphicsProgram(Shader *vertex, Shader *fragment) {
		return new GLGraphicsProgram(vertex, fragment);
	}
}

