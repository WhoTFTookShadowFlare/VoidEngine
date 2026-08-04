#pragma once

#include "ve/class_db.hpp"
#include "ve/object.hpp"
#include "ve/variant.hpp"
#include <memory>

namespace VoidEngine {
	template<IsAbstractClass T>
	struct NativeProperty : public PropertyBase {
		using Getter = Variant (T::*)(void) const;
		using Setter = void (T::*)(Variant);
	private:
		const Getter getterFn;
		const Setter setterFn;
	public:
		NativeProperty(std::string name, Getter getterFn) :
			PropertyBase(name), getterFn(getterFn), setterFn(nullptr)
		{}
		NativeProperty(std::string name, Getter getterFn, Setter setterFn) :
			PropertyBase(name), getterFn(getterFn), setterFn(setterFn)
		{}

		Variant get(std::shared_ptr<Object> object) const override {
			if(!object->getClass()->instanceOf(&T::ClassData)) return nullptr;
			return (std::static_pointer_cast<T>(object).get()->*getterFn)();
		}

		void set(std::shared_ptr<Object> object, Variant value) const override {
			if(isReadOnly()) return;
			if(!object->getClass()->instanceOf(&T::ClassData)) return;
			(std::static_pointer_cast<T>(object).get()->*setterFn)(value);
		}

		bool isReadOnly() const override { return setterFn == nullptr; }
	};
}