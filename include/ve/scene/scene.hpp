#pragma once

#include "ve/object.hpp"
#include "ve/scene/game_object.hpp"
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <filesystem>

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::Scene::Components {
	class ACamera;
}

namespace VoidEngine::Scene {
	class Scene final : public Object, public std::enable_shared_from_this<Scene> {
		std::map<std::string, std::shared_ptr<GameObject>> objects = {};

		std::shared_ptr<GameObject> currentCamera = nullptr;
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		static std::shared_ptr<Scene> create();
		static std::shared_ptr<Scene> loadFrom(std::filesystem::path);

		std::shared_ptr<GameObject> getObject(std::string name);
		void addObject(std::shared_ptr<GameObject> obj);

		std::shared_ptr<GameObject> getObjectFromPath(std::string path);

		std::vector<std::shared_ptr<GameObject>> getObjects();

		void setCamera(std::shared_ptr<GameObject>);
		std::shared_ptr<GameObject> getCamera();

		void draw(double delta, std::shared_ptr<IO::Window> window);
	};
}
