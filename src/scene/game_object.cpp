#include <ve/scene/game_object.hpp>
#include <ve/scene/scene.hpp>

#include <ve/scene/components/a_mono_object_component.hpp>
#include <ve/scene/components/a_poly_object_component.hpp>

#include <ve/class_event_handler.hpp>

namespace VoidEngine::Scene {
	const ::VoidEngine::Class GameObject::ClassData = {
		.name = "GameObject",
		.super = &Object::ClassData,
		.eventHandlers = {
			new NativeEventHandler(&EObjectRenamed::ClassData, &GameObject::handleOnRename),
			new NativeEventHandler(&EChildAdded::ClassData, &GameObject::handleOnChildAdded),
			new NativeEventHandler(&EParented::ClassData, &GameObject::handleOnParented),
			new NativeEventHandler(&EAddedToScene::ClassData, &GameObject::handleOnAddedToScene),
			new NativeEventHandler(&ERemovedFromScene::ClassData, &GameObject::handleOnRemovedFromScene)
		},
		.constructor = new NativeConstructor(&GameObject::create),
		.flags = ClassFlags::FINAL
	};

	GameObject::GameObject() {}

	GameObject::~GameObject() {}

	std::shared_ptr<GameObject> GameObject::create() {
		auto self = std::shared_ptr<GameObject>(new GameObject);
		self->onChildAdded.addHandler(self);
		self->onAddedToScene.addHandler(self);
		self->onRemovedFromScene.addHandler(self);
		return self;
	}

	std::string GameObject::getName() const {
		return name;
	}

	void GameObject::setName(std::string value) {
		std::shared_ptr<GameObject> obj = parent.lock();
		std::shared_ptr<Scene> scn = scene.lock();

		if((obj != nullptr && obj->getChild(value) != nullptr) || (scn != nullptr && scn->getObject(value))) {
			std::println("[ERR] Failed to rename object {}, name already taken", getName());
			return;
		}

		auto oldName = name;
		name = value;
		std::shared_ptr<EObjectRenamed> evt = EObjectRenamed::create();
		evt->obj = shared_from_this();
		evt->oldName = oldName;
		onRename.fireEvent(evt);
	}

	void GameObject::handleOnRename(std::shared_ptr<Object> evtObj) {
		auto evt = std::static_pointer_cast<EObjectRenamed>(evtObj);
		
		children[evt->getObject()->getName()] = children[evt->getOldName()];
		children.erase(evt->getOldName());
	}
	
	void GameObject::handleOnChildAdded(std::shared_ptr<Object> evtObj) {
		auto evt = std::static_pointer_cast<EAddedToScene>(evtObj);

		std::shared_ptr<GameObject> obj = parent.lock();
		if(obj != nullptr) obj->onChildAdded.fireEvent(std::static_pointer_cast<Event::AEvent>(evt));
	}

	void GameObject::handleOnParented(std::shared_ptr<Object> evtObj) {
		auto evt = std::static_pointer_cast<EParented>(evtObj);

		scene = evt->getParent()->getScene();

		std::for_each(children.begin(), children.end(), [&evt](const auto& iter) {
			iter.second->onParented.fireEvent(evt);
		});
	}

	void GameObject::handleOnAddedToScene(std::shared_ptr<Object> evtObj) {
		auto evt = std::static_pointer_cast<EAddedToScene>(evtObj);
		scene = evt->getScene();
		
		std::for_each(children.begin(), children.end(), [&evt](const auto& iter) {
			iter.second->onAddedToScene.fireEvent(evt);
		});
	}

	void GameObject::handleOnRemovedFromScene(std::shared_ptr<Object> evtObj) {
		auto evt = std::static_pointer_cast<ERemovedFromScene>(evtObj);
		scene = std::weak_ptr<Scene>();

		std::for_each(children.begin(), children.end(), [&evt](const auto& iter) {
			iter.second->onRemovedFromScene.fireEvent(evt);
		});
	}

	std::shared_ptr<GameObject> GameObject::getChild(std::string name) {
		if(!children.contains(name)) return nullptr;
		return children[name];
	}

