#pragma once

#include <memory>
#include "ve/io/sfx/audio_backend.hpp"
#include "ve/io/sfx/audio_source.hpp"

namespace VoidEngine::IO::SFX {
	class Audio {
	private:
		static std::shared_ptr<Audio> instance;
		Audio();

		AudioBackend *backend = nullptr;
	public:
		static std::shared_ptr<Audio> getInstance();
		~Audio();

		std::shared_ptr<AudioSource> createSource();
	};
}
