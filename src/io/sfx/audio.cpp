#include "ve/io/sfx/audio.hpp"
#include "ve/io/sfx/audio_backend.hpp"
#include <functional>
#include <print>
#include <vector>

#ifdef COMPONENT_AUDIO_OPENAL_ENABLED
#include "backend_openal.hpp"
#endif // COMPONENT_AUDIO_OPENAL_ENABLED
#include "ve/io/sfx/dummy/backend_dummy.hpp"

namespace VoidEngine::IO::SFX {
	std::shared_ptr<Audio> Audio::instance = nullptr;

	std::vector<std::function<AudioBackend*()>> backendLoaders = {
#ifdef COMPONENT_AUDIO_OPENAL_ENABLED
		[]() { return new OpenAL::OpenALBackend; },
#endif // COMPONENT_AUDIO_OPENAL_ENABLED
		[]() { return new Dummy::DummyBackend; }
	};

	Audio::Audio() {}

	Audio::~Audio() {
		if(backend == nullptr) return;
		delete backend;
	}

	std::shared_ptr<Audio> Audio::getInstance() {
		if(instance == nullptr) {
			instance = std::shared_ptr<Audio>(new Audio);
			for(const auto& loadFn : backendLoaders) {
				instance->backend = loadFn();
				if(instance->backend != nullptr) break;
			}
			if(instance->backend == nullptr) std::println("[FATAL] Failed to load audio backend");
		}
		return instance;
	}

	std::shared_ptr<AudioSource> Audio::createSource() {
		if(backend == nullptr) return nullptr;
		return backend->createSource();
	}
}
