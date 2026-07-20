#pragma once

#include "glm/ext/vector_float3.hpp"
#include "ve/event/event_listener.hpp"
#include "ve/scene/events.hpp"
#include "ve/scene/object_component.hpp"
#include <memory>

namespace VoidEngine::Scene::Components {
	class LightComponent final : public AObjectComponent,
		public Event::IEventListener<Events::EComponentDraw>
	{
	private:
		glm::vec3 ambient = { 1.0f, 1.0f, 1.0f };
		glm::vec3 diffuse = { 1.0f, 1.0f, 1.0f };
		glm::vec3 specular = { 1.0f, 1.0f, 1.0f };

		LightComponent();
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		static std::shared_ptr<LightComponent> create();

		void onEvent(Events::EComponentDraw&);
		
		glm::vec3 getAmbient();
		void setAmbient(glm::vec3);

		glm::vec3 getDiffuse();
		void setDiffuse(glm::vec3);

		glm::vec3 getSpecular();
		void setSpecular(glm::vec3);
	};
}
