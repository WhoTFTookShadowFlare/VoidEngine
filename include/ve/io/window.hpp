#pragma once

#include <SDL3/SDL_video.h>
#include <glm/ext/vector_int2.hpp>
#include <map>
#include <memory>
#include <string>

#include "input_events.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/event/event_bus.hpp"
#include "ve/io/window_events.hpp"
#include "ve/io/input_events.hpp"

namespace VoidEngine {
	class Engine;
#ifdef COMPONENT_GRAPHICS_OPENGL_ENABLED
	namespace IO::GFX::OpenGL {
		class GLWindow;
	}
#endif // COMPONENT_GRAPHICS_OPENGL_ENABLED
	namespace IO::GFX::Dummy {
		class DummyWindow;
	}
}

namespace VoidEngine::IO {
	class Window : public GFX::IRenderTarget, public std::enable_shared_from_this<Window> {
		friend class VoidEngine::Engine;

#ifdef COMPONENT_GRAPHICS_OPENGL_ENABLED
		friend class VoidEngine::IO::GFX::OpenGL::GLWindow;
#endif // COMPONENT_GRAPHICS_OPENGL_ENABLED
		friend class VoidEngine::IO::GFX::Dummy::DummyWindow;
	public:
		struct CreationOptions {
			glm::ivec2 size = { 800, 600 };
			std::string title = "VoidEngine";
			bool resizable = true;
			bool borderless = false;
			bool alwaysOnTop = false;
			bool utility = false;
			bool visible = true;
		};
	private:
		bool closing = false;
		
	protected:
		static std::map<SDL_WindowID, std::weak_ptr<Window>> WindowMap;
		SDL_Window *window = nullptr;
	
	public:
		virtual ~Window();

		Event::EventBus<Events::EWindowCloseRequested> onCloseRequested;
		Event::EventBus<Events::EWindowSizeChanged> onSizeChanged;
		Event::EventBus<Events::EWindowRepositioned> onReposition;
		Event::EventBus<Events::EWindowFocus> onFocusChanged;
		Event::EventBus<Events::EMouseEnter> onMouseEnter;
		Event::EventBus<Events::EWindowMinimized> onMinimize;
		Event::EventBus<Events::EWindowRestored> onRestore;
		Event::EventBus<Events::EWindowMaximized> onMaximize;

		Event::EventBus<Events::EMouseMotion> onMouseMotion;
		Event::EventBus<Events::EMouseButton> onMouseButton;
		Event::EventBus<Events::EKeyButton> onKeyButton;

		virtual void swapBuffers() = 0;

		void setClosing(bool value);
		void close();
		bool isClosing() const;

		void setSize(glm::ivec2);
		glm::ivec2 getSize() override;

		void setPosition(glm::ivec2);
		glm::ivec2 getPosition();

		void setTitle(std::string);
		std::string getTitle();

		void setBorderless(bool value);
		bool isBorderlress();

		void setResizable(bool value);
		bool isResizable();

		void setAlwaysOnTop(bool value);
		bool isAlwaysOnTop();

		void setVisible(bool value);
		bool isVisible();
	};
}
