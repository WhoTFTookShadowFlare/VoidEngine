#pragma once

#include "ve/io/sfx/audio_backend.hpp"
#include "ve/io/sfx/audio_source.hpp"

#include <AL/alc.h>

#include <memory>

namespace VoidEngine::IO::SFX::OpenAL {
	class OpenALBackend : public AudioBackend {
	private:
		ALCdevice *device = nullptr;
		ALCcontext *ctx = nullptr;
	public:
		OpenALBackend();
		~OpenALBackend();
		std::vector<AudioDevice> getDevices() override;

		std::shared_ptr<AudioSource> createSource() override;

		void setListenerPosition(glm::vec3) override;
		glm::vec3 getListenerPosition() override;
		void setListenerVelocity(glm::vec3) override;
		glm::vec3 getListenerVelocity() override;
		void setListenerOrientation(glm::vec3) override;
		glm::vec3 getListenerOrientation() override;
	};
}
