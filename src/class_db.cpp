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

namespace VoidEngine {
	std::shared_ptr<ClassDB> ClassDB::instance = nullptr;

	void ClassDB::freezeClassList() {
		classListFrozen = true;
	}

	ClassDB::ClassDB() {
		registerClass(&Event::AEvent::ClassData, &Object::ClassData);

		registerClass(&IO::ResourceProviders::EMeshProviderChanged::ClassData, &Event::AEvent::ClassData);
		registerClass(&IO::ResourceProviders::ETextureChanged::ClassData, &Event::AEvent::ClassData);

		registerClass(&Events::EQuitEvent::ClassData, &Event::AEvent::ClassData);
		registerClass(&Events::EScreenLayoutChangedEvent::ClassData, &Event::AEvent::ClassData);

		registerClass(&IO::Events::BasicWindowEvent::ClassData, &Event::AEvent::ClassData);
		registerClass(&IO::Events::EWindowMinimized::ClassData, &Event::AEvent::ClassData);
		registerClass(&IO::Events::EWindowRestored::ClassData, &Event::AEvent::ClassData);
		registerClass(&IO::Events::EWindowMaximized::ClassData, &Event::AEvent::ClassData);
		registerClass(&IO::Events::EWindowCloseRequested::ClassData, &Event::AEvent::ClassData);
		registerClass(&IO::Events::EWindowSizeChanged::ClassData, &Event::AEvent::ClassData);
		registerClass(&IO::Events::EWindowRepositioned::ClassData, &Event::AEvent::ClassData);
		registerClass(&IO::Events::EMouseEnter::ClassData, &Event::AEvent::ClassData);
		registerClass(&IO::Events::EWindowFocus::ClassData, &Event::AEvent::ClassData);

		registerClass(&Scene::Events::EComponentUpdate::ClassData, &Event::AEvent::ClassData);
		registerClass(&Scene::Events::ESceneDraw::ClassData, &Event::AEvent::ClassData);
		registerClass(&Scene::Events::EComponentDraw::ClassData, &Event::AEvent::ClassData);
		registerClass(&Scene::Events::EAddedToScene::ClassData, &Event::AEvent::ClassData);
		registerClass(&Scene::Events::ERemovedFromScene::ClassData, &Event::AEvent::ClassData);
		registerClass(&Scene::Events::EComponentAddedToObject::ClassData, &Event::AEvent::ClassData);
		registerClass(&Scene::Events::EComponentRemovedFromObject::ClassData, &Event::AEvent::ClassData);
		registerClass(&Scene::Events::EChildAdded::ClassData, &Event::AEvent::ClassData);
		registerClass(&Scene::Events::EChildRemoved::ClassData, &Event::AEvent::ClassData);

		registerClass(&Scene::Scene::ClassData, &Object::ClassData);
		registerClass(&Scene::GameObject::ClassData, &Object::ClassData);

		registerClass(&Scene::AObjectComponent::ClassData, &Object::ClassData);

		registerClass(&Scene::Components::LightComponent::ClassData, &Scene::AObjectComponent::ClassData);
		registerClass(&Scene::Components::PointLightComponent::ClassData, &Scene::Components::LightComponent::ClassData);
		registerClass(&Scene::Components::SpotLightComponent::ClassData, &Scene::Components::LightComponent::ClassData);
		registerClass(&Scene::Components::MeshComponent::ClassData, &Scene::AObjectComponent::ClassData);

		registerClass(&Scene::Components::SoundComponent::ClassData, &Scene::AObjectComponent::ClassData);

		registerClass(&Scene::Components::ACamera::ClassData, &Scene::AObjectComponent::ClassData);
		registerClass(&Scene::Components::OrthoCamera::ClassData, &Scene::Components::ACamera::ClassData);
		registerClass(&Scene::Components::PerspectiveCamera::ClassData, &Scene::Components::ACamera::ClassData);
	}

	std::shared_ptr<ClassDB> ClassDB::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<ClassDB>(new ClassDB);
		return instance;
	}

	const Class* ClassDB::getClassByName(std::string name) {
		return componentClasses[name];
	}
}
