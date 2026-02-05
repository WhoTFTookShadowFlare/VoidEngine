#pragma once

#include "ve/io/gfx/mesh.hpp"
#include <cstdint>

namespace VoidEngine::IO::GFX::OpenGL {
	class GLMesh : public Mesh {
		uint32_t VBO = 0, builtVtxCount = 0;
		void draw();
	public:
		GLMesh();
		~GLMesh();

		void buildMesh();
	};
}
