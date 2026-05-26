#pragma once

#include "ve/io/res_providers/sfx/a_provider.hpp"

#include <filesystem>

namespace VoidEngine::IO::ResourceProviders {
	class FileSoundProvider : public ASoundProvider {
	private:
		short *data;
		size_t sampleCount;
		int32_t channels;
		uint32_t sampleRate;
	public:
		FileSoundProvider(std::filesystem::path& path);
		~FileSoundProvider();

		short* getAudioData() override;
		size_t getAudioByteCount() override;
		uint32_t getSampleRate() override;
	};
}