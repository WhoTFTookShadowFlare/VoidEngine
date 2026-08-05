#include "ve/class_db.hpp"

#include "ve/engine_events.hpp"
#include "ve/event/event.hpp"
#include "ve/io/res_providers/mesh/a_provider.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include "ve/io/window_events.hpp"
#include "ve/object.hpp"
#include "ve/scene/components/light.hpp"
#include "ve/scene/components/mesh.hpp"
#include "ve/scene/components/sound.hpp"
#include "ve/scene/components/camera.hpp"
#include "ve/scene/object_component.hpp"
#include "ve/scene/scene.hpp"
#include "ve/script/a_script_object.hpp"

namespace VoidEngine {
	std::shared_ptr<ClassDB> ClassDB::instance = nullptr;

	void ClassDB::freezeClassList() {
		classListFrozen = true;
	}

	ClassDB::ClassDB() {
		registerClass(&Object::ClassData);

		registerClass(&Scripts::AScriptObject::ClassData);

		registerClass(&Event::AEvent::ClassData);

		registerClass(&IO::ResourceProviders::EMeshProviderChanged::ClassData);
		registerClass(&IO::ResourceProviders::ETextureChanged::ClassData);

		registerClass(&Events::EQuitEvent::ClassData);
		registerClass(&Events::EScreenLayoutChangedEvent::ClassData);

		registerClass(&IO::Events::BasicWindowEvent::ClassData);
		registerClass(&IO::Events::EWindowMinimized::ClassData);
		registerClass(&IO::Events::EWindowRestored::ClassData);
		registerClass(&IO::Events::EWindowMaximized::ClassData);
		registerClass(&IO::Events::EWindowCloseRequested::ClassData);
		registerClass(&IO::Events::EWindowSizeChanged::ClassData);
		registerClass(&IO::Events::EWindowRepositioned::ClassData);
		registerClass(&IO::Events::EMouseEnter::ClassData);
		registerClass(&IO::Events::EWindowFocus::ClassData);

		registerClass(&Scene::Events::EComponentUpdate::ClassData);
		registerClass(&Scene::Events::ESceneDraw::ClassData);
		registerClass(&Scene::Events::EComponentDraw::ClassData);
		registerClass(&Scene::Events::EAddedToScene::ClassData);
		registerClass(&Scene::Events::ERemovedFromScene::ClassData);
		registerClass(&Scene::Events::EComponentAddedToObject::ClassData);
		registerClass(&Scene::Events::EComponentRemovedFromObject::ClassData);
		registerClass(&Scene::Events::EChildAdded::ClassData);
		registerClass(&Scene::Events::EChildRemoved::ClassData);

		registerClass(&IO::Events::WindowCloseRequestedDefaultHandler::ClassData);

		registerClass(&Scene::Scene::ClassData);
		registerClass(&Scene::GameObject::ClassData);

		registerClass(&Scene::AObjectComponent::ClassData);

		registerClass(&Scene::Components::LightComponent::ClassData);
		registerClass(&Scene::Components::PointLightComponent::ClassData);
		registerClass(&Scene::Components::SpotLightComponent::ClassData);
		registerClass(&Scene::Components::MeshComponent::ClassData);

		registerClass(&Scene::Components::SoundComponent::ClassData);

		registerClass(&Scene::Components::ACamera::ClassData);
		registerClass(&Scene::Components::OrthoCamera::ClassData);
		registerClass(&Scene::Components::PerspectiveCamera::ClassData);
	}

	std::shared_ptr<ClassDB> ClassDB::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<ClassDB>(new ClassDB);
		return instance;
	}

	const Class* ClassDB::getClassByName(std::string name) {
		return componentClasses[name];
	}

	void ClassDB::registerClass(const Class* cls) {
		if(componentClasses[cls->name] != nullptr) [[unlikely]] {
			std::println("[ERR] Duplicate class name {}", cls->name);
			return;
		}

		if(cls->super == nullptr && cls != &Object::ClassData) [[unlikely]] {
			std::println("[WARN] {} did not setup ClassData::super", cls->getName());
		}

		componentClasses[cls->name] = cls;
	}
}
