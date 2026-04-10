#include "ve/io/input.hpp"

namespace VoidEngine::IO {
	std::shared_ptr<Input> Input::instance = nullptr;

	std::shared_ptr<Input> Input::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<Input>(new Input());
		return instance;
	}
}
