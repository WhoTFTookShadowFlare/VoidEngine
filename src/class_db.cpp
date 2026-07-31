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
		registerAbstractClass<Event::AEvent, Object>();

		registerAbstractClass<Event::AEvent, IO::ResourceProviders::EMeshProviderChanged>();
		registerAbstractClass<Event::AEvent, IO::ResourceProviders::ETextureChanged>();

		registerAbstractClass<Events::EQuitEvent, Event::AEvent>();
		registerAbstractClass<Events::EScreenLayoutChangedEvent, Event::AEvent>();

		registerAbstractClass<IO::Events::BasicWindowEvent, Event::AEvent>();
		registerAbstractClass<IO::Events::EWindowMinimized, Event::AEvent>();
		registerAbstractClass<IO::Events::EWindowRestored, Event::AEvent>();
		registerAbstractClass<IO::Events::EWindowMaximized, Event::AEvent>();
		registerAbstractClass<IO::Events::EWindowCloseRequested, Event::AEvent>();
		registerAbstractClass<IO::Events::EWindowSizeChanged, Event::AEvent>();
		registerAbstractClass<IO::Events::EWindowRepositioned, Event::AEvent>();
		registerAbstractClass<IO::Events::EMouseEnter, Event::AEvent>();
		registerAbstractClass<IO::Events::EWindowFocus, Event::AEvent>();

		registerAbstractClass<Scene::Events::EComponentUpdate, Event::AEvent>();
		registerAbstractClass<Scene::Events::ESceneDraw, Event::AEvent>();
		registerAbstractClass<Scene::Events::EComponentDraw, Event::AEvent>();
		registerAbstractClass<Scene::Events::EAddedToScene, Event::AEvent>();
		registerAbstractClass<Scene::Events::ERemovedFromScene, Event::AEvent>();
		registerAbstractClass<Scene::Events::EComponentAddedToObject, Event::AEvent>();
		registerAbstractClass<Scene::Events::EComponentRemovedFromObject, Event::AEvent>();
		registerAbstractClass<Scene::Events::EChildAdded, Event::AEvent>();
		registerAbstractClass<Scene::Events::EChildRemoved, Event::AEvent>();

		registerClass<Scene::Scene, Object>();
		// registerClass<Scene::GameObject, Object>();

		registerAbstractClass<Scene::AObjectComponent, Object>();

		registerAbstractClass<Scene::Components::LightComponent, Scene::AObjectComponent>();
		registerClass<Scene::Components::PointLightComponent, Scene::Components::LightComponent>();
		registerClass<Scene::Components::SpotLightComponent, Scene::Components::LightComponent>();
		registerClass<Scene::Components::MeshComponent, Scene::AObjectComponent>();

		registerClass<Scene::Components::SoundComponent, Scene::AObjectComponent>();

		registerAbstractClass<Scene::Components::ACamera, Scene::AObjectComponent>();
		registerClass<Scene::Components::OrthoCamera, Scene::Components::ACamera>();
		registerClass<Scene::Components::PerspectiveCamera, Scene::Components::ACamera>();
	}

	std::shared_ptr<ClassDB> ClassDB::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<ClassDB>(new ClassDB);
		return instance;
	}

	const Class* ClassDB::getClassByName(std::string name) {
		return componentClasses[name];
	}
}
