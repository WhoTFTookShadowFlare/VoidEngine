#include "ve/cs/engine_module.hpp"
#include "ve/cs/interface.hpp"
#include "ve/cs/math/module.hpp"
#include "ve/engine.hpp"
#include "ve/math/rect2.hpp"
#include <cstdint>
#include <memory>
#include <mono-2.0/mono/metadata/loader.h>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <mono-2.0/mono/metadata/object.h>
#include <vector>

namespace VoidEngine::CS {
	CSharpInterface *interface = nullptr;

	double Engine_GetDelta();
	MonoString *Engine_GetExecutablePath();
	MonoString *Engine_GetDataDirectory();
	MonoArray *Engine_GetMonitorAreas();
	MonoObject *Engine_GetWorkspaceArea();
	MonoArray *Engine_GetWorkspaceChunked();
	MonoArray *Engine_GetWorkspaceDeadzones();
	MonoArray *Engine_GetWorkspaceCaves();
	MonoArray *Engine_GetWorkspacePlateaus();

	void initModule_Engine(void) {
		mono_add_internal_call("VoidEngine.Engine::GetDelta", (void*) Engine_GetDelta);
		mono_add_internal_call("VoidEngine.Engine::GetExecutablePath", (void*) Engine_GetExecutablePath);
		mono_add_internal_call("VoidEngine.Engine::GetDataDirectory", (void*) Engine_GetDataDirectory);
		mono_add_internal_call("VoidEngine.Engine::GetMonitorAreas", (void*) Engine_GetMonitorAreas);
		mono_add_internal_call("VoidEngine.Engine::GetWorkspaceArea", (void*) Engine_GetWorkspaceArea);
		mono_add_internal_call("VoidEngine.Engine::GetWorkspaceChunked", (void*) Engine_GetWorkspaceChunked);
		mono_add_internal_call("VoidEngine.Engine::GetWorkspaceDeadzones", (void*) Engine_GetWorkspaceDeadzones);
		mono_add_internal_call("VoidEngine.Engine::GetWorkspaceCaves", (void*) Engine_GetWorkspaceCaves);
		mono_add_internal_call("VoidEngine.Engine::GetWorkspacePlateaus", (void*) Engine_GetWorkspacePlateaus);

		interface = CSharpInterface::getInstance();
	}

	std::shared_ptr<Engine> engine = Engine::getInstance();

	double Engine_GetDelta() {
		return engine->getDelta();
	}

	MonoString *Engine_GetExecutablePath() {
		return mono_string_new_wrapper(engine->getExecutablePath().c_str());
	}

	MonoString *Engine_GetDataDirectory() {
		return mono_string_new_wrapper(engine->getDataDirectory().c_str());
	}

	MonoArray *Engine_GetMonitorAreas() {
		std::vector<VoidEngine::Math::Rect2i> areas = engine->getMonitorAreas();
		MonoArray *array = interface->allocArray(Math::getRect2iClass(), areas.size());

		for(uint8_t idx = 0; idx < areas.size(); idx++)
			mono_array_setref(array, idx, Math::rect2iToMonoObject(areas[idx]));

		return array;
	}

	MonoObject *Engine_GetWorkspaceArea() {
		return CS::Math::vec2iToMonoObject(Engine::getInstance()->getWorkspaceArea());
	}

	MonoArray *Engine_GetWorkspaceChunked() {
		std::vector<VoidEngine::Math::Rect2i> areas = engine->getWorkspaceChunked();
		MonoArray *array = interface->allocArray(Math::getRect2iClass(), areas.size());

		for(uint8_t idx = 0; idx < areas.size(); idx++)
			mono_array_setref(array, idx, Math::rect2iToMonoObject(areas[idx]));

		return array;
	}

	MonoArray *Engine_GetWorkspaceDeadzones() {
		std::vector<VoidEngine::Math::Rect2i> areas = engine->getWorkspaceDeadzones();
		MonoArray *array = interface->allocArray(Math::getRect2iClass(), areas.size());

		for(uint8_t idx = 0; idx < areas.size(); idx++)
			mono_array_setref(array, idx, Math::rect2iToMonoObject(areas[idx]));

		return array;
	}

	MonoArray *Engine_GetWorkspaceCaves() {
		std::vector<VoidEngine::Math::Rect2i> areas = engine->getWorkspaceCaves();
		MonoArray *array = interface->allocArray(Math::getRect2iClass(), areas.size());

		for(uint8_t idx = 0; idx < areas.size(); idx++)
			mono_array_setref(array, idx, Math::rect2iToMonoObject(areas[idx]));

		return array;
	}

	MonoArray *Engine_GetWorkspacePlateaus() {
		std::vector<VoidEngine::Math::Rect2i> areas = engine->getWorkspacePlateaus();
		MonoArray *array = interface->allocArray(Math::getRect2iClass(), areas.size());

		for(uint8_t idx = 0; idx < areas.size(); idx++)
			mono_array_setref(array, idx, Math::rect2iToMonoObject(areas[idx]));

		return array;
	}
}

