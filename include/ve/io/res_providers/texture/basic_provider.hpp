#pragma once

#include "ve/io/res_providers/texture/a_provider.hpp"

namespace VoidEngine::IO::ResourceProviders {
	class BasicTextureProvider : public ATextureProvider {
		std::vector<uint8_t> data;
		glm::ivec2 size;
	public:
		BasicTextureProvider(std::vector<uint8_t> data, glm::ivec2 size) : data(data), size(size) {}

		glm::ivec2 getSize() { return size; }
		std::vector<uint8_t> getData() { return data; }
	};
}
