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
	namespace IO::GFX::OpenGL {
		class GLWindow;
	}
	namespace IO::GFX::Dummy {
		class DummyWindow;
	}
}

namespace VoidEngine::IO {
	class Window : public GFX::IRenderTarget, public std::enable_shared_from_this<Window> {
		friend class VoidEngine::Engine;
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

		Event::EventBus onCloseRequested = &Events::EWindowCloseRequested::ClassData;
		Event::EventBus onSizeChanged = &Events::EWindowSizeChanged::ClassData;
		Event::EventBus onReposition = &Events::EWindowRepositioned::ClassData;
		Event::EventBus onFocusChanged = &Events::EWindowFocus::ClassData;
		Event::EventBus onMouseEnter = &Events::EMouseEnter::ClassData;
		Event::EventBus onMinimize = &Events::EWindowMinimized::ClassData;
		Event::EventBus onRestore = &Events::EWindowRestored::ClassData;
		Event::EventBus onMaximize = &Events::EWindowMaximized::ClassData;

		Event::EventBus onMouseMotion = &Events::EMouseMotion::ClassData;
		Event::EventBus onMouseButton = &Events::EMouseButton::ClassData;
		Event::EventBus onKeyButton = &Events::EKeyButton::ClassData;

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
