#include "ve/io/window.hpp"
#include <SDL3/SDL_video.h>
#include <glm/ext/vector_int2.hpp>
#include <print>

namespace VoidEngine::IO {
	std::map<SDL_WindowID, std::weak_ptr<Window>> Window::WindowMap;

	Window::~Window() {
		if(WindowMap.contains(SDL_GetWindowID(window))) WindowMap.erase(SDL_GetWindowID(window));
		SDL_DestroyWindow(window);
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
			std::println("{}", SDL_GetError());
	}

	glm::ivec2 Window::getSize() {
		glm::ivec2 size = { 0, 0 };
		if(!SDL_GetWindowSize(window, &size.x, &size.y))
			std::println("{}", SDL_GetError());
		return size;
	}

	void Window::setPosition(glm::ivec2 position) {
		if(!SDL_SetWindowPosition(window, position.x, position.y))
			std::println("{}", SDL_GetError());
	}

	glm::ivec2 Window::getPosition() {
		glm::ivec2 position = { 0, 0 };
		if(!SDL_GetWindowPosition(window, &position.x, &position.y))
			std::println("{}", SDL_GetError());
		return position;
	}

	void Window::setTitle(std::string value) {
		if(!SDL_SetWindowTitle(window, value.c_str()))
			std::println("{}", SDL_GetError());
	}

	std::string Window::getTitle() {
		return SDL_GetWindowTitle(window);
	}

	void Window::setBorderless(bool value) {
		if(!SDL_SetWindowBordered(window, !value))
			std::println("{}", SDL_GetError());
	}

	bool Window::isBorderlress() {
		return SDL_GetWindowFlags(window) | SDL_WINDOW_BORDERLESS;
	}

	void Window::setResizable(bool value) {
		if(!SDL_SetWindowResizable(window, value))
			std::println("{}", SDL_GetError());
	}

	bool Window::isResizable() {
		return SDL_GetWindowFlags(window) | SDL_WINDOW_RESIZABLE;
	}

	void Window::setAlwaysOnTop(bool value) {
		if(!SDL_SetWindowAlwaysOnTop(window, value))
			std::println("{}", SDL_GetError());
	}

	bool Window::isAlwaysOnTop() {
		return SDL_GetWindowFlags(window) | SDL_WINDOW_ALWAYS_ON_TOP;
	}

	void Window::setVisible(bool value) {
		if(!(value ? SDL_ShowWindow : SDL_HideWindow)(window))
			std::println("{}", SDL_GetError());
	}
	
	bool Window::isVisible() {
		return SDL_GetWindowFlags(window) | SDL_WINDOW_HIDDEN;
	}

	void bindRenderTarget() {

	}
}
