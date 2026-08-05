#pragma once

#include "ve/event/event.hpp"
#include "ve/io/gfx/render_frame.hpp"
#include "ve/object.hpp"
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
	class EComponentUpdate final : public Event::AEvent {
		friend class VoidEngine::Scene::ComponentUpdater;
		VE_CLASS(EComponentUpdate)
	private:
		EComponentUpdate(double delta) : delta(delta) {}
	public:
		const double delta;
	};

	class ESceneDraw final : public Event::AEvent {
		friend class VoidEngine::Scene::Scene;
		VE_CLASS(ESceneDraw)
	private:
		ESceneDraw(double delta, std::shared_ptr<IO::GFX::RenderFrame> frame, std::shared_ptr<Scene> scene)
			: delta(delta), frame(frame), scene(scene)
		{}
	public:
		const double delta;
		const std::shared_ptr<IO::GFX::RenderFrame> frame;
		const std::shared_ptr<Scene> scene;
	};

	class EComponentDraw final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
		VE_CLASS(EComponentDraw)
	private:
		EComponentDraw(ESceneDraw& sceneDraw, std::shared_ptr<GameObject> object)
			: delta(sceneDraw.delta), frame(sceneDraw.frame), scene(sceneDraw.scene), object(object)
		{}
	public:
		const double delta;
		const std::shared_ptr<IO::GFX::RenderFrame> frame;
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<GameObject> object;
	};

	class EAddedToScene final : public Event::AEvent {
		friend class VoidEngine::Scene::Scene;
		VE_CLASS(EAddedToScene)
	private:
		EAddedToScene(std::shared_ptr<Scene> scene, std::shared_ptr<GameObject> object)
			: scene(scene), object(object)
		{}
	public:
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<GameObject> object;
	};

	class ERemovedFromScene final : public Event::AEvent {
		friend class VoidEngine::Scene::Scene;
		VE_CLASS(ERemovedFromScene)
	private:
		ERemovedFromScene(std::shared_ptr<Scene> scene, std::shared_ptr<GameObject> object)
			: scene(scene), object(object)
		{}
	public:
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<GameObject> object;
	};

	class EComponentAddedToObject final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
		VE_CLASS(EComponentAddedToObject)
	private:
		EComponentAddedToObject(std::shared_ptr<GameObject> object, std::shared_ptr<AObjectComponent> component)
			: object(object), component(component)
		{}
	public:
		const std::shared_ptr<GameObject> object;
		const std::shared_ptr<AObjectComponent> component;
	};

	class EComponentRemovedFromObject final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
		VE_CLASS(EComponentRemovedFromObject)
	private:
		EComponentRemovedFromObject(std::shared_ptr<GameObject> object, std::shared_ptr<AObjectComponent> component)
			: object(object), component(component)
		{}
	public:
		const std::shared_ptr<GameObject> object;
		const std::shared_ptr<AObjectComponent> component;
	};

	class EChildAdded final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
		VE_CLASS(EChildAdded)
	private:
		EChildAdded(std::shared_ptr<GameObject> parent, std::shared_ptr<GameObject> child)
			: parent(parent), child(child)
		{}
	public:
		const std::shared_ptr<GameObject> parent;
		const std::shared_ptr<GameObject> child;
	};

	class EChildRemoved final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
		VE_CLASS(EChildRemoved)
	private:
		EChildRemoved(std::shared_ptr<GameObject> parent, std::shared_ptr<GameObject> child)
			: parent(parent), child(child)
		{}
	public:
		const std::shared_ptr<GameObject> parent;
		const std::shared_ptr<GameObject> child;
	};
}
