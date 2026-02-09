#include "ve/io/gfx/texture_provider.hpp"
#include "stb_image.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <format>
#include <string>
#include <sys/types.h>
#include <vector>

namespace VoidEngine::IO::GFX {
	FileTextureProvider::FileTextureProvider(std::filesystem::path& filePath) {
		if(!(std::filesystem::exists(filePath) && !std::filesystem::is_directory(filePath))) {
			throw std::runtime_error(std::format("File {} is either a directory or does not exist", filePath.string()));
		}

		std::ifstream in = std::ifstream(filePath, std::ios::binary);
		if(!in.is_open()) throw std::runtime_error(std::format("Failed to open file {}", filePath.string()));
		std::basic_string<uint8_t> raw = std::basic_string<uint8_t>(std::istreambuf_iterator(in), {});
		in.close();

		int32_t channels = 0;
		data = stbi_load_from_memory(raw.data(), raw.size(), &size.x, &size.y, &channels, 4);
		if(data == nullptr) {
			throw std::runtime_error(stbi_failure_reason());
		}
	}

	FileTextureProvider::~FileTextureProvider() {
		if(data != nullptr) stbi_image_free(data);
	}

	glm::ivec2 FileTextureProvider::getSize() {
		return size;
	}

	std::vector<uint8_t> FileTextureProvider::getData() {
		const size_t channels = 4;
		std::vector<uint8_t> retVal(static_cast<uint8_t*>(data), static_cast<uint8_t*>(data) + (channels * size.x * size.y));
		return retVal;
	}
}

