#pragma once

#include <ve/class_db.hpp>

namespace VoidEngine {
	struct NativeConstructor final : public ConstructorBase {
	private:
		const std::function<std::shared_ptr<Object>()> fn;
	public:
		NativeConstructor(std::function<std::shared_ptr<Object>()> fn) 
			: fn(fn)
		{}

		std::shared_ptr<Object> create() const override { return fn(); }
	};
}
