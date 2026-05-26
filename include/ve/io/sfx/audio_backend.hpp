#pragma once

#include <vector>
#include <memory>

#include <glm/ext/vector_float3.hpp>

#include "ve/io/sfx/audio_device.hpp"
#include "ve/io/sfx/audio_source.hpp"

namespace VoidEngine::IO::SFX {
	class AudioBackend {
	private:
	public:
		virtual std::vector<AudioDevice> getDevices() = 0;

		virtual std::shared_ptr<AudioSource> createSource() = 0;

		virtual void setListenerPosition(glm::vec3) = 0;
		virtual glm::vec3 getListenerPosition() = 0;
		virtual void setListenerVelocity(glm::vec3) = 0;
		virtual glm::vec3 getListenerVelocity() = 0;
		virtual void setListenerOrientation(glm::vec3) = 0;
		virtual glm::vec3 getListenerOrientation() = 0;
	};
}
