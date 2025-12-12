#include "engine.hpp"
#include "io/window.hpp"
#include "io/window_event.hpp"
#include "structs/rect2i.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_video.h>
#include <algorithm>
#include <array>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
#include <memory>

#include <SDL3/SDL.h>
#include <vector>

namespace VoidEngine {
	std::shared_ptr<Engine> Engine::instance;

	Engine::Engine() {
#ifdef __linux__
		setenv("SDL_VIDEODRIVER", "x11", 1);
#endif // __linux__

		SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");

		SDL_Init(SDL_INIT_VIDEO);

		IO::Window::CreationOptions mainWindowOptions = {	};
		mainWindow = IO::Window::create(mainWindowOptions);
	}

	Engine::~Engine() {
		SDL_Quit();
	}

	std::shared_ptr<Engine> Engine::getInstance() {
		instance = std::shared_ptr<Engine>(new Engine());
		return instance;
	}

	std::shared_ptr<IO::Window> Engine::getMainWindow() {
		return mainWindow;
	}

	void Engine::pollEvents() {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
					IO::Window* window = IO::Window::windowMap[event.window.windowID];
					IO::Events::WindowCloseRequested closeRequest;
					window->onCloseRequested.postEvent(closeRequest);
					} break;
				case SDL_EVENT_MOUSE_MOTION: {
					IO::Window* window = IO::Window::windowMap[event.motion.windowID];
					IO::Events::MouseMoved motion(window, { event.motion.x, event.motion.y }, { event.motion.xrel, event.motion.yrel });
					window->onMouseMotion.postEvent(motion);
					} break;
			}
		}
	}

	std::vector<Structs::Rect2i> Engine::getMonitorAreas() {
		std::vector<Structs::Rect2i> areas;

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

	std::vector<Structs::Rect2i> Engine::getWorkspaceChunked() {
		glm::ivec2 workspaceArea = getWorkspaceArea();
		std::vector<Structs::Rect2i> areaRects = getMonitorAreas();

		std::vector<int> interiorVerticesX, interiorVerticesY;
		for(const Structs::Rect2i& area : areaRects) {
			std::array<glm::ivec2, 4> vertices = area.getRectVertices();
			for(const glm::ivec2 vertex : vertices) {
				if((vertex.x == 0 || vertex.x == workspaceArea.x) || (vertex.y == 0 || vertex.y == workspaceArea.y)) continue;
				if(!std::count(interiorVerticesX.begin(), interiorVerticesX.end(), vertex.x)) interiorVerticesX.push_back(vertex.x);
				if(!std::count(interiorVerticesY.begin(), interiorVerticesY.end(), vertex.y)) interiorVerticesY.push_back(vertex.y);
			}
		}

		std::vector<Structs::Rect2i> workspaceRects = {{ { 0, 0 }, workspaceArea }};

		for(const auto& yPoint : interiorVerticesY) {
			std::vector<Structs::Rect2i> splits;
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
			std::vector<Structs::Rect2i> splits;
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

	std::vector<Structs::Rect2i> Engine::getWorkspaceDeadzones() {
		std::vector<Structs::Rect2i> 
			chunks = getWorkspaceChunked(),
			monitorAreas = getMonitorAreas();

		for(int idx = chunks.size() - 1; idx >= 0; idx--) {
			bool hitsMonitor = false;
			for(const auto& monArea : monitorAreas) {
				if(monArea.collidesWith(chunks[idx])) {
					hitsMonitor = true;
					break;
				}
			}
			if(hitsMonitor) chunks.erase(chunks.begin() + idx);
		}

		return chunks;
	}
}

