#pragma once

#include <algorithm>
#include <memory>
#include <print>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <concepts>
#include <cassert>

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

	struct EventHandlerBase {
	protected:
		EventHandlerBase(const Class* event) : event(event) {}
	public:
		virtual ~EventHandlerBase() = default;

		const Class* event;
		virtual void handleEvent(std::shared_ptr<Object> obj, std::shared_ptr<Object> event) const = 0;
	};

	struct ConstructorBase {
	protected:
		ConstructorBase() {}
	public:
		virtual ~ConstructorBase() = default;

		virtual std::shared_ptr<Object> create() const = 0;
	};

	struct NativeConstructor final : public ConstructorBase {
	private:
		const std::function<std::shared_ptr<Object>()> fn;
	public:
		NativeConstructor(std::function<std::shared_ptr<Object>()> fn) 
			: fn(fn)
		{}

		std::shared_ptr<Object> create() const override { return fn(); }
	};

	struct Class {
		const char* name;

		const Class *super;
		std::vector<const PropertyBase*> properties;
		std::vector<const MethodBase*> methods;
		std::vector<const EventHandlerBase*> eventHandlers;
		const ConstructorBase* constructor = nullptr;

		const char* getName() const { return name; }
		const Class* getSuper() const { return super; }
		const std::vector<const PropertyBase*>& getProperties() const { return properties; }
		const std::vector<const MethodBase*>& getMethods() const { return methods; }
		const std::vector<const EventHandlerBase*>& getEventHandlers() const { return eventHandlers; }

		bool operator==(Class* RHS) const { return name == RHS->name; }

		bool instanceOf(const Class* cls) const {
			const Class *check = this;
			while(check != nullptr) {
				if(cls == check) return true;
				check = check->super;
			}
			return false;
		}

		bool isAbstract() const {
			return constructor == nullptr;
		}

		const PropertyBase* findProperty(std::string name) const {
			const Class* cls = this;
			while(cls != nullptr) {
				const auto idx = std::find_if(cls->properties.cbegin(), cls->properties.cend(), [&name](const auto prop) {
					return prop->name == name;
				});
				if(idx == properties.cend()) {
					cls = cls->super;
					continue;
				}
				return *idx;
			}
			return nullptr;
		}

		const MethodBase* findMethod(std::string name) const {
			const Class* cls = this;
			while(cls != nullptr) {
				const auto idx = std::find_if(cls->methods.cbegin(), cls->methods.cend(), [&name](const auto meth) {
					return meth->name == name;
				});
				if(idx == methods.cend()) {
					cls = cls->super;
					continue;
				}
				return *idx;
			}
			return nullptr;
		}

		const EventHandlerBase* findEventHandler(const Class* eventClass) const {
			const Class* cls = this;
			while(cls != nullptr) {
				const auto idx = std::find_if(cls->eventHandlers.cbegin(), cls->eventHandlers.cend(), [&eventClass](const auto handler) {
					return handler->event == eventClass;
				});
				if(idx == eventHandlers.cend()) {
					cls = cls->super;
					continue;
				}
				return *idx;
			}
			return nullptr;
		}
	};

	class ClassDB {
		friend class Engine;
	private:
		static std::shared_ptr<ClassDB> instance;

		std::unordered_map<std::string, const Class*> componentClasses;
		bool classListFrozen = false;

		void freezeClassList();

		ClassDB();
	public:
		static std::shared_ptr<ClassDB> getInstance();

		const Class* getClassByName(std::string);

		void registerClass(const Class* cls);
	};
}
