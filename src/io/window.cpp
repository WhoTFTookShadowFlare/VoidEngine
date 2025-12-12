#include "io/window.hpp"
#include "engine.hpp"
#include "io/window_event.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>
#include <glbinding/gl/functions.h>
#include <glbinding/glbinding.h>
#include <glbinding/gl46core/gl.h>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
#include <memory>

namespace VoidEngine::IO {
	std::map<SDL_WindowID, Window*> Window::windowMap;

	Window::Window(Window::CreationOptions& options) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_WindowFlags flags = SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL | SDL_WINDOW_TRANSPARENT;
		if(options.alwaysOnTop)	flags |= SDL_WINDOW_ALWAYS_ON_TOP;
		if(options.borderless)	flags |= SDL_WINDOW_BORDERLESS;
		if(options.utility)			flags |= SDL_WINDOW_UTILITY;
		if(options.resizable)		flags |= SDL_WINDOW_RESIZABLE;
		window = SDL_CreateWindow("HEWO 4:38", options.startingSize.x, options.startingSize.y, flags);
		if(window == nullptr) {
			std::cout << SDL_GetError() << std::endl;
			return;
		}

		if(Engine::instance && Engine::instance->mainWindow) {
			SDL_SetWindowParent(window, Engine::instance->mainWindow->window);
		}

		glContext = SDL_GL_CreateContext(window);
		if(glContext == nullptr) {
			std::cout << SDL_GetError() << std::endl;
			return;
		}

		SDL_GL_MakeCurrent(window, glContext);
		glbinding::initialize(SDL_GL_GetProcAddress);
		windowMap[SDL_GetWindowID(window)] = this;

		SDL_ShowWindow(window);
	}

	Window::~Window() {
		windowMap.erase(SDL_GetWindowID(window));
		SDL_GL_DestroyContext(glContext);
		SDL_DestroyWindow(window);
	}

	std::shared_ptr<Window> Window::create(Window::CreationOptions& options) {
		auto instance = std::shared_ptr<Window>(new Window(options));
	
		instance->onCloseRequested.addListener(instance);

		return instance;
	}

	void Window::bindRenderTarget() {
		SDL_GL_MakeCurrent(window, glContext);
		gl::glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}

	void Window::setClearColor(glm::vec4 color) {
		clearColor = color;
	}

	void Window::onEvent(Events::WindowCloseRequested& event) {
		closeRequested = true;
	}

	void Window::setWindowVisible(bool value) {
		(value ? SDL_ShowWindow : SDL_HideWindow)(window);
	}

	glm::ivec2 Window::getPosition() {
		glm::ivec2 position = { 0, 0 };
		SDL_GetWindowPosition(window, &position.x, &position.y);
		return position;
	}

	glm::ivec2 Window::getSize() {
		glm::ivec2 size = { 0, 0 };
		SDL_GetWindowSize(window, &size.x, &size.y);
		return size;
	}

	void Window::setPosition(glm::ivec2 position) {
		SDL_SetWindowPosition(window, position.x, position.y);
	}

	void Window::setSize(glm::ivec2 size) {
		SDL_SetWindowSize(window, size.x, size.y);
	}

	bool Window::shouldClose() {
		return closeRequested;
	}

	void Window::swapBuffers() {
		SDL_GL_SwapWindow(window);
	}
}
