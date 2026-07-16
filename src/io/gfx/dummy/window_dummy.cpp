#include "ve/io/gfx/dummy/window_dummy.hpp"
#include "SDL3/SDL_video.h"
#include <memory>

namespace VoidEngine::IO::GFX::Dummy {
	DummyWindow::DummyWindow(Window::CreationOptions& options) {
		SDL_WindowFlags winFlags = SDL_WINDOW_TRANSPARENT;

		if(options.resizable) winFlags |= SDL_WINDOW_RESIZABLE;
		if(options.borderless) winFlags |= SDL_WINDOW_BORDERLESS;
		if(options.alwaysOnTop) winFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
		if(options.utility) winFlags |= SDL_WINDOW_UTILITY;
		if(!options.visible) winFlags |= SDL_WINDOW_HIDDEN;

		window = SDL_CreateWindow(options.title.c_str(), options.size.x, options.size.y, winFlags);
		if(window == nullptr) { throw std::runtime_error(SDL_GetError()); }
	}

	std::shared_ptr<DummyWindow> DummyWindow::create(Window::CreationOptions& opts) {
		auto window = std::shared_ptr<DummyWindow>(new DummyWindow(opts));
		WindowMap[SDL_GetWindowID(window->window)] = window;
		return window;
	}

	void DummyWindow::swapBuffers() {}
	void DummyWindow::bindRenderTarget() {}
}
