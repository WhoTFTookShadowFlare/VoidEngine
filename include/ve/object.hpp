#pragma once

#include "ve/class_db.hpp"

namespace VoidEngine {
	class Object {
	private:
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
	};
}
