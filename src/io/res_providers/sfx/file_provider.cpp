#include "ve/io/res_providers/sfx/file_provider.hpp"

#include <fstream>
#include <format>

#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"

namespace VoidEngine::IO::ResourceProviders {
	FileSoundProvider::FileSoundProvider(std::filesystem::path& path) {
		if(!(std::filesystem::exists(path) && !std::filesystem::is_directory(path)))
			throw std::runtime_error(std::format("{} either does not exist or is a directory", path.string()));

		std::ifstream in(path, std::ios::binary);
		if (!in.is_open()) throw std::runtime_error(std::format("Failed to open file {}", path.string()));
		std::basic_string<uint8_t> raw = std::basic_string<uint8_t>(std::istreambuf_iterator(in), {});
		in.close();

		//int channels, sample_rate;
		//stb_vorbis_decode_memory(raw.c_str(), raw.length(), &channels, &sample_rate, &data);

		int err = 0;
		stb_vorbis *vorbis = stb_vorbis_open_memory(raw.c_str(), raw.length(), &err, nullptr);
		stb_vorbis_info info = stb_vorbis_get_info(vorbis);

		channels = info.channels;
		sampleRate = info.sample_rate;
		sampleCount = stb_vorbis_stream_length_in_samples(vorbis);

		data = new short[sampleCount];
		stb_vorbis_get_samples_short(vorbis, channels, &data, sampleCount);
		stb_vorbis_close(vorbis);
	}

	FileSoundProvider::~FileSoundProvider() {
		delete[] data;
	}

	short* FileSoundProvider::getAudioData() { return data; }
	size_t FileSoundProvider::getAudioByteCount() { return sampleCount * sizeof(short); }
	uint32_t FileSoundProvider::getSampleRate() { return sampleRate; }
}
