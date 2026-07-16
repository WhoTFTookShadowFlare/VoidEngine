#pragma once

#include "ve/io/sfx/audio_source.hpp"
#include <memory>

namespace VoidEngine::IO::SFX::Dummy {
	class DummySource final : public AudioSource {
	private:
		glm::vec3 position, velocity;
		bool looping = false, playing = false;

		DummySource();
	public:
		static std::shared_ptr<AudioSource> create();

		glm::vec3 getPosition();
		void setPosition(glm::vec3);

		glm::vec3 getVelocity();
		void setVelocity(glm::vec3);

		std::shared_ptr<ResourceProviders::ASoundProvider> getSound();
		void setSound(std::shared_ptr<ResourceProviders::ASoundProvider>);

		void setLooping(bool);
		bool isLooping();

		void play();
		void pause();
		void stop();
		bool isPlaying();
	};
}
