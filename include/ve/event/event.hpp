#pragma once

#include "ve/object.hpp"

namespace VoidEngine::Event {
	class AEvent : public Object {
		VE_CLASS(AEvent)
	private:
		Variant scr_isSetup(std::vector<Variant>) { return isSetup(); }

		static std::shared_ptr<AEvent> create();
	protected:
		AEvent() = default;
	public:
		virtual bool isSetup() const { return false; }
	};
}