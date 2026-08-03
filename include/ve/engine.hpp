#pragma once

#include "ve/engine_events.hpp"
#include "ve/event/event_bus.hpp"
#include "ve/math/rect2.hpp"
#include <filesystem>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <memory>
#include <vector>

namespace VoidEngine {
	namespace IO {
		class Window;
		class Input;
		namespace SFX {
			class Audio;
		}
		namespace GFX {
			class Renderer;
		}

		namespace Events {
			class WindowCloseRequestedDefaultHandler;
		}
	}

	class Engine final {
		friend class IO::Window;
		Engine() {}
	
		static std::shared_ptr<Engine> instance;
		std::shared_ptr<IO::GFX::Renderer> renderer;
		std::shared_ptr<IO::SFX::Audio> audio;
		std::shared_ptr<IO::Input> input;

		std::filesystem::path dataSubdir;
		std::chrono::time_point<std::chrono::steady_clock> lastTime = std::chrono::steady_clock::now();
		double delta = 0.0;

		int argc = 0;
		char** argv = nullptr;

		std::shared_ptr<IO::Window> mainWindow = nullptr;

		std::shared_ptr<IO::Events::WindowCloseRequestedDefaultHandler> winDefaultClose = nullptr;
	public:
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		~Engine();

		// Event::EventBusLegacy<Events::EQuitEvent> onQuit;
		// Event::EventBusLegacy<Events::EScreenLayoutChangedEvent> onScreenLayoutChanged;

		Event::EventBus onQuit = &Events::EQuitEvent::ClassData;
		Event::EventBus onScreenLayoutChanged = &Events::EScreenLayoutChangedEvent::ClassData;

		static void initialize(int argc, char** argv);
		[[nodiscard]] static std::shared_ptr<Engine> getInstance();
		[[nodiscard]] std::shared_ptr<IO::Window> getMainWindow() const;

		[[nodiscard]] std::shared_ptr<IO::Events::WindowCloseRequestedDefaultHandler> getDefaultWindowCloseEvent() const;

		void setupScriptEngines();

		[[nodiscard]] double getDelta() const;

		void pollEvents();

		[[nodiscard]] std::filesystem::path getExecutablePath();

		void setDataDirectorySubdir(std::filesystem::path subdir);
		[[nodiscard]] std::filesystem::path getDataDirectory();

		[[nodiscard]] std::vector<Math::Rect2i> getMonitorAreas();
		[[nodiscard]] glm::ivec2 getWorkspaceArea();
		[[nodiscard]] std::vector<Math::Rect2i> getWorkspaceChunked();
		[[nodiscard]] std::vector<Math::Rect2i> getWorkspaceDeadzones();
		[[nodiscard]] std::vector<Math::Rect2i> getWorkspaceCaves();
		[[nodiscard]] std::vector<Math::Rect2i> getWorkspacePlateaus();

		void finalize();
	};
}
