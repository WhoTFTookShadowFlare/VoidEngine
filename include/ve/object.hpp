#pragma once

#include "ve/class_db.hpp"

// TODO: Add macro for common class data

#ifdef VE_CLASS
#undef VE_CLASS
#endif

#ifdef VE_CLASS_GET_CLASS_MODIFIER
#undef VE_CLASS_GET_CLASS_MODIFIER
#endif
#define VE_CLASS_GET_CLASS_MODIFIER

#define VE_CLASS(cls) \
	private: \
	public: \
		static const ::VoidEngine::Class ClassData; \
		virtual const ::VoidEngine::Class* getClass() const VE_CLASS_GET_CLASS_MODIFIER { return &ClassData; } \
	private:

namespace VoidEngine {
	class Object {
		VE_CLASS(Object)
	};
}

#undef VE_CLASS_GET_CLASS_MODIFIER
#define VE_CLASS_GET_CLASS_MODIFIER override
