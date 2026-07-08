#include "ve/io/gfx/opengl/window.hpp"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_video.h"
#include "glbinding/gl/enum.h"
#include "glbinding/gl/functions.h"
#include "glbinding/glbinding.h"
#include "ve/io/gfx/renderer.hpp"
#include "ve/io/window.hpp"
#include <SDL3/SDL_video.h>
#include <memory>
#include <stdexcept>

namespace VoidEngine::IO::GFX::OpenGL {
	SDL_GLContext GLWindow::context = nullptr;

	GLWindow::GLWindow(Window::CreationOptions& options) {
		SDL_WindowFlags winFlags = SDL_WINDOW_TRANSPARENT | SDL_WINDOW_OPENGL;

		if(options.resizable) winFlags |= SDL_WINDOW_RESIZABLE;
		if(options.borderless) winFlags |= SDL_WINDOW_BORDERLESS;
		if(options.alwaysOnTop) winFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
		if(options.utility) winFlags |= SDL_WINDOW_UTILITY;
		if(!options.visible) winFlags |= SDL_WINDOW_HIDDEN;

		window = SDL_CreateWindow(options.title.c_str(), options.size.x, options.size.y, winFlags);
		if(window == nullptr) { throw std::runtime_error(SDL_GetError()); }

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

		if(context == nullptr) {
			context = SDL_GL_CreateContext(window);
			if(context == nullptr) { throw std::runtime_error(SDL_GetError()); }
			SDL_GL_MakeCurrent(window, context);
			glbinding::initialize(SDL_GL_GetProcAddress);
			SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, true);
		}
	}

	GLWindow::~GLWindow() {
		// SDL_GL_DestroyContext(context);
	}

	std::shared_ptr<Window> GLWindow::create(Window::CreationOptions& options) {
		auto window = std::shared_ptr<Window>(new GLWindow(options));
		WindowMap[SDL_GetWindowID(window->window)] = window;
		return window;
	}

	void GLWindow::swapBuffers() {
		bindRenderTarget();
		SDL_GL_SwapWindow(window);
	}

	void GLWindow::bindRenderTarget() {
		SDL_GL_MakeCurrent(window, context);
		gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, 0);
		Renderer::getInstance()->setViewport({ { 0, 0 }, getSize() });
	}
}
