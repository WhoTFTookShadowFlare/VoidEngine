#pragma once

#include "SDL3/SDL_video.h"
#include "ve/io/window.hpp"
#include <memory>

namespace VoidEngine::IO::GFX::OpenGL {
	class GLWindow final : public Window {
	private:
		GLWindow(Window::CreationOptions&);
		static SDL_GLContext context;
	public:
		static std::shared_ptr<Window> create(Window::CreationOptions&);
		~GLWindow();

		void swapBuffers() override;
		void bindRenderTarget() override;
	};
}
