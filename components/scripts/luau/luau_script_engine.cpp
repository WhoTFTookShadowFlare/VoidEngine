#include "luau_script_engine.hpp"
#include "lua.h"
#include "lualib.h"
#include "luacode.h"
#include "luau_script.hpp"
#include "luau_script_module.hpp"
#include "types/class_holder.hpp"
#include "types/object_holder.hpp"
#include "types/property_holder.hpp"
#include "types/method_holder.hpp"
#include "types/event_handler_holder.hpp"
#include "types/event_bus.hpp"
#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "ve/event/event_bus.hpp"
#include "ve/io/res_providers/source/a_provider.hpp"
#include "ve/object.hpp"
#include "ve/script/a_script_engine.hpp"
#include "ve/variant.hpp"
#include <algorithm>
#include <cstdint>
#include <exception>
#include <map>
#include <memory>
#include <print>
#include <string>
#include <vector>

namespace VoidEngine::Scripts::Luau {
	std::shared_ptr<LuauScriptEngine> LuauScriptEngine::instance = nullptr;

	void LuauScriptEngine::setupNativeTypes() {
		luaL_register(vmState, "Object", objectLib);
		lua_pop(vmState, 1);

		luaL_register(vmState, "Class", classLib);
		lua_pop(vmState, 1);

		luaL_register(vmState, "Method", methodLib);
		lua_pop(vmState, 1);

		luaL_register(vmState, "Property", propertyLib);
		lua_pop(vmState, 1);

		luaL_register(vmState, "EventHandler", eventHandlerLib);
		lua_pop(vmState, 1);

		luaL_register(vmState, "EventBus", eventBusLib);
		lua_pop(vmState, 1);
		
		luaL_sandbox(vmState);
	}

	LuauScriptEngine::LuauScriptEngine() {
		vmState = luaL_newstate();
		luaL_openlibs(vmState);
	}

	LuauScriptEngine::~LuauScriptEngine() {
		lua_close(vmState);
		vmState = nullptr;
	}

