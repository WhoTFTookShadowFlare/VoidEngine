#include "ve/engine.hpp"
#include "ve/engine_events.hpp"
#include "ve/io/window.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/math/rect2.hpp"
#include "ve/scene/component_updater.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#include <csignal>
#include <cstdint>
#include <filesystem>
#include <format>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
#include <memory>
#include <SDL3/SDL.h>
#include <vector>

#ifdef __unix
#include <unistd.h>
#include <pwd.h>
#endif // __unix

#ifdef _WIN64
#include <Windows.h>
#endif // _WIN64

namespace VoidEngine {
	std::shared_ptr<Engine> Engine::instance = nullptr;

	static void sigHandler(int signal) {
		switch (signal) {
		case SIGINT:
		case SIGTERM: {
			Events::QuitEvent event;
			std::shared_ptr<Engine> engine = Engine::getInstance();
			engine->onQuit.postEvent(event);
			}; break;
		}
	}

	Engine::~Engine() {
		SDL_Quit();
	}

	void Engine::initialize(int argc, char** argv) {
		instance = std::shared_ptr<Engine>(new Engine());
		instance->argc = argc;
		instance->argv = argv;

#ifdef __linux__
		setenv("SDL_VIDEODRIVER", "x11", 1);
#endif // __linux__

		SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");

		SDL_Init(SDL_INIT_VIDEO);

		signal(SIGINT, sigHandler);
		signal(SIGTERM, sigHandler);
		IO::Window::CreationOptions options{};
		instance->mainWindow = IO::Window::create(options);

		instance->renderer = IO::GFX::Renderer::getInstance();

		Scene::ComponentUpdater::ensureSetup();
	}

	std::shared_ptr<Engine> Engine::getInstance() {
		if(!instance) throw std::runtime_error("Engine is not initialized");
		return instance;
	}
	
	std::shared_ptr<IO::Window> Engine::getMainWindow() const {
		return mainWindow;
	}

	double Engine::getDelta() const {
		return delta;
	}
	
	std::filesystem::path Engine::getExecutablePath() {
#ifdef _WIN64
		char exePath[MAX_PATH];
		GetModuleFileNameA(nullptr, exePath, MAX_PATH);
		return std::filesystem::path(exePath);
#endif // _WIN64
#ifdef __unix
		return std::filesystem::canonical("/proc/self/exe");
#endif // __unix
	}

	void Engine::setDataDirectorySubdir(std::filesystem::path dataSubdir) {
		this->dataSubdir = dataSubdir;
	}

	std::filesystem::path Engine::getDataDirectory() {
#ifdef _WIN64
		return std::filesystem::path(getenv("USERPROFILE")) / "Appdata/Roaming" / dataSubdir;
#endif // _WIN64
#ifdef __linux
		std::filesystem::path homeDir = getpwuid(getuid())->pw_dir;
		return homeDir / ".local/share" / dataSubdir;
#endif // __linux
#if defined (__unix) and not defined (__linux)
		std::filesystem::path homeDir = getpwuid(getuid())->pw_dir;
		return homeDir / "Library/Application Support" / dataSubdir;
#endif //  defined (__unix) and not defined (__linux)
	}

