#pragma once

#include "ve/scene/object_component.hpp"
#include "ve/class_db.hpp"

#include "ve/io/sfx/audio_source.hpp"

namespace VoidEngine::Scene::Components {
	class SoundComponent : public AObjectComponent {
	private:
		SoundComponent();

		std::shared_ptr<VoidEngine::IO::SFX::AudioSource> source;
	public:
		static const Class ClassData;
		static std::shared_ptr<SoundComponent> create();

		std::shared_ptr<VoidEngine::IO::SFX::AudioSource> getSource();

		virtual const Class* getClass() const override { return &ClassData; }
	};
}