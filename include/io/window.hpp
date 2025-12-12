#pragma once

#include "io/gfx/render_target.hpp"
#include "event/event_bus.hpp"
#include "event/event_listener.hpp"
#include "io/window_event.hpp"
#include <glm/ext/vector_float4.hpp>
#include <map>
#include <SDL3/SDL_video.h>
#include <memory>
#include <glm/ext/vector_int2.hpp>

namespace VoidEngine {
	class Engine;
}

namespace VoidEngine::IO {
	class Window : 
		public GFX::IRenderTarget,
		public Event::IEventListener<Events::WindowCloseRequested>
	{
	public:
		struct CreationOptions {
			bool utility = false;
			bool popup = false;
			glm::ivec2 startingSize = { 800, 600 };
			bool resizable = true;
			bool borderless = false;
			bool alwaysOnTop = false;
		};

	private:
		friend class ::VoidEngine::Engine;
		static std::map<SDL_WindowID, Window*> windowMap;
		SDL_Window* window = nullptr;
		SDL_GLContext glContext;

		glm::vec4 clearColor = { 0.1, 0.1, 0.1, 1.0 };

		bool closeRequested = false;

		Window(CreationOptions& options);
	public:
		void bindRenderTarget();
		void setClearColor(glm::vec4 color);

		void onEvent(Events::WindowCloseRequested& event);

		static std::shared_ptr<Window> create(CreationOptions& options);
		~Window();

		Event::EventBus<Events::WindowCloseRequested> onCloseRequested;
		Event::EventBus<Events::MouseMoved> onMouseMotion;

		void setWindowVisible(bool value);

		glm::ivec2 getPosition();
		glm::ivec2 getSize();

		void setPosition(glm::ivec2 position);
		void setSize(glm::ivec2 size);

		bool shouldClose();
		void swapBuffers();
	};
}
