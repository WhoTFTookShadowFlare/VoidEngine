#include "ve/scene/components/mono.hpp"
#include <iostream>
#include <mono-2.0/mono/metadata/class.h>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <mono-2.0/mono/metadata/object.h>
#include <stdexcept>

namespace VoidEngine::Scene::Components	{
	using namespace std;

	MonoComponent::MonoComponent(MonoObject *self) :
		inst(self),
		instClass(mono_object_get_class(inst)),
		updateFunc(mono_class_get_method_from_name(instClass, "update", 1)),
		drawFunc(mono_class_get_method_from_name(instClass, "draw", 1)) {	}

	void MonoComponent::draw(double delta) {
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
}

