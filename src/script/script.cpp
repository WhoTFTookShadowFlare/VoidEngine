#include "ve/script/script.hpp"

namespace VoidEngine::Scripts {
	Script::Script(ByteCode code) : code(code) {}

	Script::~Script() {
		delete (char*) code.code;
	}

	ByteCode Script::getByteCode() { return code; }
}
