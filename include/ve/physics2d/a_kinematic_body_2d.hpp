#pragma once

#include <ve/physics2d/a_body_2d.hpp>

namespace VoidEngine::Physics2D {
	class AKinematicBody2D : public ABody2D {
	public:
		virtual ~AKinematicBody2D() = default;
	};
}
