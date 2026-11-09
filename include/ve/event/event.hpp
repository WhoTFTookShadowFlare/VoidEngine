#pragma once

#include "ve/object.hpp"

namespace VoidEngine::Event {
	class AEvent : public Object {
		VE_CLASS(AEvent)
	private:
		Variant scr_isSetup(std::vector<Variant>) { return isSetup(); }
	public:
		virtual bool isSetup() const { return false; }
	};
}