#pragma once

#include "glm/ext/vector_int2.hpp"

namespace VoidEngine::IO::GFX {
	class IRenderTarget {
	private:
	public:
		virtual void bindRenderTarget() = 0;
		virtual glm::ivec2 getSize() = 0;
	};
}
