#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"

namespace VoidEngine::IO::ResourceProviders {
	const Class ETextureChanged::ClassData = {
		.name = "ETextureChanged",
		.super = &Event::AEvent::ClassData
	};
}
