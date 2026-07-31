#pragma once

#include "ve/event/event.hpp"
#include "ve/io/gfx/render_frame.hpp"
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
	private:
		EComponentUpdate(double delta) : delta(delta) {}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const double delta;
	};

	class ESceneDraw final : public Event::AEvent {
		friend class VoidEngine::Scene::Scene;
	private:
		ESceneDraw(double delta, std::shared_ptr<IO::GFX::RenderFrame> frame, std::shared_ptr<Scene> scene)
			: delta(delta), frame(frame), scene(scene)
		{}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const double delta;
		const std::shared_ptr<IO::GFX::RenderFrame> frame;
		const std::shared_ptr<Scene> scene;
	};

	class EComponentDraw final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
	private:
		EComponentDraw(ESceneDraw& sceneDraw, std::shared_ptr<GameObject> object)
			: delta(sceneDraw.delta), frame(sceneDraw.frame), scene(sceneDraw.scene), object(object)
		{}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const double delta;
		const std::shared_ptr<IO::GFX::RenderFrame> frame;
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<GameObject> object;
	};

	class EAddedToScene final : public Event::AEvent {
		friend class VoidEngine::Scene::Scene;
	private:
		EAddedToScene(std::shared_ptr<Scene> scene, std::shared_ptr<GameObject> object)
			: scene(scene), object(object)
		{}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<GameObject> object;
	};

	class ERemovedFromScene final : public Event::AEvent {
		friend class VoidEngine::Scene::Scene;
	private:
		ERemovedFromScene(std::shared_ptr<Scene> scene, std::shared_ptr<GameObject> object)
			: scene(scene), object(object)
		{}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<GameObject> object;
	};

	class EComponentAddedToObject final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
	private:
		EComponentAddedToObject(std::shared_ptr<GameObject> object, std::shared_ptr<AObjectComponent> component)
			: object(object), component(component)
		{}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const std::shared_ptr<GameObject> object;
		const std::shared_ptr<AObjectComponent> component;
	};

	class EComponentRemovedFromObject final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
	private:
		EComponentRemovedFromObject(std::shared_ptr<GameObject> object, std::shared_ptr<AObjectComponent> component)
			: object(object), component(component)
		{}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const std::shared_ptr<GameObject> object;
		const std::shared_ptr<AObjectComponent> component;
	};

	class EChildAdded final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
	private:
		EChildAdded(std::shared_ptr<GameObject> parent, std::shared_ptr<GameObject> child)
			: parent(parent), child(child)
		{}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const std::shared_ptr<GameObject> parent;
		const std::shared_ptr<GameObject> child;
	};

	class EChildRemoved final : public Event::AEvent {
		friend class VoidEngine::Scene::GameObject;
	private:
		EChildRemoved(std::shared_ptr<GameObject> parent, std::shared_ptr<GameObject> child)
			: parent(parent), child(child)
		{}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const std::shared_ptr<GameObject> parent;
		const std::shared_ptr<GameObject> child;
	};
}
