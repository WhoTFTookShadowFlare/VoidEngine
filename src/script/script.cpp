#include "ve/script/script.hpp"

namespace VoidEngine::Scripts {
	Script::Script(std::shared_ptr<IO::ResourceProviders::ASourceProvider> code) : code(code) {}

	Script::~Script() {	}

	std::shared_ptr<IO::ResourceProviders::ASourceProvider> Script::getCode() { return code; }
}
