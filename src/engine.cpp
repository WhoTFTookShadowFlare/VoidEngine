#include "ve/engine.hpp"
#include "ve/engine_events.hpp"
#include "ve/event/event_handler.hpp"
#include "ve/io/window.hpp"
#include "ve/io/window_events.hpp"
#include "ve/io/input.hpp"
#include "ve/io/input_events.hpp"
#include "ve/io/sfx/audio.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/math/rect2.hpp"
#include "ve/class_db.hpp"
#include "ve/scene/component_updater.hpp"
#include "ve/script/script_engines.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#include <csignal>
#include <filesystem>
#include <glm/ext/vector_int2.hpp>
#include <memory>
#include <SDL3/SDL.h>
#include <vector>

#ifdef __unix
#include <unistd.h>
#include <pwd.h>
#endif // __unix

#if defined(_WIN64) or defined(_WIN32)
#include <Windows.h>
#endif // _WIN64 or _WIN32

namespace VoidEngine {
	std::shared_ptr<Engine> Engine::instance = nullptr;

	static void sigHandler(int signal) {
		switch (signal) {
		case SIGINT:
		case SIGTERM: {
			std::shared_ptr<Events::EQuitEvent> event = std::make_shared<Events::EQuitEvent>();
			std::shared_ptr<Engine> engine = Engine::getInstance();
			engine->onQuit.fireEvent(event);
			}; break;
		}
	}

	Engine::~Engine() {
		std::shared_ptr<Events::EQuitEvent> evt = std::make_shared<Events::EQuitEvent>();
		onQuit.fireEvent(evt);
		mainWindow = nullptr;
		renderer = nullptr;
		SDL_Quit();
	}

	void Engine::initialize(int argc, char** argv) {
		if(instance != nullptr) throw std::runtime_error("Engine is already initialized");

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
		IO::Window::CreationOptions options {
			.visible = false
		};
		
		instance->audio = IO::SFX::Audio::getInstance();
		instance->renderer = IO::GFX::Renderer::getInstance();
		instance->mainWindow = instance->renderer->createWindow(options);
		instance->input = IO::Input::getInstance();

		instance->winDefaultClose = std::make_shared<IO::Events::WindowCloseRequestedDefaultHandler>();

		Scene::ComponentUpdater::ensureSetup();
		auto compDB = ClassDB::getInstance();
	}

	std::shared_ptr<Engine> Engine::getInstance() {
		if(!instance) throw std::runtime_error("Engine is not initialized");
		return instance;
	}
	
	std::shared_ptr<IO::Window> Engine::getMainWindow() const {
		return mainWindow;
	}

	std::shared_ptr<IO::Events::WindowCloseRequestedDefaultHandler> Engine::getDefaultWindowCloseEvent() const {
		return winDefaultClose;
	}

	void Engine::setupScriptEngines() {
		ClassDB::getInstance()->freezeClassList();
		Scripts::ScriptEngines::getInstance();
	}

	double Engine::getDelta() const {
		return delta;
	}
	
	std::filesystem::path Engine::getExecutablePath() {
#if defined(_WIN64) or defined(_WIN32)
		char exePath[MAX_PATH];
		GetModuleFileNameA(nullptr, exePath, MAX_PATH);
		return std::filesystem::path(exePath);
#endif // _WIN64 or _WIN32
#ifdef __unix
		return std::filesystem::canonical("/proc/self/exe");
#endif // __unix
	}

	void Engine::setDataDirectorySubdir(std::filesystem::path dataSubdir) {
		this->dataSubdir = dataSubdir;
	}

