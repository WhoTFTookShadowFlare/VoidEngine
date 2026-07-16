#include "ve/io/sfx/dummy/backend_dummy.hpp"
#include "ve/io/sfx/dummy/source_dummy.hpp"

namespace VoidEngine::IO::SFX::Dummy {
	std::vector<AudioDevice> DummyBackend::getDevices() {
		return {};
	}

	std::shared_ptr<AudioSource> DummyBackend::createSource() {
		return DummySource::create();
	}

	void DummyBackend::setListenerPosition(glm::vec3 value) {
		listenerPosition = value;
	}
	
	glm::vec3 DummyBackend::getListenerPosition() {
		return listenerPosition;
	}
	
	void DummyBackend::setListenerVelocity(glm::vec3 value) {
		listenerVelocity = value;
	}
	
	glm::vec3 DummyBackend::getListenerVelocity() {
		return listenerVelocity;
	}
	
	void DummyBackend::setListenerOrientation(glm::vec3 value) {
		listenerOrientation = value;
	}

	glm::vec3 DummyBackend::getListenerOrientation() {
		return listenerOrientation;
	}
}
