#pragma once

#include <ve/physics2d/a_body_2d.hpp>

namespace VoidEngine::Physics2D {
	class AStaticBody2D : public ABody2D {
	public:
		virtual ~AStaticBody2D() = default;
	};
}
