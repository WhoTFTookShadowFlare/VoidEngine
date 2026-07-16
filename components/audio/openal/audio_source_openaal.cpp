#include "audio_source_openal.hpp"

#include <AL/al.h>

#include <stdexcept>
#include <format>
#include <print>

namespace VoidEngine::IO::SFX::OpenAL {
	OpenALAudioSource::OpenALAudioSource() {
		alGenSources(1, &source);
		ALenum err = alGetError();
		if(err != AL_NO_ERROR) {
			throw std::runtime_error(std::format("Got OpenAL error: {}", err));
		}

		alGenBuffers(1, &buffer);
		err = alGetError();
		if(err != AL_NO_ERROR) {
			alDeleteSources(1, &source);
			throw std::runtime_error(std::format("Got OpenAL error: {}", err));
		}
	}

	OpenALAudioSource::~OpenALAudioSource() {
		alDeleteSources(1, &source);
		alDeleteBuffers(1, &buffer);
	}

	glm::vec3 OpenALAudioSource::getPosition() {
		glm::vec3 value(0.0f);
		alGetSource3f(source, AL_POSITION, &value.x, &value.y, &value.z);
		ALenum err = alGetError();
		if(err != AL_NO_ERROR) std::println("Got OpenAL error: {}", err);
		return value;
	}
	
	void OpenALAudioSource::setPosition(glm::vec3 value) {
		alSource3f(source, AL_POSITION, value.x, value.y, value.z);
		ALenum err = alGetError();
		if (err != AL_NO_ERROR) std::println("Got OpenAL error: {}", err);
	}

	glm::vec3 OpenALAudioSource::getVelocity() {
		glm::vec3 value(0.0f);
		alGetSource3f(source, AL_VELOCITY, &value.x, &value.y, &value.z);
		ALenum err = alGetError();
		if (err != AL_NO_ERROR) std::println("Got OpenAL error: {}", err);
		return value;
	}
	
	void OpenALAudioSource::setVelocity(glm::vec3 value) {
		alSource3f(source, AL_VELOCITY, value.x, value.y, value.z);
		ALenum err = alGetError();
		if (err != AL_NO_ERROR) std::println("Got OpenAL error: {}", err);
	}

	std::shared_ptr<ResourceProviders::ASoundProvider> OpenALAudioSource::getSound() {
		return sound;
	}

	void OpenALAudioSource::setSound(std::shared_ptr<ResourceProviders::ASoundProvider> value) {
		sound = value;
		alBufferData(buffer, AL_FORMAT_MONO16, value->getAudioData(), value->getAudioByteCount(), value->getSampleRate());
		ALenum err = alGetError();
		if(err != AL_NO_ERROR) std::println("Got OpenAL error: {}", err);

		alSourceQueueBuffers(source, 1, &buffer);
		err = alGetError();
		if(err != AL_NO_ERROR) std::println("Got OpenAL error: {}", err);
	}

	void OpenALAudioSource::setLooping(bool value) {
		alSourcei(source, AL_LOOPING, value);
	}

	bool OpenALAudioSource::isLooping() {
		int isLooping = false;
		alGetSourcei(source, AL_LOOPING, &isLooping);
		return isLooping;
	}

	void OpenALAudioSource::play() {
		alSourcePlay(source);
	}

	void OpenALAudioSource::pause() {
		alSourcePause(source);
	}

	void OpenALAudioSource::stop() {
		alSourceStop(source);
	}

	bool OpenALAudioSource::isPlaying() {
		int state = false;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}
}
