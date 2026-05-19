#pragma once

#include <vector>

#include "ve/io/sfx/audio_device.hpp"

namespace VoidEngine::IO::SFX {
	class AudioBackend {
	private:
	public:
		virtual std::vector<AudioDevice> getDevices() = 0;
	};
}