	std::filesystem::path Engine::getDataDirectory() {
#if defined(_WIN64) or defined(_WIN32)
		return std::filesystem::path(getenv("USERPROFILE")) / "Appdata/Roaming" / dataSubdir;
#endif // _WIN64 or _WIN32
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
		std::chrono::time_point<std::chrono::steady_clock> time = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = time - lastTime;
		delta = diff.count();
		lastTime = time;

		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_DISPLAY_ORIENTATION:
				case SDL_EVENT_DISPLAY_REMOVED:
				case SDL_EVENT_DISPLAY_MOVED:
				case SDL_EVENT_DISPLAY_ADDED: {
					auto event = std::make_shared<Events::EScreenLayoutChangedEvent>();
					onScreenLayoutChanged.fireEvent(event);
					}; break;
				case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.window.windowID];
					auto winPtr = window.lock();
					if(winPtr == nullptr) continue;
					auto closeRequest = std::make_shared<IO::Events::EWindowCloseRequested>(winPtr);
					winPtr->onCloseRequested.fireEvent(closeRequest);
					} break;
				case SDL_EVENT_WINDOW_RESIZED: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.window.windowID];
					auto winPtr = window.lock();
					if(winPtr == nullptr) continue;
					auto sizeChanged = std::make_shared<IO::Events::EWindowSizeChanged>(winPtr);
					winPtr->onSizeChanged.fireEvent(sizeChanged);
					} break;
				case SDL_EVENT_WINDOW_MOVED: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.window.windowID];
					auto winPtr = window.lock();
					if(winPtr == nullptr) continue;
					auto moved = std::make_shared<IO::Events::EWindowRepositioned>(winPtr);
					winPtr->onReposition.fireEvent(moved);
					} break;
				case SDL_EVENT_WINDOW_FOCUS_GAINED:
				case SDL_EVENT_WINDOW_FOCUS_LOST: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.window.windowID];
					auto winPtr = window.lock();
					if(winPtr == nullptr) continue;
					auto focus = std::make_shared<IO::Events::EWindowFocus>(winPtr, event.type == SDL_EVENT_WINDOW_FOCUS_GAINED);
					winPtr->onFocusChanged.fireEvent(focus);
					} break;
				case SDL_EVENT_WINDOW_MOUSE_ENTER:
				case SDL_EVENT_WINDOW_MOUSE_LEAVE: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.window.windowID];
					auto winPtr = window.lock();
					if(winPtr == nullptr) continue;
					auto enter = std::make_shared<IO::Events::EMouseEnter>(winPtr, event.type == SDL_EVENT_WINDOW_MOUSE_ENTER);
					winPtr->onMouseEnter.fireEvent(enter);
					} break;
				case SDL_EVENT_WINDOW_MINIMIZED: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.window.windowID];
					auto winPtr = window.lock();
					if(winPtr == nullptr) continue;
					auto minimize = std::make_shared<IO::Events::EWindowMinimized>(winPtr);
					winPtr->onMinimize.fireEvent(minimize);
					}; break;
				case SDL_EVENT_WINDOW_MAXIMIZED: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.window.windowID];
					auto winPtr = window.lock();
					if(winPtr == nullptr) continue;
					auto maximize = std::make_shared<IO::Events::EWindowMaximized>(winPtr);
					winPtr->onMaximize.fireEvent(maximize);
					} break;
				case SDL_EVENT_WINDOW_RESTORED: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.window.windowID];
					auto winPtr = window.lock();
					if (winPtr == nullptr) continue;
					auto restored = std::make_shared<IO::Events::EWindowRestored>(winPtr);
					winPtr->onRestore.fireEvent(restored);
					} break;
				case SDL_EVENT_MOUSE_MOTION: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.motion.windowID];
					auto winPtr = window.lock();
					if(winPtr == nullptr) continue;
					auto motion = std::make_shared<IO::Events::EMouseMotion>(
						winPtr,
						glm::vec2 { event.motion.x, event.motion.y },
						glm::vec2 { event.motion.xrel, event.motion.yrel }
					);
					winPtr->onMouseMotion.fireEvent(motion);
					input->onMouseMotion.fireEvent(motion);
					} break;
				case SDL_EVENT_MOUSE_BUTTON_DOWN:
				case SDL_EVENT_MOUSE_BUTTON_UP: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.button.windowID];
					auto winPtr = window.lock();
					if(winPtr == nullptr) continue;
					auto button = std::make_shared<IO::Events::EMouseButton>(
						winPtr, event.button.which, event.button.button, event.button.down, event.button.clicks,
						glm::vec2 { event.button.x, event.button.y }
					);
					winPtr->onMouseButton.fireEvent(button);
					input->onMouseButton.fireEvent(button);
					}; break;
				case SDL_EVENT_KEY_DOWN:
				case SDL_EVENT_KEY_UP: {
					std::weak_ptr<IO::Window> window = IO::Window::WindowMap[event.key.windowID];
					auto winPtr = window.lock();
					if (winPtr == nullptr) continue;
					
					auto button = std::make_shared<IO::Events::EKeyButton>(
						winPtr, event.key.which, event.key.key,
						event.key.mod, event.key.down, event.key.repeat
					);
					winPtr->onKeyButton.fireEvent(button);
					input->onKeyButton.fireEvent(button);
					} break;
			}
		}
	}

	std::vector<Math::Rect2i> Engine::getMonitorAreas() {
		std::vector<Math::Rect2i> areas;

		int count = 0;
		SDL_DisplayID* displays = SDL_GetDisplays(&count);

		glm::ivec2 offset = { 0, 0 };

		for(int idx = 0; idx < count; idx++) {
			SDL_Rect rect;
			SDL_GetDisplayBounds(displays[idx], &rect);
			areas.push_back({{ rect.x, rect.y }, { rect.w, rect.h }});

			if(offset.x > areas.back().position.x) offset.x = areas.back().position.x;
			if(offset.y > areas.back().position.y) offset.y = areas.back().position.y;
		}

		std::for_each(areas.begin(), areas.end(), [&offset](auto& area) {
			area.position -= offset;
		});

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

	void Engine::finalize() {
		auto evt = std::make_shared<Events::EQuitEvent>();
		onQuit.fireEvent(evt);
		instance = nullptr;
	}
}