	void GameObject::addChild(std::shared_ptr<GameObject> child) {
		if(child == nullptr) {
			return;
		}

		if(!child->parent.expired()) {
			std::println("[ERR] Cannot add child to multiple objects");
			return;
		}

		if(getChild(child->getName()) != nullptr) {
			std::println("[WARN] Object with name {} already in children, adding suffix", child->getName());
			child->setName(std::format("{}{}", child->getName(), reinterpret_cast<size_t>(child.get())));
		}

		children[child->getName()] = child;
		child->onRename.addHandler(shared_from_this());

		auto childAddedEvt = EChildAdded::create();
		childAddedEvt->parent = shared_from_this();
		childAddedEvt->child = child;
		onChildAdded.fireEvent(childAddedEvt);

		auto parentedEvt = EParented::create();
		parentedEvt->parent = shared_from_this();
		parentedEvt->child = child;
		onParented.fireEvent(parentedEvt);
	}

	void GameObject::removeChild(std::string name) {
		std::shared_ptr<GameObject> child = getChild(name);
		if(child == nullptr) return;
		children.erase(name);

		auto evt = EChildRemoved::create();
		evt->child = child;
		evt->parent = shared_from_this();
		onChildRemoved.fireEvent(evt);
	}

	std::shared_ptr<Scene> GameObject::getScene() const {
		return scene.lock();
	}

	std::vector<std::shared_ptr<Components::AMonoObjectComponent>> GameObject::getMonoComponents() const {
		std::vector<std::shared_ptr<Components::AMonoObjectComponent>> comps(monoComponents.size());
		for(const auto& iter : monoComponents)
			comps.emplace_back(iter.second);
		return comps;
	}
	
	std::vector<std::shared_ptr<Components::APolyObjectComponent>> GameObject::getPolyComponents() const {
		std::vector<std::shared_ptr<Components::APolyObjectComponent>> comps(polyComponents.size());
		for(const auto& iter : polyComponents)
			comps.emplace_back(iter.second);
		return comps;
	}

	std::shared_ptr<Components::AMonoObjectComponent> GameObject::getMonoComponent(const Class* compCls) {
		if(!compCls->instanceOf(&Components::AMonoObjectComponent::ClassData)) {
			std::println("[ERR] Class {} is not an AMonoObjectComponent", compCls->getName());
			return nullptr;
		}

		if(!monoComponents.contains(compCls)) return nullptr;
		return monoComponents[compCls];
	}

	std::shared_ptr<Components::APolyObjectComponent> GameObject::getPolyComponent(const Class* compCls) {
		if(!compCls->instanceOf(&Components::AMonoObjectComponent::ClassData)) {
			std::println("[ERR] Class {} is not an APolyObjectComponent", compCls->getName());
			return nullptr;
		}

		if(!polyComponents.contains(compCls)) return nullptr;
		return polyComponents[compCls];
	}

	void GameObject::addComponent(std::shared_ptr<Components::AObjectComponent> comp) {
		if(getMonoComponent(comp->getClass()) != nullptr || getPolyComponent(comp->getClass()) != nullptr) return;

		if (comp->getClass()->instanceOf(&Components::AMonoObjectComponent::ClassData)) {
			auto mono = std::static_pointer_cast<Components::AMonoObjectComponent>(comp);
			monoComponents[comp->getClass()] = mono;
			mono->object = weak_from_this();
			return;
		}
		else if (comp->getClass()->instanceOf(&Components::APolyObjectComponent::ClassData)) {
			auto poly = std::static_pointer_cast<Components::APolyObjectComponent>(comp);
			polyComponents[comp->getClass()] = poly;
			poly->objects.emplace_back(shared_from_this());
			return;
		}
		std::println("[FATAL] Could not determine how to add component {} to a GameObject", comp->getClass()->getName());
		assert(false);
	}

	void GameObject::removeComponent(const Class* compCls) {
		if (compCls->instanceOf(&Components::AMonoObjectComponent::ClassData)) {
			auto comp = getMonoComponent(compCls);
			comp->object = std::weak_ptr<GameObject>();
			monoComponents.erase(compCls);
			return;
		}
		else if (compCls->instanceOf(&Components::APolyObjectComponent::ClassData)) {
			auto comp = getPolyComponent(compCls);
			auto self = shared_from_this();
			comp->objects.erase(std::find_if(comp->objects.cbegin(), comp->objects.cend(), [&self](const auto& iterWeak) {
				return iterWeak.lock() == self;
			}));
			polyComponents.erase(compCls);
			return;
		}
		std::println("[FATAL] Could not determine how to remove component {} from a GameObject", compCls->getName());
		assert(false);
	}
}
