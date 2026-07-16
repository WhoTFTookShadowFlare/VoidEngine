#include "ve/io/sfx/audio.hpp"

#ifdef COMPONENT_AUDIO_OPENAL_ENABLED
#include "backend_openal.hpp"
#endif // COMPONENT_AUDIO_OPENAL_ENABLED

namespace VoidEngine::IO::SFX {
	std::shared_ptr<Audio> Audio::instance = nullptr;

	Audio::Audio() {
#ifdef COMPONENT_AUDIO_OPENAL_ENABLED
		backend = new OpenAL::OpenALBackend;
#endif // COMPONENT_AUDIO_OPENAL_ENABLED
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
