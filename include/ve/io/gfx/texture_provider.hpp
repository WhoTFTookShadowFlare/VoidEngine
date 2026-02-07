#pragma once

#include <filesystem>
#include <glm/ext/vector_int2.hpp>

namespace VoidEngine::IO::GFX {
	class ATextureProvider {
	public:
		virtual ~ATextureProvider() {}

		virtual glm::ivec2 getSize() = 0;
		virtual void *getData() = 0;
	};

	class FileTextureProvider : public ATextureProvider {
		void *data = nullptr;
		glm::ivec2 size;
	public:
		FileTextureProvider(std::filesystem::path& filePath);
		~FileTextureProvider();

		glm::ivec2 getSize();
		void *getData();
	};
}

