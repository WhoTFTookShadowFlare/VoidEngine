#pragma once

#include <stdint.h>

namespace VoidEngine::IO::ResourceProviders {
	class ASoundProvider {
	private:
	public:
		virtual short *getAudioData() = 0;
		virtual size_t getAudioByteCount() = 0;
		virtual uint32_t getSampleRate() = 0;
	};
}
