#pragma once

#include "ve/scene/object_component.hpp"
#include "ve/scene/component_db.hpp"

#include "ve/io/sfx/audio_source.hpp"

namespace VoidEngine::Scene::Components {
	class SoundComponent : public AObjectComponent {
	private:
		SoundComponent();

		std::shared_ptr<VoidEngine::IO::SFX::AudioSource> source;
	public:
		static const ComponentClass ClassData;
		static std::shared_ptr<SoundComponent> create();

		std::shared_ptr<VoidEngine::IO::SFX::AudioSource> getSource();

		virtual const ComponentClass* getClass() const override { return &ClassData; }
	};
}