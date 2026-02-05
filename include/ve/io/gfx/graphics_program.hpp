#pragma once

#include "ve/io/gfx/mesh.hpp"

namespace VoidEngine::IO::GFX {
	class GraphicsProgram {
	protected:
		void forwardDraw(Mesh *mesh) { mesh->draw(); }
	public:
		virtual ~GraphicsProgram() {}

		virtual void draw(Mesh*) = 0;
	};
}

