#include "ve/scene/game_object.hpp"
#include "ve/class_property.hpp"
#include "ve/scene/events.hpp"
#include "ve/scene/object_component.hpp"
#include <algorithm>
#include <format>
#include <memory>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <stdexcept>
#include <vector>

namespace VoidEngine::Scene {
	const Class GameObject::ClassData = {
		.name = "GameObject",
		.properties = {
			new NativeProperty<GameObject>("position", &GameObject::getPosition, &GameObject::setPosition),
			new NativeProperty<GameObject>("rotation", &GameObject::getRotation, &GameObject::setRotation),
			new NativeProperty<GameObject>("scale", &GameObject::getScale, &GameObject::setScale),
		}
	};

	GameObject::GameObject(std::string name)
		: name(name)
	{	}

	std::shared_ptr<GameObject> GameObject::create(std::string name) {
		return std::shared_ptr<GameObject>(new GameObject(name));
	}

	std::string GameObject::getName() const {
		return name;
	}

	void GameObject::addComponent(std::shared_ptr<AObjectComponent> comp) {
		if(comp == nullptr) return;
		if(components[comp->getClass()] != nullptr) return;
		
		components[comp->getClass()] = comp;
		comp->tiedTo.push_back(weak_from_this());

		auto evt = std::shared_ptr<Events::EComponentAddedToObject>(new Events::EComponentAddedToObject(shared_from_this(), comp));
		comp->onComponentAdded.fireEvent(evt);
		onComponentAdded.fireEvent(evt);
	}

	void GameObject::removeComponent(std::shared_ptr<AObjectComponent> comp) {
		auto evt = std::shared_ptr<Events::EComponentRemovedFromObject>(new Events::EComponentRemovedFromObject(shared_from_this(), comp));
		components[comp->getClass()]->onComponentRemoved.fireEvent(evt);
		onComponentRemoved.fireEvent(evt);
		components.erase(comp->getClass());
	}

	std::vector<std::shared_ptr<AObjectComponent>> GameObject::getComponents() {
		std::vector<std::shared_ptr<AObjectComponent>> compList;
		std::for_each(components.cbegin(), components.cend(), [&compList](const auto& iter) {
			compList.emplace_back(iter.second);
			});
		return compList;
	}

	glm::mat4 GameObject::getModelMatrix() const {
		glm::mat4 matrix(1.0f);

		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f });
		matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f });
		matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });
		matrix = glm::scale(matrix, scale);

		if(auto parent = this->parent.lock())
			return parent->getModelMatrix() * matrix;
		return matrix;
	}

	void GameObject::addChild(std::shared_ptr<GameObject> child) {
		if(children.contains(child->getName())) {
			throw std::runtime_error(std::format("Duplicate name on child ({})", child->getName()));
		}

		if(!child->parent.expired()) {
			throw std::runtime_error(std::format("An object cannot have multiple parents."));
		}

		child->parent = weak_from_this();

		children[child->getName()] = child;
		auto evt = std::shared_ptr<Events::EChildAdded>(new Events::EChildAdded(shared_from_this(), child));
		onChildAdded.fireEvent(evt);
	}

	void GameObject::removeChild(std::string name) {
		if(!children.contains(name)) return;

		std::shared_ptr<GameObject> child = children[name];
		children.erase(name);
		auto evt = std::shared_ptr<Events::EChildRemoved>(new Events::EChildRemoved(shared_from_this(), child));
		onChildRemoved.fireEvent(evt);
	}

	std::shared_ptr<GameObject> GameObject::getChild(std::string name) {
		if(!children.contains(name)) return nullptr;
		return children[name];
	}

	std::shared_ptr<GameObject> GameObject::getChildFromPath(std::string path) {
		size_t split = path.find_first_of('/');
		if(split == std::string::npos) {
			return getChild(path);
		}

		std::string next = path.substr(0, split), remaining = path.substr(split + 1);

		std::shared_ptr<GameObject> child = getChild(next);
		if(child == nullptr) return nullptr;
		return child->getChildFromPath(remaining);
	}

	std::vector<std::shared_ptr<GameObject>> GameObject::getChildren() {
		std::vector<std::shared_ptr<GameObject>> children;
		std::for_each(this->children.cbegin(), this->children.cend(), [&children](const auto& iter) {
			children.emplace_back(iter.second);
			});
		return children;
	}

	void GameObject::draw(Events::ESceneDraw& scnDraw) {
		auto draw = std::shared_ptr<Events::EComponentDraw>(new Events::EComponentDraw(scnDraw, shared_from_this()));
		for(auto& child : children) if(child.second != nullptr) child.second->draw(scnDraw);
		for(auto& comp : components) if(comp.second != nullptr) comp.second->onDraw.fireEvent(draw);
	}

	std::shared_ptr<AObjectComponent> GameObject::getComponent(const Class* cls) {
		return components[cls];
	}

	std::shared_ptr<AObjectComponent> GameObject::getFirstOfType(const Class* cls) {
		const auto idx = std::find_if(components.cbegin(), components.cend(), [&cls](const auto& iter) {
			return iter.first->instanceOf(cls);
			});
		if(idx == components.cend()) return nullptr;
		return idx->second;
	}


	void find_component(const Class* cls, std::shared_ptr<GameObject> object, std::vector<std::shared_ptr<AObjectComponent>>& found) {
		auto comp = object->getComponent(cls);
		if(comp != nullptr) found.push_back(comp);
		auto children = object->getChildren();
		std::for_each(children.cbegin(), children.cend(), [&](const auto& child) {
			find_component(cls, child, found);
		});
	}

	std::vector<std::shared_ptr<AObjectComponent>> GameObject::gatherComponentsOfType(const Class* cls) {
		std::vector<std::shared_ptr<AObjectComponent>> components;
		find_component(cls, shared_from_this(), components);
		return components;
	}

	void GameObject::setPosition(Variant value) {
		if(!value.isVec3()) return;
		position = value.asVec3().value();
	}

	void GameObject::setRotation(Variant value) {
		if(!value.isVec3()) return;
		rotation = value.asVec3().value();
	}

	void GameObject::setScale(Variant value) {
		if(!value.isVec3()) return;
		scale = value.asVec3().value();
	}

	Variant GameObject::getPosition() const {
		return position;
	}

	Variant GameObject::getRotation() const {
		return rotation;
	}

	Variant GameObject::getScale() const {
		return scale;
	}	
}
