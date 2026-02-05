#pragma once

#include <filesystem>
#include <fstream>
#include <stdexcept>
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
			std::ifstream in = std::ifstream(filePath);

			if(!in.is_open()) throw std::runtime_error("Failed to get file stream");
			shaderSourceCode = std::string(std::istreambuf_iterator<char>{in}, {});
			in.close();
		}

		std::string getShaderSource() { return shaderSourceCode; }
	};
}

