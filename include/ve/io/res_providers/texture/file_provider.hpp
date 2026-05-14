#pragma once

#include "ve/io/res_providers/texture/a_provider.hpp"
#include <filesystem>

namespace VoidEngine::IO::ResourceProviders {
	class FileTextureProvider : public ATextureProvider {
		void* data = nullptr;
		glm::ivec2 size;
	public:
		FileTextureProvider(std::filesystem::path& filePath);
		~FileTextureProvider();

		glm::ivec2 getSize();
		std::vector<uint8_t> getData();
	};
}
