#pragma once

#include "ve/engine_events.hpp"
#include "ve/event/event_bus.hpp"
#include "ve/io/window.hpp"
#include "ve/structs/rect2i.hpp"
#include <glm/ext/vector_int2.hpp>
#include <memory>
#include <vector>

namespace VoidEngine {
	namespace IO {
		class Window;
	}

	class Engine {
		friend class IO::Window;
		Engine();
	
		std::shared_ptr<IO::Window> mainWindow = std::shared_ptr<IO::Window>(nullptr);
		static std::shared_ptr<Engine> instance;

		uint64_t lastTime;
		double delta;
	public:
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		~Engine();

		Event::EventBus<Events::QuitEvent> onQuit;
		Event::EventBus<Events::ScreenLayoutChangedEvent> onScreenLayoutChanged;

		static std::shared_ptr<Engine> getInstance();

		double getDelta() const;

		std::shared_ptr<IO::Window> getMainWindow();
		void pollEvents();

		std::vector<Structs::Rect2i> getMonitorAreas();
		glm::ivec2 getWorkspaceArea();
		std::vector<Structs::Rect2i> getWorkspaceChunked();
		std::vector<Structs::Rect2i> getWorkspaceDeadzones();
	};
}
