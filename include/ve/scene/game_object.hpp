#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "ve/object.hpp"
#include "ve/scene/object_component.hpp"

#include <memory>
#include <string>
#include <vector>
#include <map>

#include <glm/ext/vector_float3.hpp>

#include "ve/event/event_bus.hpp"
#include "ve/scene/events.hpp"

#include "ve/class_db.hpp"
#include "ve/variant.hpp"

namespace VoidEngine::Scene {
	class GameObject final : public Object, public std::enable_shared_from_this<GameObject> {
		std::map<const Class*, std::shared_ptr<AObjectComponent>> components;

		std::map<std::string, std::shared_ptr<GameObject>> children;
		std::weak_ptr<GameObject> parent;

		GameObject(std::string name);

		const std::string name;

		glm::vec3
			position = { 0.0f, 0.0f, 0.0f },
			rotation = { 0.0f, 0.0f, 0.0f },
			scale = { 1.0f, 1.0f, 1.0f };

	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		static std::shared_ptr<GameObject> create(std::string name);

		std::string getName() const;

		glm::mat4 getModelMatrix();

		std::vector<std::shared_ptr<GameObject>> getChildren();
		std::vector<std::shared_ptr<AObjectComponent>> getComponents();

		void addChild(std::shared_ptr<GameObject> child);
		void removeChild(std::string name);
		std::shared_ptr<GameObject> getChild(std::string name);
		std::shared_ptr<GameObject> getChildFromPath(std::string path);

		void addComponent(std::shared_ptr<AObjectComponent> component);
		void removeComponent(std::shared_ptr<AObjectComponent> component);

		Event::EventBus<Events::EAddedToScene> onAddedToScene;
		Event::EventBus<Events::ERemovedFromScene> onRemovedFromScene;

		Event::EventBus<Events::EComponentAddedToObject> onComponentAdded;
		Event::EventBus<Events::EComponentRemovedFromObject> onComponentRemoved;

		Event::EventBus<Events::EChildAdded> onChildAdded;
		Event::EventBus<Events::EChildRemoved> onChildRemoved;

		void draw(Events::ESceneDraw& draw);

		std::shared_ptr<AObjectComponent> getComponent(const Class* cls);
		std::shared_ptr<AObjectComponent> getFirstOfType(const Class* cls);
		std::vector<std::shared_ptr<AObjectComponent>> gatherComponentsOfType(const Class* cls);

		void setPosition(Variant);
		void setRotation(Variant);
		void setScale(Variant);

		Variant getPosition() const;
		Variant getRotation() const;
		Variant getScale() const;
	};
}
