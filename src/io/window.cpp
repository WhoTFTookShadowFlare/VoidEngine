#include "ve/io/window.hpp"
#include "ve/io/gfx/renderer.hpp"
#include <SDL3/SDL_video.h>
#include <glm/ext/vector_int2.hpp>
#include <memory>
#include <iostream>

namespace VoidEngine::IO {
	std::map<SDL_WindowID, std::weak_ptr<Window>> Window::WindowMap;

	Window::Window(CreationOptions& options) {
		// TODO: Extract SDL_WINDOW_OPENGL
		SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_TRANSPARENT;

		if(options.resizable) flags |= SDL_WINDOW_RESIZABLE;
		if(options.borderless) flags |= SDL_WINDOW_BORDERLESS;
		if(options.alwaysOnTop) flags |= SDL_WINDOW_ALWAYS_ON_TOP;
		if(options.utility) flags |= SDL_WINDOW_UTILITY;
		if(!options.visible) flags |= SDL_WINDOW_HIDDEN;

		window = SDL_CreateWindow(options.title.c_str(), options.size.x, options.size.y, flags);
		if(window == nullptr) throw std::runtime_error(SDL_GetError());
		auto renderer = GFX::Renderer::getInstance();
		renderer->setupWindow(this);
	}

	Window::~Window() {
		//WindowMap[SDL_GetWindowID(window)] = std::weak_ptr<Window>();
		//WindowMap.erase(SDL_GetWindowID(window));
		auto renderer = GFX::Renderer::getInstance();
		renderer->destroyWindow(this);
		SDL_DestroyWindow(window);
	}

	std::shared_ptr<Window> Window::create(CreationOptions& options) {
		auto window = std::shared_ptr<Window>(new Window(options));
		WindowMap[SDL_GetWindowID(window->window)] = window;
		return window;
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
		if(!SDL_SetWindowSize(window, size.x, size.y))
			std::cerr << SDL_GetError() << std::endl;
	}

	glm::ivec2 Window::getSize() {
		glm::ivec2 size = { 0, 0 };
		if(!SDL_GetWindowSize(window, &size.x, &size.y))
			std::cerr << SDL_GetError() << std::endl;
		return size;
	}

	void Window::setPosition(glm::ivec2 position) {
		if(!SDL_SetWindowPosition(window, position.x, position.y))
			std::cerr << SDL_GetError() << std::endl;
	}

	glm::ivec2 Window::getPosition() {
		glm::ivec2 position = { 0, 0 };
		if(!SDL_GetWindowPosition(window, &position.x, &position.y))
			std::cerr << SDL_GetError() << std::endl;
		return position;
	}

	void Window::setTitle(std::string value) {
		if(!SDL_SetWindowTitle(window, value.c_str()))
			std::cerr << SDL_GetError() << std::endl;
	}

	std::string Window::getTitle() {
		return SDL_GetWindowTitle(window);
	}

	void Window::setBorderless(bool value) {
		if(!SDL_SetWindowBordered(window, value))
			std::cerr << SDL_GetError() << std::endl;
	}

	bool Window::isBorderlress() {
		return SDL_GetWindowFlags(window) | SDL_WINDOW_BORDERLESS;
	}

	void Window::setResizable(bool value) {
		if(!SDL_SetWindowResizable(window, value))
			std::cerr << SDL_GetError() << std::endl;
	}

	bool Window::isResizable() {
		return SDL_GetWindowFlags(window) | SDL_WINDOW_RESIZABLE;
	}

	void Window::setAlwaysOnTop(bool value) {
		if(!SDL_SetWindowAlwaysOnTop(window, value))
			std::cerr << SDL_GetError() << std::endl;
	}

	bool Window::isAlwaysOnTop() {
		return SDL_GetWindowFlags(window) | SDL_WINDOW_ALWAYS_ON_TOP;
	}

	void Window::setVisible(bool value) {
		if(!(value ? SDL_ShowWindow : SDL_HideWindow)(window))
			std::cerr << SDL_GetError() << std::endl;
	}
	
	bool Window::isVisible() {
		return SDL_GetWindowFlags(window) | SDL_WINDOW_HIDDEN;
	}
}
