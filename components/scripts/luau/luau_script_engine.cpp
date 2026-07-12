#include "luau_script_engine.hpp"
#include "lua.h"
#include "lualib.h"
#include "luacode.h"
#include "luau_script.hpp"
#include "ve/class_db.hpp"
#include "ve/object.hpp"
#include "ve/script/a_script_engine.hpp"
#include "ve/variant.hpp"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <print>

namespace VoidEngine::Scripts::Luau {
	std::shared_ptr<LuauScriptEngine> LuauScriptEngine::instance = nullptr;

	struct ObjectHolder {
		std::shared_ptr<Object> obj;
	};

	static int ObjectNew(lua_State* L);

	static int ObjectToString(lua_State* L);
	static int ObjectGet(lua_State* L);
	static int ObjectSet(lua_State* L);

	static const luaL_Reg objectMeth[] = {
		{ "__tostring", ObjectToString },
		{ "__index", ObjectGet },
		{ "__newindex", ObjectSet },
		{ nullptr, nullptr }
	};

	static const luaL_Reg objectLib[] = {
		{ "new", ObjectNew },
		{ nullptr, nullptr }
	};

	LuauScriptEngine::LuauScriptEngine() {
		vmState = luaL_newstate();
		luaL_openlibs(vmState);

		luaL_register(vmState, "Object", objectLib);
		lua_pop(vmState, 1);
		
		luaL_sandbox(vmState);
	}

	LuauScriptEngine::~LuauScriptEngine() {
		lua_close(vmState);
		vmState = nullptr;
	}

	std::shared_ptr<LuauScriptEngine> LuauScriptEngine::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<LuauScriptEngine>(new LuauScriptEngine);
		return instance;
	}

	std::shared_ptr<Script> LuauScriptEngine::compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider> srcProvider) {
		if(srcProvider == nullptr) return nullptr;
		auto src = srcProvider->getShaderSource();
		ByteCode retVal;
		retVal.code = luau_compile(src.c_str(), src.length(), nullptr, &retVal.size);
		return LuauScript::create(retVal);
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
			case LUA_TOBJECT: return static_cast<ObjectHolder*>(lua_touserdata(vmState, idx))->obj;
			case LUA_TSTRING: return luaL_checkstring(vmState, idx);
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
				for(auto idx = 0; idx < arr->size(); idx++) {
					lua_pushinteger(vmState, idx + 1);
					objectFromVariant((*arr)[idx]);
					lua_settable(vmState, -3);
				}
			}; break;
			case VoidEngine::VariantType::MAP: {
				lua_createtable(vmState, 0, 5);
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
			default: {
				std::println("Lua Variant type conversion to {} is not yet implemented", (uint8_t) value.getType());
			}
		}

		return nullptr;
	}

	static int ObjectNew(lua_State* L) {
		const char* type = luaL_checkstring(L, 1);
		if(type == nullptr) return 0;

		auto cls = ClassDB::getInstance()->getClassByName(type);
		if(cls == nullptr) return 0;
		if(cls->isAbstract()) return 0;
		
		ObjectHolder* ptr = static_cast<ObjectHolder*>(lua_newuserdatadtor(L, sizeof(ObjectHolder), [](void* ptr) {
			ObjectHolder* self = static_cast<ObjectHolder*>(ptr);
			self->obj.~shared_ptr<Object>();
		}));

		if(luaL_newmetatable(L, "Object")) {
			luaL_register(L, nullptr, objectMeth);
			lua_pushliteral(L, "Object");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		new(&ptr->obj) std::shared_ptr<Object>(cls->create());

		return 1;
	}

	static int ObjectToString(lua_State* L) {
		ObjectHolder* obj = static_cast<ObjectHolder*>(lua_touserdata(L, 1));
		lua_pushstring(L, obj->obj->getClass()->name);
		return 1;
	}

	static int ObjectGet(lua_State* L) {
		ObjectHolder* obj = static_cast<ObjectHolder*>(lua_touserdata(L, 1));
		const char* key = luaL_checkstring(L, 2);
		if(key == nullptr) return 0;

		auto cls = obj->obj->getClass();
		if(cls == nullptr) return 0;
		auto property = cls->findProperty(key);
		if(property == nullptr) return 0;
		LuauScriptEngine::getInstance()->objectFromVariant(property->get(obj->obj));

		return 1;
	}

	static int ObjectSet(lua_State* L) {
		ObjectHolder* obj = static_cast<ObjectHolder*>(lua_touserdata(L, 1));
		const char* key = luaL_checkstring(L, 2);
		if(key == nullptr) return 0;

		auto cls = obj->obj->getClass();
		if(cls == nullptr) return 0;
		auto property = cls->findProperty(key);
		if(property == nullptr) return 0;
		if(property->isReadOnly()) return 0;

		int32_t* idx = new int32_t(3);
		Variant value = LuauScriptEngine::getInstance()->objectToVariant(idx);
		delete idx;

		property->set(obj->obj, value);
		return 0;
	}
}
