#include "ve/engine.hpp"
#include "ve/engine_events.hpp"
#include "ve/io/window.hpp"
#include "ve/io/window_event.hpp"
#include "ve/math/rect2.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <csignal>
#include <cstdint>
#include <glm/ext/vector_int2.hpp>
#include <memory>

#include <SDL3/SDL.h>
#include <vector>

namespace VoidEngine {
	Engine* Engine::instance;

	void sigHandler(int signal) {
		switch (signal) {
		case SIGINT:
		case SIGTERM: {
			Events::QuitEvent event;
			Engine* engine = Engine::getInstance();
			engine->onQuit.postEvent(event);
			}; break;
		}
	}

	Engine::Engine() {
#ifdef __linux__
		setenv("SDL_VIDEODRIVER", "x11", 1);
#endif // __linux__

		SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");

		SDL_Init(SDL_INIT_VIDEO);

		signal(SIGINT, sigHandler);
		signal(SIGTERM, sigHandler);

		IO::Window::CreationOptions mainWindowOptions = {	};
		mainWindow = std::make_shared<IO::Window>(mainWindowOptions);
	}

	Engine::~Engine() {
		SDL_Quit();
	}

	Engine* Engine::getInstance() {
		if(!instance) instance = new Engine();
		return instance;
	}
	
	double Engine::getDelta() const {
		return delta;
	}

	std::shared_ptr<IO::Window> Engine::getMainWindow() {
		return mainWindow;
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
				case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
					IO::Window* window = IO::Window::windowMap[event.window.windowID];
					if(!window) continue;
					IO::Events::WindowCloseRequested closeRequest;
					window->onCloseRequested.postEvent(closeRequest);
					} break;
				case SDL_EVENT_MOUSE_MOTION: {
					IO::Window* window = IO::Window::windowMap[event.motion.windowID];
					if(!window) continue;
					IO::Events::MouseMoved motion(window, { event.motion.x, event.motion.y }, { event.motion.xrel, event.motion.yrel });
					window->onMouseMotion.postEvent(motion);
					} break;
				case SDL_EVENT_MOUSE_BUTTON_DOWN: {
					IO::Window* window = IO::Window::windowMap[event.button.windowID];
					if(!window) continue;
					IO::Events::MouseButtonPressed pressed(window, event.button.clicks, event.button.button, true);
					window->onMouseButtonPressed.postEvent(pressed);
					}; break;
				case SDL_EVENT_MOUSE_BUTTON_UP: {
					IO::Window* window = IO::Window::windowMap[event.button.windowID];
					if(!window) continue;
					IO::Events::MouseButtonPressed pressed(window, event.button.clicks, event.button.button, false);
					window->onMouseButtonReleased.postEvent(pressed);
					}; break;
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
			caves = std::vector<Math::Rect2i>(deadzones.size());

		for(const auto& chunk : chunks) {
			for(const auto& zone : deadzones) {
				if(chunk.containsPoint({ zone.getHorizontalCenter(), zone.position.y + zone.size.y + 1 })) {
					caves.push_back(chunk);
				}
			}
		}

		return caves;
	}

	std::vector<Math::Rect2i> Engine::getWorkspacePlateaus() {
		std::vector<Math::Rect2i> deadzones = getWorkspaceDeadzones(),
			chunks = getWorkspaceChunked(),
			plateaus = std::vector<Math::Rect2i>(deadzones.size());

		for(const auto& chunk : chunks) {
			for(const auto& zone : deadzones) {
				if(chunk.containsPoint({ zone.getHorizontalCenter(), zone.position.y - 1 })) {
					plateaus.push_back(chunk);
				}
			}
		}

		return plateaus;
	}
}

