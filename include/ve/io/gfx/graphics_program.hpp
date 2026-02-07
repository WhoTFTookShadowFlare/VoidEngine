#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <vector>
#include <string>

namespace VoidEngine::IO::GFX {
	class GraphicsProgram {
	protected:
		void forwardDraw(Mesh *mesh) { mesh->draw(); }
		Uniform createUniform(std::string name, int32_t location, UniformType type) { return Uniform { name, location, type }; }
	public:
		virtual ~GraphicsProgram() {}

		virtual void draw(Mesh*) = 0;

		virtual std::vector<Uniform> getUniforms() = 0;
	};
}

