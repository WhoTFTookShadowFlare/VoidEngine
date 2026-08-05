#pragma once

#include "ve/io/gfx/mesh.hpp"
#include <cstdint>

namespace VoidEngine::IO::GFX::OpenGL {
	class GLMesh : public Mesh {
		VE_CLASS(GLMesh)
		uint32_t VBO = 0, builtVtxCount = 0;
		void draw();
	protected:
		void buildMesh();
	public:
		GLMesh();
		~GLMesh();
	};
}
