#pragma once

#include <cstdint>
#include <glm/ext/vector_int2.hpp>
#include <vector>

namespace VoidEngine::IO::ResourceProviders {
	class ATextureProvider {
	public:
		virtual ~ATextureProvider() {}

		virtual glm::ivec2 getSize() = 0;
		virtual std::vector<uint8_t> getData() = 0;
	};
}
