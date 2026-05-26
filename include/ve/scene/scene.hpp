#pragma once

#include "ve/scene/game_object.hpp"
#include <memory>
#include <map>
#include <vector>
#include <string>

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::Scene::Components {
	class ACamera;
}

namespace VoidEngine::Scene {
	class Scene final : public std::enable_shared_from_this<Scene> {
		std::map<std::string, std::shared_ptr<GameObject>> objects = {};

		std::shared_ptr<GameObject> currentCamera = nullptr;
	public:
		std::shared_ptr<GameObject> getObject(std::string name);
		void addObject(std::shared_ptr<GameObject> obj);

		std::vector<std::shared_ptr<GameObject>> getObjects();

		void setCamera(std::shared_ptr<GameObject>);
		std::shared_ptr<GameObject> getCamera();

		void draw(double delta, std::shared_ptr<IO::Window> window);
	};
}
