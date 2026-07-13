#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <concepts>
#include <cassert>
#include "ve/variant.hpp"

namespace VoidEngine {
	class Object;
	class Variant;
	struct Class;

	template<typename T>
	concept IsAbstractClass =
		std::is_base_of<Object, T>::value &&
		requires(T a) {
			{ T::ClassData } -> std::convertible_to<Class>;
			{ a.getClass() } -> std::same_as<const Class*>;
		};

	template<typename T>
	concept IsClass =
		IsAbstractClass<T> &&
		requires(T a) {
			{ T::create() } -> std::convertible_to<std::shared_ptr<Object>>;
			// { T::deserialize() } -> std::convertible_to<std::shared_ptr<AObjectComponent>>;
		};
	
	struct PropertyBase {
	protected:
		PropertyBase(std::string name) : name(name) {}
	public:
		virtual ~PropertyBase() = default;

		const std::string name;

		virtual Variant get(std::shared_ptr<Object>) const = 0;
		virtual void set(std::shared_ptr<Object>, Variant) const = 0;
		virtual bool isReadOnly() const = 0;
	};

	struct MethodBase {
	protected:
		MethodBase(std::string name) : name(name) {}
	public:
		virtual ~MethodBase() = default;

		const std::string name;
		virtual Variant call(std::shared_ptr<Object> obj, std::vector<Variant> args) const = 0;
	};

	struct Class {
		const char* name;

		const Class *super;
		std::vector<const Class*> childTypes;
		std::vector<const PropertyBase*> properties;
		std::vector<const MethodBase*> methods;

		std::function<std::shared_ptr<Object>()> create;

		bool operator==(Class RHS) const { return name == RHS.name; }

		bool instanceOf(const Class* cls) const {
			const Class *check = this;
			while(check != nullptr) {
				if(cls == check) return true;
				check = check->super;
			}
			return false;
		}

		bool isAbstract() const {
			return create == nullptr;
		}

		const PropertyBase* findProperty(std::string name) const {
			const auto idx = std::find_if(properties.cbegin(), properties.cend(), [&name](const auto prop) {
				return prop->name == name;
			});
			if(idx == properties.cend()) return nullptr;
			return *idx;
		}

		const MethodBase* findMethod(std::string name) const {
			const auto idx = std::find_if(methods.cbegin(), methods.cend(), [&name](const auto meth) {
				return meth->name == name;
			});
			if(idx == methods.cend()) return nullptr;
			return *idx;
		}
	};

	class ClassDB {
	private:
		static std::shared_ptr<ClassDB> instance;

		std::unordered_map<std::string, const Class*> componentClasses;

		ClassDB();
	public:
		static std::shared_ptr<ClassDB> getInstance();

		const Class* getClassByName(std::string);

		template<IsAbstractClass clazz, IsAbstractClass parent>
		void registerAbstractClass() {
			Class *cls = (Class*) &clazz::ClassData;
			cls->super = &parent::ClassData;

			Class *parentCls = (Class*) &parent::ClassData;
			parentCls->childTypes.emplace_back(cls);

			componentClasses[cls->name] = cls;
		}

		template<IsClass clazz, IsAbstractClass parent>
		void registerClass() {
			registerAbstractClass<clazz, parent>();
			Class *cls = (Class*) &clazz::ClassData;
			cls->create = clazz::create;
		}
	};
}
