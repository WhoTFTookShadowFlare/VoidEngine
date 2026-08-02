#pragma once

#include "ve/class_db.hpp"
#include "ve/variant.hpp"
#include <memory>

namespace VoidEngine::Scripts::Luau {
	struct LuauProperty final : public PropertyBase {
	private:
		const bool readonly;
	public:
		LuauProperty(std::string, bool readonly);

		Variant get(std::shared_ptr<Object>) const override;
		void set(std::shared_ptr<Object>, Variant value) const override;
		bool isReadOnly() const override;
	};
}
