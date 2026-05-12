#pragma once

#include "ve/io/res_providers/shader/a_provider.hpp"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <format>

namespace VoidEngine::IO::ResourceProviders {
	class FileShaderSourceProvider : public AShaderSourceProvider {
		std::string shaderSourceCode = "";
	public:
		FileShaderSourceProvider(std::filesystem::path& filePath) {
			if (!(std::filesystem::exists(filePath) && !std::filesystem::is_directory(filePath))) {
				throw std::runtime_error(std::format("File {} is either a directory or does not exist", filePath.string()));
			}
			std::ifstream in = std::ifstream(filePath);

			if (!in.is_open()) throw std::runtime_error(std::format("Failed to open file {}", filePath.string()));
			shaderSourceCode = std::string(std::istreambuf_iterator<char>{in}, {});
			in.close();
		}

		std::string getShaderSource() { return shaderSourceCode; }
	};
}
