#pragma once

#include <cstdint>
#include <filesystem>
#include <glm/ext/vector_int2.hpp>
#include <vector>

namespace VoidEngine::IO::GFX {
	class ATextureProvider {
	public:
		virtual ~ATextureProvider() {}

		virtual glm::ivec2 getSize() = 0;
		virtual std::vector<uint8_t> getData() = 0;
	};

	class BasicTextureProvider : public ATextureProvider {
		std::vector<uint8_t> data;
		glm::ivec2 size;
	public:
		BasicTextureProvider(std::vector<uint8_t> data, glm::ivec2 size) : data(data), size(size) {}

		glm::ivec2 getSize() { return size; }
		std::vector<uint8_t> getData() { return data; }
	};

	class FileTextureProvider : public ATextureProvider {
		void *data = nullptr;
		glm::ivec2 size;
	public:
		FileTextureProvider(std::filesystem::path& filePath);
		~FileTextureProvider();

		glm::ivec2 getSize();
		std::vector<uint8_t> getData();
	};
}

