#pragma once

#include "ve/io/window.hpp"
#include <memory>

namespace VoidEngine::IO::GFX::Dummy {
	class DummyWindow final : public Window {
	private:
		DummyWindow(Window::CreationOptions&);
	public:
		static std::shared_ptr<DummyWindow> create(Window::CreationOptions&);

		void swapBuffers();
		void bindRenderTarget();
	};
}
