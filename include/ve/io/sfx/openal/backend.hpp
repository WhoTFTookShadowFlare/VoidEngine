#pragma once

#include "ve/io/sfx/audio_backend.hpp"

#include <AL/alc.h>

namespace VoidEngine::IO::SFX::OpenAL {
	class OpenALBackend : public AudioBackend {
	private:
		ALCdevice *device = nullptr;
		ALCcontext *ctx = nullptr;
	public:
		OpenALBackend();
		~OpenALBackend();
		std::vector<AudioDevice> getDevices() override;
	};
}
