#include "ve/io/sfx/audio.hpp"

#include "ve/io/sfx/openal/backend.hpp"

namespace VoidEngine::IO::SFX {
	std::shared_ptr<Audio> Audio::instance = nullptr;

	Audio::Audio() {
		backend = new OpenAL::OpenALBackend;
	}

	Audio::~Audio() {
		if(backend == nullptr) return;
		delete backend;
	}

	std::shared_ptr<Audio> Audio::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<Audio>(new Audio);
		return instance;
	}

	std::shared_ptr<AudioSource> Audio::createSource() {
		if(backend == nullptr) return nullptr;
		return backend->createSource();
	}
}
