#include "ve/scene/components/sound.hpp"

#include "ve/io/sfx/audio.hpp"

namespace VoidEngine::Scene::Components {
	const Class SoundComponent::ClassData = {
		.name = "SoundComponent",
		.super = &AObjectComponent::ClassData,
		.constructor = new NativeConstructor(SoundComponent::create)
	};

	SoundComponent::SoundComponent() {}

	std::shared_ptr<SoundComponent> SoundComponent::create() {
		auto comp = std::shared_ptr<SoundComponent>(new SoundComponent);
		comp->source = VoidEngine::IO::SFX::Audio::getInstance()->createSource();
		return comp;
	}

	std::shared_ptr<VoidEngine::IO::SFX::AudioSource> SoundComponent::getSource() {
		return source;
	}
}
