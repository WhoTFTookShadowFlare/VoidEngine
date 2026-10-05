#pragma once

#include <ve/physics2d/a_body_2d.hpp>

namespace VoidEngine::Physics2D {
	class ADynamicBody2D : public ABody2D {
	public:
		virtual ~ADynamicBody2D() = default;
	};
}
