#pragma once

#include <memory>

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::Scene {
	class Scene;
	class GameObject;
	class AObjectComponent;
	class ComponentUpdater;
}

namespace VoidEngine::Scene::Events {
	class EComponentUpdate final {
		friend class VoidEngine::Scene::ComponentUpdater;
	private:
		EComponentUpdate(double delta) : delta(delta) {}
	public:
		const double delta;
	};

	class EComponentDraw final {
		friend class VoidEngine::Scene::Scene;
	private:
		EComponentDraw(double delta, std::shared_ptr<IO::Window> window, std::shared_ptr<Scene> scene)
			: delta(delta), window(window), scene(scene)
		{}
	public:
		const double delta;
		const std::shared_ptr<IO::Window> window;
		const std::shared_ptr<Scene> scene;
	};

	class EAddedToScene final {
		friend class VoidEngine::Scene::Scene;
	private:
		EAddedToScene(std::shared_ptr<Scene> scene, std::shared_ptr<GameObject> object)
			: scene(scene), object(object)
		{}
	public:
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<GameObject> object;
	};

	class ERemovedFromScene final {
		friend class VoidEngine::Scene::Scene;
	private:
		ERemovedFromScene(std::shared_ptr<Scene> scene, std::shared_ptr<GameObject> object)
			: scene(scene), object(object)
		{}
	public:
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<GameObject> object;
	};

	class EAddedToObject final {
		friend class VoidEngine::Scene::GameObject;
	private:
		EAddedToObject(std::shared_ptr<GameObject> object, std::shared_ptr<AObjectComponent> component)
			: object(object), component(component)
		{}
	public:
		const std::shared_ptr<GameObject> object;
		const std::shared_ptr<AObjectComponent> component;
	};

	class ERemovedFromObject final {
		friend class VoidEngine::Scene::GameObject;
	private:
		ERemovedFromObject(std::shared_ptr<GameObject> object, std::shared_ptr<AObjectComponent> component)
			: object(object), component(component)
		{}
	public:
		const std::shared_ptr<GameObject> object;
		const std::shared_ptr<AObjectComponent> component;
	};
}
