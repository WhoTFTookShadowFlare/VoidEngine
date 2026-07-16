#include "ve/io/sfx/dummy/source_dummy.hpp"
#include "ve/io/sfx/audio_source.hpp"
#include <memory>

namespace VoidEngine::IO::SFX::Dummy {
	DummySource::DummySource() {}
	std::shared_ptr<AudioSource> DummySource::create() {
		return std::shared_ptr<AudioSource>(new DummySource);
	}

	glm::vec3 DummySource::getPosition() { return position; }
	void DummySource::setPosition(glm::vec3 value) { position = value;}

	glm::vec3 DummySource::getVelocity() { return velocity; }
	void DummySource::setVelocity(glm::vec3 value) { velocity = value; }

	std::shared_ptr<ResourceProviders::ASoundProvider> DummySource::getSound() { return sound; }
	void DummySource::setSound(std::shared_ptr<ResourceProviders::ASoundProvider> value) { sound = value; }

	void DummySource::setLooping(bool value) { looping = value; }
	bool DummySource::isLooping() { return looping; }

	void DummySource::play() { playing = true; }
	void DummySource::pause() { playing = false; }
	void DummySource::stop() { playing = false; }
	bool DummySource::isPlaying() { return playing; }
}
