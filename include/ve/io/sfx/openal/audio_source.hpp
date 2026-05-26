#pragma once

#include "ve/io/sfx/audio_source.hpp"

namespace VoidEngine::IO::SFX::OpenAL {
	class OpenALAudioSource : public AudioSource {
	private:
		uint32_t source = 0;
		uint32_t buffer = 0;
	public:
		OpenALAudioSource();
		~OpenALAudioSource();

		glm::vec3 getPosition();
		void setPosition(glm::vec3);

		glm::vec3 getVelocity();
		void setVelocity(glm::vec3);

		std::shared_ptr<ResourceProviders::ASoundProvider> getSound();
		void setSound(std::shared_ptr<ResourceProviders::ASoundProvider>);

		void setLooping(bool) override;
		bool isLooping() override;

		void play() override;
		void pause() override;
		void stop() override;
		bool isPlaying() override;
	};
}