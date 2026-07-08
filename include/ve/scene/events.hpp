#pragma once

#include "ve/io/gfx/render_target.hpp"
#include <cinttypes>
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

	class ESceneDraw final {
		friend class VoidEngine::Scene::Scene;
	private:
		ESceneDraw(double delta, std::shared_ptr<IO::GFX::IRenderTarget> target, std::shared_ptr<Scene> scene)
			: delta(delta), target(target), scene(scene)
		{}
	public:
		const double delta;
		const std::shared_ptr<IO::GFX::IRenderTarget> target;
		const std::shared_ptr<Scene> scene;
	};

	class EComponentDraw final {
		friend class VoidEngine::Scene::GameObject;
	private:
		EComponentDraw(ESceneDraw& sceneDraw, std::shared_ptr<GameObject> object)
			: delta(sceneDraw.delta), target(sceneDraw.target), scene(sceneDraw.scene), object(object)
		{}
	public:
		const double delta;
		const std::shared_ptr<IO::GFX::IRenderTarget> target;
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<GameObject> object;
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

	class EComponentAddedToObject final {
		friend class VoidEngine::Scene::GameObject;
	private:
		EComponentAddedToObject(std::shared_ptr<GameObject> object, std::shared_ptr<AObjectComponent> component)
			: object(object), component(component)
		{}
	public:
		const std::shared_ptr<GameObject> object;
		const std::shared_ptr<AObjectComponent> component;
	};

	class EComponentRemovedFromObject final {
		friend class VoidEngine::Scene::GameObject;
	private:
		EComponentRemovedFromObject(std::shared_ptr<GameObject> object, std::shared_ptr<AObjectComponent> component)
			: object(object), component(component)
		{}
	public:
		const std::shared_ptr<GameObject> object;
		const std::shared_ptr<AObjectComponent> component;
	};

	class EChildAdded final {
		friend class VoidEngine::Scene::GameObject;
	private:
		EChildAdded(std::shared_ptr<GameObject> parent, std::shared_ptr<GameObject> child)
			: parent(parent), child(child)
		{}
	public:
		const std::shared_ptr<GameObject> parent;
		const std::shared_ptr<GameObject> child;
	};

	class EChildRemoved final {
		friend class VoidEngine::Scene::GameObject;
	private:
		EChildRemoved(std::shared_ptr<GameObject> parent, std::shared_ptr<GameObject> child)
			: parent(parent), child(child)
		{}
	public:
		const std::shared_ptr<GameObject> parent;
		const std::shared_ptr<GameObject> child;
	};
}
