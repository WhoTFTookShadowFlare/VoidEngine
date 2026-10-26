#pragma once

#include <ve/object.hpp>
#include <ve/scene/events.hpp>
#include <ve/event/event_bus.hpp>

namespace VoidEngine::Scene {
	class Scene;

	namespace Components {
		class AObjectComponent;
		class AMonoObjectComponent;
		class APolyObjectComponent;
	}

	class GameObject final : public Object, public std::enable_shared_from_this<GameObject> {
		friend class Scene;
		VE_CLASS(GameObject);
	private:
		GameObject();

		std::string name = "GameObject";

		glm::vec3 position = { 0, 0, 0 };
		glm::vec3 rotation = { 0, 0 ,0 };
		glm::vec3 scale = { 1, 1, 1 };

		std::weak_ptr<Scene> scene;
		std::weak_ptr<GameObject> parent;

		std::map<std::string, std::shared_ptr<GameObject>> children;

		std::map<const Class*, std::shared_ptr<Components::AMonoObjectComponent>> monoComponents;
		std::map<const Class*, std::shared_ptr<Components::APolyObjectComponent>> polyComponents;

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
		Event::EventBus onComponentAdded = &EComponentAdded::ClassData;
		Event::EventBus onComponentRemoved = &EComponentRemoved::ClassData;
		Event::EventBus onDraw = &EDraw::ClassData;
		
		std::string getName() const;
		void setName(std::string);

		glm::mat4 calculateModelMatrix() const;

		std::shared_ptr<Scene> getScene() const;
		std::shared_ptr<GameObject> getParent() const;

		std::shared_ptr<GameObject> getChild(std::string);
		void addChild(std::shared_ptr<GameObject>);
		void removeChild(std::string name);

		std::vector<std::shared_ptr<Components::AMonoObjectComponent>> getMonoComponents() const;
		std::vector<std::shared_ptr<Components::APolyObjectComponent>> getPolyComponents() const;

		std::shared_ptr<Components::AMonoObjectComponent> getMonoComponent(const Class* compCls);
		std::shared_ptr<Components::APolyObjectComponent> getPolyComponent(const Class* compCls);
		void addComponent(std::shared_ptr<Components::AObjectComponent>);
		void removeComponent(const Class* compCls);
	};
}
