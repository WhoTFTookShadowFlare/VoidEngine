#pragma once

#include "ve/object.hpp"

namespace VoidEngine::Scene {
	class UIElement : public Object {
	private:

		glm::vec2 position;
		glm::vec2 size;

	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
	};
}
