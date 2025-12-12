#pragma once

#include "io/window.hpp"
#include "structs/rect2i.hpp"
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
	public:
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		~Engine();

		static std::shared_ptr<Engine> getInstance();

		std::shared_ptr<IO::Window> getMainWindow();
		void pollEvents();

		std::vector<Structs::Rect2i> getMonitorAreas();
		glm::ivec2 getWorkspaceArea();
		std::vector<Structs::Rect2i> getWorkspaceChunked();
		std::vector<Structs::Rect2i> getWorkspaceDeadzones();
	};
}
