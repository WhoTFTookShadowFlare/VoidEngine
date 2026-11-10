#pragma once

#include <SDL3/SDL_joystick.h>

namespace VoidEngine::IO {
	struct JoystickInternal final {
		SDL_Joystick* ctrl = nullptr;
	};
}
