#pragma once

#include "ve/io/gfx/dummy/backend_dummy.hpp"
#include "ve/io/sfx/audio_backend.hpp"

namespace VoidEngine::IO::SFX::Dummy {
	class DummyBackend final : public AudioBackend {
	private:
		glm::vec3 listenerPosition, listenerVelocity, listenerOrientation;
	public:
		std::vector<AudioDevice> getDevices();

		std::shared_ptr<AudioSource> createSource();

		void setListenerPosition(glm::vec3);
		glm::vec3 getListenerPosition();
		void setListenerVelocity(glm::vec3);
		glm::vec3 getListenerVelocity();
		void setListenerOrientation(glm::vec3);
		glm::vec3 getListenerOrientation();
	};
}
