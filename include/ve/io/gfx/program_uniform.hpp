#pragma once

#include <cstdint>
#include <string>

namespace VoidEngine::IO::GFX {
	enum UniformType : uint32_t {
		INVALID = 0,

		// Basic types
		FLOAT,
		INT,

		// Structure types
		VECTOR_2F,
		VECTOR_3F,
		VECTOR_4F,
		VECTOR_2I,
		VECTOR_3I,
		VECTOR_4I,

		MATRIX_4X4F,

		// Object types
		SAMPLER_2D,
	};

	struct Uniform {
		friend class GraphicsProgram;
	private:
		Uniform(std::string name, int32_t location, UniformType type) :
			name(name),
			location(location),
			type(type) {}
		
		std::string name;
		int32_t location;
		UniformType type;

	public:
		constexpr std::string& getName() { return name; }
		constexpr int32_t getLocation() { return location; }
		constexpr UniformType getType() { return type; }
	};
}

