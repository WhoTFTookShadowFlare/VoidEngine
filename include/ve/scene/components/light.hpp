#pragma once

#include "glm/ext/vector_float3.hpp"
#include "ve/event/event_listener.hpp"
#include "ve/scene/events.hpp"
#include "ve/scene/object_component.hpp"
#include <memory>

namespace VoidEngine::Scene::Components {
	class LightComponent : public AObjectComponent
	{
	private:
		glm::vec3 diffuse = { 1.0f, 1.0f, 1.0f };
		glm::vec3 specular = { 1.0f, 1.0f, 1.0f };

	protected:
		LightComponent();
	
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		glm::vec3 getDiffuse();
		void setDiffuse(glm::vec3);

		glm::vec3 getSpecular();
		void setSpecular(glm::vec3);
	};

	class PointLightComponent final : public LightComponent,
		public Event::IEventListener<Events::EComponentDraw>
	{
	private:
		float constant = 1.0f;
		float linear = 0.09f;
		float quadratic = 0.032f;

	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		static std::shared_ptr<PointLightComponent> create();

		void onEvent(Events::EComponentDraw&);
	};
}
