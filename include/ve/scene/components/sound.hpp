#pragma once

#include "ve/scene/object_component.hpp"
#include "ve/class_db.hpp"

#include "ve/io/sfx/audio_source.hpp"

namespace VoidEngine::Scene::Components {
	class SoundComponent : public AObjectComponent {
		VE_CLASS(SoundComponent)
	private:
		SoundComponent();

		std::shared_ptr<VoidEngine::IO::SFX::AudioSource> source;
	public:
		static std::shared_ptr<SoundComponent> create();

		std::shared_ptr<VoidEngine::IO::SFX::AudioSource> getSource();
	};
}