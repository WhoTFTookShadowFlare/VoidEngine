#include "ve/io/window.hpp"
#include "ve/io/gfx/renderer.hpp"
#include <SDL3/SDL_video.h>
#include <glm/ext/vector_int2.hpp>
#include <memory>

namespace VoidEngine::IO {
	Window::Window(CreationOptions& options) {
		// TODO: Extract SDL_WINDOW_OPENGL
		SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_TRANSPARENT;

		if(options.resizable) flags |= SDL_WINDOW_RESIZABLE;
		if(options.borderless) flags |= SDL_WINDOW_BORDERLESS;
		if(options.alwaysOnTop) flags |= SDL_WINDOW_ALWAYS_ON_TOP;
		if(options.utility) flags |= SDL_WINDOW_UTILITY;

		window = SDL_CreateWindow(options.title.c_str(), options.size.x, options.size.y, flags);
		auto renderer = GFX::Renderer::getInstance();
		renderer->setupWindow(this);
	}

	Window::~Window() {
		auto renderer = GFX::Renderer::getInstance();
		renderer->destroyWindow(this);
		SDL_DestroyWindow(window);
	}

	std::shared_ptr<Window> Window::create(CreationOptions& options) {
		return std::shared_ptr<Window>(new Window(options));
	}

	void Window::setClosing(bool value) {
		closing = value;
	}

	void Window::close() {
		setClosing(true);
	}

	bool Window::isClosing() const {
		return closing;
	}

	void Window::setSize(glm::ivec2 size) {
		SDL_SetWindowSize(window, size.x, size.y);
	}

	glm::ivec2 Window::getSize() {
		glm::ivec2 size;
		SDL_GetWindowSize(window, &size.x, &size.y);
		return size;
	}

	void Window::setPosition(glm::ivec2 position) {
		SDL_SetWindowPosition(window, position.x, position.y);
	}

	glm::ivec2 Window::getPosition() {
		glm::ivec2 position;
		SDL_GetWindowPosition(window, &position.x, &position.y);
		return position;
	}

	void Window::setTitle(std::string value) {
		SDL_SetWindowTitle(window, value.c_str());
	}

	std::string Window::getTitle() {
		return SDL_GetWindowTitle(window);
	}
}

