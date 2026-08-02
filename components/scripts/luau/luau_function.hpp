#pragma once

#include <string>
#include <cstdint>
#include "ve/class_db.hpp"

struct lua_State;

namespace VoidEngine::Scripts::Luau {
	struct LuauMethod final : public MethodBase {
	private:
		lua_State* L;
	public:
		LuauMethod(std::string name, lua_State* L, uint32_t stackIdx);
		~LuauMethod();

		Variant call(std::shared_ptr<Object> obj, std::vector<Variant> args) const override;
	};
}
