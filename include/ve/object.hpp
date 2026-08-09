#pragma once

#include "ve/class_db.hpp"
#include "ve/script/a_script_object.hpp"
#include <memory>

#ifdef VE_CLASS
#undef VE_CLASS
#endif

#define VE_CLASS(cls) \
	private: \
	public: \
		static const ::VoidEngine::Class ClassData; \
		virtual const ::VoidEngine::Class* getClass() const { \
			if(getScript() == nullptr) return &ClassData; \
			return getScript()->getClass(); \
		} \
	private:

namespace VoidEngine {
	class Object {
		VE_CLASS(Object)
	private:
		std::shared_ptr<Scripts::AObjectScript> script = nullptr;
	public:
		std::shared_ptr<Scripts::AObjectScript> getScript() const;
		void setScript(std::shared_ptr<Scripts::AObjectScript>);
	};
}
