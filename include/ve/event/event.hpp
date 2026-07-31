#pragma once

#include "ve/object.hpp"

namespace VoidEngine::Event {
	class AEvent : public Object {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
	};
}