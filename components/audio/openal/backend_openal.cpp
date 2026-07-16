#include "backend_openal.hpp"

#include <AL/alc.h>
#include <AL/al.h>

#include "audio_source_openal.hpp"

#include <stdexcept>

namespace VoidEngine::IO::SFX::OpenAL {
	OpenALBackend::OpenALBackend() {
		device = alcOpenDevice(nullptr);
		if(device == nullptr) throw std::runtime_error("Failed to open default device");
		ctx = alcCreateContext(device, nullptr);
		if(ctx == nullptr) throw std::runtime_error("Failed to create OpenAL context");
		alcMakeContextCurrent(ctx);
	}

	OpenALBackend::~OpenALBackend() {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(ctx);
		alcCloseDevice(device);
	}

	std::vector<AudioDevice> OpenALBackend::getDevices() {
		const char *deviceNames = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
		std::vector<AudioDevice> devices = {};
		while(*deviceNames != (char) '\0') {
			std::string name = deviceNames;
			deviceNames = deviceNames + name.length();
			
			devices.emplace_back(name);
		}
		return devices;
	}

	std::shared_ptr<AudioSource> OpenALBackend::createSource() {
		return std::shared_ptr<AudioSource>(new OpenALAudioSource);
	}

	void OpenALBackend::setListenerPosition(glm::vec3 value) {
		alListener3f(AL_POSITION, value.x, value.y, value.z);
	}

	glm::vec3 OpenALBackend::getListenerPosition() {
		glm::vec3 value(0.0f);
		alGetListener3f(AL_POSITION, &value.x, &value.y, &value.z);
		return value;
	}

	void OpenALBackend::setListenerVelocity(glm::vec3 value) {
		alListener3f(AL_VELOCITY, value.x, value.y, value.z);
	}

	glm::vec3 OpenALBackend::getListenerVelocity() {
		glm::vec3 value(0.0f);
		alGetListener3f(AL_VELOCITY, &value.x, &value.y, &value.z);
		return value;
	}

	void OpenALBackend::setListenerOrientation(glm::vec3 facing) {
		float orientation[6] = { facing.x, facing.y, facing.z, 0, 1, 0 };
		alListenerfv(AL_ORIENTATION, orientation);
	}

	glm::vec3 OpenALBackend::getListenerOrientation() {
		float orientation[6];
		alGetListenerfv(AL_ORIENTATION, orientation);
		return { orientation[0], orientation[1], orientation[2] };
	}
}