	void Engine::pollEvents() {
		uint64_t time = SDL_GetTicks();
		delta = (double) (time - lastTime) * 1000.0 / (double) SDL_GetPerformanceFrequency();
		lastTime = time;

		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_DISPLAY_ORIENTATION:
				case SDL_EVENT_DISPLAY_REMOVED:
				case SDL_EVENT_DISPLAY_MOVED:
				case SDL_EVENT_DISPLAY_ADDED: {
					Events::ScreenLayoutChangedEvent event;
					onScreenLayoutChanged.postEvent(event);
					}; break;
				// case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
				// 	IO::Window* window = IO::Window::windowMap[event.window.windowID];
				// 	if(!window) continue;
				// 	IO::Events::WindowCloseRequested closeRequest;
				// 	window->onCloseRequested.postEvent(closeRequest);
				// 	} break;
				// case SDL_EVENT_MOUSE_MOTION: {
				// 	IO::Window* window = IO::Window::windowMap[event.motion.windowID];
				// 	if(!window) continue;
				// 	IO::Events::MouseMoved motion(window, { event.motion.x, event.motion.y }, { event.motion.xrel, event.motion.yrel });
				// 	window->onMouseMotion.postEvent(motion);
				// 	} break;
				// case SDL_EVENT_MOUSE_BUTTON_DOWN: {
				// 	IO::Window* window = IO::Window::windowMap[event.button.windowID];
				// 	if(!window) continue;
				// 	IO::Events::MouseButtonPressed pressed(window, event.button.clicks, event.button.button, true);
				// 	window->onMouseButtonPressed.postEvent(pressed);
				// 	}; break;
				// case SDL_EVENT_MOUSE_BUTTON_UP: {
				// 	IO::Window* window = IO::Window::windowMap[event.button.windowID];
				// 	if(!window) continue;
				// 	IO::Events::MouseButtonPressed pressed(window, event.button.clicks, event.button.button, false);
				// 	window->onMouseButtonReleased.postEvent(pressed);
				// 	}; break;
			}
		}
	}

	std::vector<Math::Rect2i> Engine::getMonitorAreas() {
		std::vector<Math::Rect2i> areas;

		int count = 0;
		SDL_DisplayID* displays = SDL_GetDisplays(&count);
		for(int idx = 0; idx < count; idx++) {
			SDL_Rect rect;
			SDL_GetDisplayBounds(displays[idx], &rect);
			areas.push_back({{ rect.x, rect.y }, { rect.w, rect.h }});
		}

		return areas;
	}

	glm::ivec2 Engine::getWorkspaceArea() {
		glm::ivec2 area = { 0, 0 };

		for(const auto& monArea : getMonitorAreas()) {
			if(area.x < monArea.getEndPosition().x) area.x = monArea.getEndPosition().x;
			if(area.y < monArea.getEndPosition().y) area.y = monArea.getEndPosition().y;
		}

		return area;
	}

	std::vector<Math::Rect2i> Engine::getWorkspaceChunked() {
		glm::ivec2 workspaceArea = getWorkspaceArea();
		std::vector<Math::Rect2i> areaRects = getMonitorAreas();

		std::vector<int> interiorVerticesX, interiorVerticesY;
		for(const Math::Rect2i& area : areaRects) {
			std::array<glm::ivec2, 4> vertices = area.getRectVertices();
			for(const glm::ivec2 vertex : vertices) {
				if((vertex.x == 0 || vertex.x == workspaceArea.x) || (vertex.y == 0 || vertex.y == workspaceArea.y)) continue;
				if(!std::count(interiorVerticesX.begin(), interiorVerticesX.end(), vertex.x)) interiorVerticesX.push_back(vertex.x);
				if(!std::count(interiorVerticesY.begin(), interiorVerticesY.end(), vertex.y)) interiorVerticesY.push_back(vertex.y);
			}
		}

		std::vector<Math::Rect2i> workspaceRects = {{ { 0, 0 }, workspaceArea }};

		for(const auto& yPoint : interiorVerticesY) {
			std::vector<Math::Rect2i> splits;
			for(const auto& rect : workspaceRects) {
				auto rectSplits = rect.splitHorizontally(yPoint);
				for(const auto& rectSplit : rectSplits) {
					if(!(rectSplit.size.x && rectSplit.size.y)) continue;;
					splits.push_back(rectSplit);
				}
			}
			workspaceRects = splits;
		}

		for(const auto& xPoint : interiorVerticesX) {
			std::vector<Math::Rect2i> splits;
			for(const auto& rect : workspaceRects) {
				auto rectSplits = rect.splitVertically(xPoint);
				for(const auto& rectSplit : rectSplits) {
					if(!(rectSplit.size.x && rectSplit.size.y)) continue;;
					splits.push_back(rectSplit);
				}
			}
			workspaceRects = splits;
		}
		
		return workspaceRects;
	}

	std::vector<Math::Rect2i> Engine::getWorkspaceDeadzones() {
		std::vector<Math::Rect2i> 
			chunks = getWorkspaceChunked(),
			monitorAreas = getMonitorAreas();

		for(int idx = chunks.size() - 1; idx >= 0; idx--) {
			bool hitsMonitor = false;
			for(const auto& monArea : monitorAreas) {
				if(monArea.containsPoint(chunks[idx].getCenter())) {
					hitsMonitor = true;
					break;
				}
			}
			if(hitsMonitor) chunks.erase(chunks.begin() + idx);
		}

		return chunks;
	}

	std::vector<Math::Rect2i> Engine::getWorkspaceCaves() {
		std::vector<Math::Rect2i> deadzones = getWorkspaceDeadzones(),
			chunks = getWorkspaceChunked(),
			caves;

		for(const auto& chunk : chunks) {
			for(const auto& zone : deadzones) {
				if(chunk.containsPoint({ zone.getHorizontalCenter(), zone.position.y + zone.size.y + 1 })) {
					caves.push_back(chunk);
				}
			}
		}

		assert(caves.size() <= deadzones.size());

		return caves;
	}

	std::vector<Math::Rect2i> Engine::getWorkspacePlateaus() {
		std::vector<Math::Rect2i> deadzones = getWorkspaceDeadzones(),
			chunks = getWorkspaceChunked(),
			plateaus;

		for(const auto& chunk : chunks) {
			for(const auto& zone : deadzones) {
				if(chunk.containsPoint({ zone.getHorizontalCenter(), zone.position.y - 1 })) {
					plateaus.push_back(chunk);
				}
			}
		}

		assert(plateaus.size() <= deadzones.size());

		return plateaus;
	}
}