	std::shared_ptr<LuauScriptEngine> LuauScriptEngine::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<LuauScriptEngine>(new LuauScriptEngine);
		return instance;
	}

	std::string LuauScriptEngine::getLanguage() { return "Luau"; }

	std::shared_ptr<Script> LuauScriptEngine::compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider> srcProvider) {
		if(srcProvider == nullptr) return nullptr;
		auto src = srcProvider->getShaderSource();
		ByteCode retVal;
		retVal.code = luau_compile(src.c_str(), src.length(), nullptr, &retVal.size);
		return LuauScript::create(retVal);
	}

	std::shared_ptr<AScriptModule> LuauScriptEngine::compileModuleScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider> srcProvider) {
		if(srcProvider == nullptr) return nullptr;
		auto src = srcProvider->getShaderSource();
		ByteCode retVal;
		retVal.code = luau_compile(src.c_str(), src.length(), nullptr, &retVal.size);
		return LuauScriptModule::create(retVal);
	}

	Variant LuauScriptEngine::objectToVariant(void* index) {
		if(index == nullptr) return nullptr;
		int32_t idx = *static_cast<int32_t*>(index);
		int type = lua_type(vmState, idx);
		switch(type) {
			case LUA_TNIL: return nullptr;
			case LUA_TBOOLEAN: return luaL_checkboolean(vmState, idx);
			case LUA_TNUMBER: return (float) luaL_checknumber(vmState, idx);
			case LUA_TINTEGER: return luaL_checkinteger(vmState, idx);
			// case LUA_TOBJECT: return static_cast<ObjectHolder*>(lua_touserdata(vmState, idx))->obj;
			case LUA_TUSERDATA: {
				void* ptr = lua_touserdata(vmState, idx);
				if(ptr == nullptr) return nullptr;
				if(!lua_getmetatable(vmState, idx)) return nullptr;

				lua_getfield(vmState, -1, "__type");
				std::string type = luaL_checkstring(vmState, -1);

				lua_pop(vmState, 2);

				if(type == "EventBus") return static_cast<EventBusHolder*>(lua_touserdata(vmState, idx))->bus;
				if(type == "Object") return static_cast<ObjectHolder*>(lua_touserdata(vmState, idx))->obj;

				std::println("[ERR] Cannot convert type '{}' to Variant", type);
				return nullptr;
			} break;
			case LUA_TSTRING: return luaL_checkstring(vmState, idx);
			case LUA_TTABLE: {
				bool isArray = true;
				lua_pushnil(vmState);
				while(lua_next(vmState, idx) != 0) {
					if(lua_type(vmState, -1) != LUA_TNUMBER) {
						isArray = false;
						lua_pop(vmState, 2);
						break;
					}
					lua_pop(vmState, 1);
				}


				lua_pushnil(vmState);
				if(isArray) {
					std::vector<Variant> arr;
					while(lua_next(vmState, idx) != 0) {
						int32_t* nextIdx = new int32_t(-1);
						arr.push_back(objectToVariant(nextIdx));
						delete nextIdx;
						lua_pop(vmState, 1);
					}
					lua_pop(vmState, 1);

					return arr;
				} else {
					std::map<std::string, Variant> map;
					while(lua_next(vmState, idx) != 0) {
						const char* key = lua_tostring(vmState, -2);
						int32_t* nextIdx = new int32_t(-1);
						map.insert({ key, objectToVariant(nextIdx) });
						delete nextIdx;
						lua_pop(vmState, 1);
					}
					lua_pop(vmState, 1);

					return map;
				}
			}; break;
		}

		std::println("Lua type {} is not supported yet", type);
		return nullptr;
	}

	void* LuauScriptEngine::objectFromVariant(Variant value) {
		switch(value.getType()) {
			case VoidEngine::VariantType::NIL: {
				lua_pushnil(vmState);
			}; break;
			case VoidEngine::VariantType::BOOL: {
				lua_pushboolean(vmState, value.asBool().value());
			}; break;
			case VoidEngine::VariantType::INT: {
				lua_pushinteger(vmState, value.asInt().value());
			}; break;
			case VoidEngine::VariantType::FLOAT: {
				lua_pushnumber(vmState, value.asFloat().value());
			}; break;
			case VoidEngine::VariantType::STRING: {
				lua_pushstring(vmState, value.asString().value().c_str());
			}; break;
			case VoidEngine::VariantType::ARRAY: {
				auto arr = value.asArray().value();
				lua_createtable(vmState, arr->size(), 0);
				for(size_t idx = 0; idx < arr->size(); idx++) {
					lua_pushinteger(vmState, idx + 1);
					objectFromVariant((*arr)[idx]);
					lua_settable(vmState, -3);
				}
			}; break;
			case VoidEngine::VariantType::MAP: {
				auto map = value.asMap().value();
				lua_createtable(vmState, 0, map->size());
				std::for_each(map->begin(), map->end(), [&](auto& entry) {
					lua_pushstring(vmState, entry.first.c_str());
					objectFromVariant(entry.second);
					lua_settable(vmState, -3);
				});
			}; break;
			case VoidEngine::VariantType::OBJECT: {
				ObjectHolder* ptr = static_cast<ObjectHolder*>(lua_newuserdatadtor(vmState, sizeof(ObjectHolder), [](void* ptr) {
					ObjectHolder* self = static_cast<ObjectHolder*>(ptr);
					self->obj.~shared_ptr<Object>();
				}));

				if(luaL_newmetatable(vmState, "Object")) {
					luaL_register(vmState, nullptr, objectMeth);
					lua_pushliteral(vmState, "Object");
					lua_rawsetfield(vmState, -2, "__type");
				}
				lua_setmetatable(vmState, -2);

				new(&ptr->obj) std::shared_ptr<Object>(value.asObject().value());
			}; break;
			case VoidEngine::VariantType::EVENT_BUS: {
				EventBusHolder* ptr = static_cast<EventBusHolder*>(lua_newuserdata(vmState, sizeof(EventBusHolder)));
				
				if(luaL_newmetatable(vmState, "EventBus")) {
					luaL_register(vmState, nullptr, eventBusMeth);
					lua_pushliteral(vmState, "EventBus");
					lua_rawsetfield(vmState, -2, "__type");
				}
				lua_setmetatable(vmState, -2);

				ptr->bus = value.asEventBus().value();
			}; break;
			default: {
				std::println("Lua Variant type conversion to {} is not yet implemented", (uint8_t) value.getType());
			}
		}

		return nullptr;
	}
}
