#pragma once

#include "ve/engine_events.hpp"
#include "ve/event/event_bus.hpp"
#include "ve/io/window.hpp"
#include "ve/math/rect2.hpp"
#include <glm/ext/vector_float2.hpp>
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
		static Engine* instance;

		uint64_t lastTime;
		double delta;
	public:
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		~Engine();

		Event::EventBus<Events::QuitEvent> onQuit;
		Event::EventBus<Events::ScreenLayoutChangedEvent> onScreenLayoutChanged;

		[[nodiscard]] static Engine* getInstance();

		[[nodiscard]] double getDelta() const;

		[[nodiscard]] std::shared_ptr<IO::Window> getMainWindow();
		void pollEvents();

		[[nodiscard]] std::vector<Math::Rect2i> getMonitorAreas();
		[[nodiscard]] glm::ivec2 getWorkspaceArea();
		[[nodiscard]] std::vector<Math::Rect2i> getWorkspaceChunked();
		[[nodiscard]] std::vector<Math::Rect2i> getWorkspaceDeadzones();
		[[nodiscard]] std::vector<Math::Rect2i> getWorkspaceCaves();
		[[nodiscard]] std::vector<Math::Rect2i> getWorkspacePlateaus();
	};
}
