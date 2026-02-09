#pragma once

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <format>
#include <string>

namespace VoidEngine::IO::GFX {
	class AShaderSourceProvider {
	public:
		virtual std::string getShaderSource() = 0;
	};

	class FileShaderSourceProvider : public AShaderSourceProvider {
		std::string shaderSourceCode = "";
	public:
		FileShaderSourceProvider(std::filesystem::path& filePath) {
			if(!(std::filesystem::exists(filePath) && !std::filesystem::is_directory(filePath))) {
				throw std::runtime_error(std::format("File {} is either a directory or does not exist", filePath.string()));
			}
			std::ifstream in = std::ifstream(filePath);

			if(!in.is_open()) throw std::runtime_error(std::format("Failed to open file {}", filePath.string()));
			shaderSourceCode = std::string(std::istreambuf_iterator<char>{in}, {});
			in.close();
		}

		std::string getShaderSource() { return shaderSourceCode; }
	};

	class BasicShaderSourceProvider : public AShaderSourceProvider {
		std::string shaderSourceCode = "";
	public:
		BasicShaderSourceProvider(std::string shaderSourceCode) : shaderSourceCode(shaderSourceCode) {}

		std::string getShaderSource() { return shaderSourceCode; }
	};
}

