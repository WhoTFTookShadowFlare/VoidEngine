#pragma once

#include <ve/object.hpp>
#include <ve/scene/events.hpp>
#include <ve/event/event_bus.hpp>

namespace VoidEngine::Scene {
	class Scene;

	class GameObject final : public Object, public std::enable_shared_from_this<GameObject> {
		friend class Scene;
		VE_CLASS(GameObject);
	private:
		GameObject();

		std::string name = "GameObject";

		std::weak_ptr<Scene> scene;
		std::weak_ptr<GameObject> parent;

		std::map<std::string, std::shared_ptr<GameObject>> children;

		void handleOnRename(std::shared_ptr<Object> evt);
		void handleOnChildAdded(std::shared_ptr<Object> evt);
		void handleOnParented(std::shared_ptr<Object> evt);
		void handleOnAddedToScene(std::shared_ptr<Object> evt);
		void handleOnRemovedFromScene(std::shared_ptr<Object> evt);

	public:
		~GameObject();
		static std::shared_ptr<GameObject> create();

		Event::EventBus onRename = &EObjectRenamed::ClassData;
		Event::EventBus onChildAdded = &EChildAdded::ClassData;
		Event::EventBus onParented = &EParented::ClassData;
		Event::EventBus onChildRemoved = &EChildRemoved::ClassData;
		Event::EventBus onAddedToScene = &EAddedToScene::ClassData;
		Event::EventBus onRemovedFromScene = &ERemovedFromScene::ClassData;
		
		std::string getName() const;
		void setName(std::string);

		std::shared_ptr<Scene> getScene() const;

		std::shared_ptr<GameObject> getChild(std::string);
		void addChild(std::shared_ptr<GameObject>);
		void removeChild(std::string name);
	};
}
