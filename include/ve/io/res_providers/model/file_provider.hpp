#pragma once

#include "ve/io/res_providers/model/a_provider.hpp"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fstream>
#include <filesystem>

namespace VoidEngine::IO::ResourceProviders {
	class FileModelProvider : public AModelProvider {
	private:
	public:
		FileModelProvider(std::filesystem::path& path) {
			bool fExists = std::filesystem::exists(path);
			bool isDir = !std::filesystem::is_directory(path);
			bool test = !(fExists && isDir);
			if(test) {
				throw std::runtime_error(std::format("File {} is either a directory or does not exist", path.string()));
			}

			std::ifstream in = std::ifstream(path, std::ios::binary);
			if(!in.is_open()) throw std::runtime_error(std::format("Failed to open file {}", path.string()));
			std::basic_string<uint8_t> raw = std::basic_string<uint8_t>(std::istreambuf_iterator(in), {});
			in.close();

			scene = importer.ReadFileFromMemory(raw.c_str(), raw.length(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
			if(scene == nullptr) throw std::runtime_error(importer.GetErrorString());
		}

		size_t getMeshCount() { return scene->mNumMeshes; }
		
		~FileModelProvider() {
			importer.FreeScene();
		}
	};
}
