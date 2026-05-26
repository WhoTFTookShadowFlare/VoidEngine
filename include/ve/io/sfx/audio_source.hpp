#pragma once

#include <glm/ext/vector_float3.hpp>

#include <memory>

#include "ve/io/res_providers/sfx/a_provider.hpp"

namespace VoidEngine::IO::SFX {
	class AudioSource {
	private:
	protected:
		std::shared_ptr<ResourceProviders::ASoundProvider> sound;
	public:
		virtual glm::vec3 getPosition() = 0;
		virtual void setPosition(glm::vec3) = 0;

		virtual glm::vec3 getVelocity() = 0;
		virtual void setVelocity(glm::vec3) = 0;

		virtual std::shared_ptr<ResourceProviders::ASoundProvider> getSound() = 0;
		virtual void setSound(std::shared_ptr<ResourceProviders::ASoundProvider>) = 0;

		virtual void setLooping(bool) = 0;
		virtual bool isLooping() = 0;

		virtual void play() = 0;
		virtual void pause() = 0;
		virtual void stop() = 0;
		virtual bool isPlaying() = 0;
	};
}
