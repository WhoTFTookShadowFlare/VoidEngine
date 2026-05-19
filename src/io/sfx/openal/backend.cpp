#include "ve/io/sfx/openal/backend.hpp"

#include "AL/alc.h"

namespace VoidEngine::IO::SFX::OpenAL {
	OpenALBackend::OpenALBackend() {
		device = alcOpenDevice(nullptr);
		ctx = alcCreateContext(device, nullptr);
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
}
