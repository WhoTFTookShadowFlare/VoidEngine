#include "ve/event/event.hpp"
#include "ve/io/res_providers/mesh/a_provider.hpp"

namespace VoidEngine::IO::ResourceProviders {
	const Class EMeshProviderChanged::ClassData = {
		.name = "EMeshProviderChanged",
		.super = &Event::AEvent::ClassData
	};
}
