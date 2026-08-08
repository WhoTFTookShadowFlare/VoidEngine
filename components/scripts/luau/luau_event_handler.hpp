#pragma once

#include <ve/class_db.hpp>

struct lua_State;

namespace VoidEngine::Scripts::Luau {
	struct LuauEventHandler : public EventHandlerBase {
	private:
		lua_State* L;
	public:
		LuauEventHandler(const Class* eventType, lua_State* L, int32_t stackIdx);
		~LuauEventHandler();

		void handleEvent(std::shared_ptr<Object> obj, std::shared_ptr<Object> event) const override;
	};
}
