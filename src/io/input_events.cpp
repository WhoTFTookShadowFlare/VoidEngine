#include "ve/io/input_events.hpp"

namespace VoidEngine::IO::Events {
	const Class EMouseMotion::ClassData = {
		.name = "EMouseMotion"
	};

	const Class EMouseButton::ClassData = {
		.name = "EMouseButton"
	};

	const Class EKeyButton::ClassData = {
		.name = "EKeyButton"
	};
}
