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
	using namespace std;
	class Scene final : public enable_shared_from_this<Scene> {
		map<string, shared_ptr<GameObject>> objects = {};

		std::shared_ptr<GameObject> currentCamera = nullptr;
	public:
		std::shared_ptr<GameObject> getObject(string name);
		void setObject(string name, std::shared_ptr<GameObject> obj);

		vector<shared_ptr<GameObject>> getObjects();

		void setCamera(std::shared_ptr<GameObject>);
		std::shared_ptr<GameObject> getCamera();

		void draw(double delta, std::shared_ptr<IO::Window> window);
	};
}
