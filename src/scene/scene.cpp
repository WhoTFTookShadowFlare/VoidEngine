#include <ve/scene/scene.hpp>
#include <ve/scene/game_object.hpp>

#include <ve/class_event_handler.hpp>

#include <ve/physics2d/physics_2d.hpp>
#include <ve/scene/components/gfx/a_camera_component.hpp>

namespace VoidEngine::Scene {
	const ::VoidEngine::Class Scene::ClassData = {
		.name = "Scene",
		.super = &Object::ClassData,
		.eventHandlers = {
			new NativeEventHandler(&EObjectRenamed::ClassData, &Scene::handleObjectRenamed),
			new NativeEventHandler(&Components::GFX::ECameraValueChanged::ClassData, &Scene::handleCameraValueChanged)
		},
		.constructor = new NativeConstructor(&Scene::create),
		.flags = ClassFlags::FINAL
	};

	Scene::Scene() {
		world2d = Physics2D::Physics2D::getInstance()->createWorld();
	}

	Scene::~Scene() {}

	std::shared_ptr<Scene> Scene::create() {
		return std::shared_ptr<Scene>(new Scene);
	}

	void Scene::updateCameraValues() {
		if(renderTarget == nullptr) return;
		renderFrame->setView(currentCamera->getView());
		renderFrame->setProjection(currentCamera->getProjection(renderTarget->getSize()));
	}

	void Scene::handleObjectRenamed(std::shared_ptr<Object> evtObj) {
		std::shared_ptr<EObjectRenamed> evt = std::static_pointer_cast<EObjectRenamed>(evtObj);
		
		objects[evt->getObject()->getName()] = objects[evt->getOldName()];
		objects.erase(evt->getOldName());
	}

	void Scene::handleCameraValueChanged(std::shared_ptr<Object>) {
		updateCameraValues();
	}

	std::shared_ptr<GameObject> Scene::getObject(std::string name) {
		if(objects.contains(name)) return objects[name];
		return nullptr;
	}

	void Scene::addObject(std::shared_ptr<GameObject> obj) {
		if(getObject(obj->getName()) != nullptr) {
			std::println("[WARN] Object with name {} already in scene, adding suffix", obj->getName());
			obj->setName(std::format("{}{}", obj->getName(), reinterpret_cast<size_t>(obj.get())));
		}

		objects[obj->getName()] = obj;
		obj->onRename.addHandler(shared_from_this());

		auto evt = EAddedToScene::create();
		evt->scene = shared_from_this();
		obj->onAddedToScene.fireEvent(evt);
	}

	void Scene::removeObject(std::string name) {
		auto object = getObject(name);
		if(object == nullptr) return;
		objects.erase(name);

		auto evt = ERemovedFromScene::create();
		evt->scene = shared_from_this();
		evt->object = object;
		object->onRemovedFromScene.fireEvent(evt);
	}

	void Scene::draw(double delta) {

	}

	std::shared_ptr<IO::GFX::IRenderTarget> Scene::getRenderTarget() const {
		return renderTarget;
	}
	
	void Scene::setRenderTarget(std::shared_ptr<IO::GFX::IRenderTarget> value) {
		renderTarget = value;
		renderFrame->setTarget(value);
	}

	std::shared_ptr<IO::GFX::RenderFrame> Scene::getRenderFrame() const {
		return renderFrame;
	}

	void Scene::setCurrentCamera(std::shared_ptr<Components::GFX::ACameraComponent> camera) {
		if(currentCamera != nullptr) currentCamera->onCameraValueChanged.removeHandler(shared_from_this());
		currentCamera = camera;
		if(currentCamera != nullptr) currentCamera->onCameraValueChanged.addHandler(shared_from_this());
		updateCameraValues();
	}

	std::shared_ptr<Components::GFX::ACameraComponent> Scene::getCurrentCamera() const {
		return currentCamera;
	}
}
