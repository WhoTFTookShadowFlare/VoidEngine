#include "ve/scene/components/mono.hpp"
#include <iostream>
#include <mono-2.0/mono/metadata/class.h>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <mono-2.0/mono/metadata/object.h>
#include <stdexcept>

namespace VoidEngine::Scene::Components	{
	using namespace std;

	MonoComponent::MonoComponent(MonoObject *self) :
		// TODO: Fix small memory leak here
		//	Cuased by cyclic reference
		//	Better to keep than delete prematurly
		gcHandle(mono_gchandle_new(self, false)),
		instClass(mono_object_get_class(self)),
		updateFunc(mono_class_get_method_from_name(instClass, "Update", 1)),
		drawFunc(mono_class_get_method_from_name(instClass, "Draw", 1)) {	}

	MonoComponent::~MonoComponent() {
		mono_gchandle_free(gcHandle);
	}

	void MonoComponent::draw(double delta) {
		MonoObject *inst = mono_gchandle_get_target(gcHandle);
		if(inst == nullptr) return;

		if(drawFunc == nullptr || inst == nullptr)
			throw runtime_error("[ERROR] A MonoComponent is missing either the MonoObject or the Draw(double) function");

		void *args[] = {
			&delta
		};
		MonoObject *exception = nullptr;
		mono_runtime_invoke(drawFunc, inst, args, &exception);
		if(exception != nullptr) {
			cerr << "[ERROR] A MonoComponent threw an exception in Draw(double)" << endl;
		}
	}

	void MonoComponent::update(double delta) {
		MonoObject *inst = mono_gchandle_get_target(gcHandle);
		if(inst == nullptr) return;

		if(updateFunc == nullptr || inst == nullptr)
			throw runtime_error("[ERROR] A MonoComponent is missing either the MonoObject or the Update(double) function");

		void *args[] = {
			&delta
		};
		MonoObject *exception = nullptr;
		mono_runtime_invoke(updateFunc, inst, args, &exception);
		if(exception != nullptr) {
			cerr << "[ERROR] A MonoComponent threw an exception in Update(double)" << endl;
		}
	}

	MonoClass *MonoComponent::getCSClass() {
		return instClass;
	}

	MonoObject *MonoComponent::getObject() {
		return mono_gchandle_get_target(gcHandle);
	}
}

