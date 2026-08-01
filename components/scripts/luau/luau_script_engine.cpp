#include "luau_script_engine.hpp"
#include "lua.h"
#include "lualib.h"
#include "luacode.h"
#include "luau_script.hpp"
#include "luau_script_module.hpp"
#include "ve/class_db.hpp"
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

	struct ObjectHolder {
		std::shared_ptr<Object> obj;
	};

	struct ClassHolder {
		const Class* cls;
	};

	static int ObjectNew(lua_State* L);

	static int ObjectToString(lua_State* L);
	static int ObjectGet(lua_State* L);
	static int ObjectSet(lua_State* L);
	static int ObjectCall(lua_State* L);
	static int ObjectEq(lua_State* L);

	static const luaL_Reg objectMeth[] = {
		{ "__tostring", ObjectToString },
		{ "__index", ObjectGet },
		{ "__newindex", ObjectSet },
		{ "__namecall", ObjectCall },
		{ "__eq", ObjectEq },
		{ nullptr, nullptr }
	};

	static const luaL_Reg objectLib[] = {
		{ "new", ObjectNew },
		{ nullptr, nullptr }
	};

	static int ClassNew(lua_State* L);
	static int GetClass(lua_State* L);
	static int RegisterClass(lua_State* L);

	static int ClassToString(lua_State* L);
	static int ClassGet(lua_State* L);
	static int ClassSet(lua_State* L);
	static int ClassCall(lua_State* L);
	static int ClassEq(lua_State* L);

	static const luaL_Reg classMeth[] = {
		{ "__tostring", ClassToString },
		{ "__index", ClassGet },
		{ "__newindex", ClassSet },
		{ "__namecall", ClassCall },
		{ "__eq", ClassEq },
		{ nullptr, nullptr }
	};

	static const luaL_Reg classLib[] = {
		{ "new", ClassNew },
		{ "get", GetClass },
		{ "registerclass", RegisterClass },
		{ nullptr, nullptr }
	};

	void LuauScriptEngine::setupNativeTypes() {
		luaL_register(vmState, "Object", objectLib);
		lua_pop(vmState, 1);

		luaL_register(vmState, "Class", classLib);
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
			case LUA_TUSERDATA: return static_cast<ObjectHolder*>(lua_touserdata(vmState, idx))->obj;
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
			default: {
				std::println("Lua Variant type conversion to {} is not yet implemented", (uint8_t) value.getType());
			}
		}

		return nullptr;
	}

	static int ObjectNew(lua_State* L) {
		if(!lua_isstring(L, 1)) {
			std::println("[ERR] [LUAU] Object.new takes only a string for class type");
			return 0;
		}

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

		new(&ptr->obj) std::shared_ptr<Object>(cls->constructor->create());

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

	static int ObjectCall(lua_State* L) {
		ObjectHolder* obj = static_cast<ObjectHolder*>(lua_touserdata(L, 1));
		const char* key = lua_namecallatom(L, nullptr);
		if(key == nullptr) return 0;

		auto meth = obj->obj->getClass()->findMethod(key);
		if(meth == nullptr) return 0;

		auto engine = LuauScriptEngine::getInstance();
		int32_t* stackIndex = new int32_t(1);
		std::vector<Variant> args;
		for(int32_t arg = 1; arg < lua_gettop(L); arg++) {
			*stackIndex = arg + 1;

			std::println("luau arg type: {}", lua_type(L, *stackIndex));

			args.push_back(engine->objectToVariant(stackIndex));
		}
		delete stackIndex;

		Variant retVal = meth->call(obj->obj, args);
		if(retVal.isNil()) return 0;
		engine->objectFromVariant(retVal);
		return 1;
	}

	static int ObjectEq(lua_State* L) {
		if(!lua_istable(L, 2)) {
			lua_pushboolean(L, false);
			return 1;
		}

		try {
			ObjectHolder* LHS = static_cast<ObjectHolder*>(luaL_checkudata(L, 1, "Object"));
			ObjectHolder* RHS = static_cast<ObjectHolder*>(luaL_checkudata(L, 2, "Object"));
			lua_pushboolean(L, LHS->obj == RHS->obj);
			return 1;
		} catch(std::exception& ex) {	}

		lua_pushboolean(L, false);
		return 1;
	}

	static int ClassNew(lua_State* L) {
		if(!lua_isstring(L, 1)) {
			std::println("[ERR] [LUAU] Class.new takes only a string for class name");
			return 0;
		}

		const char* name = luaL_checkstring(L, 1);
		if(name == nullptr) return 0;

		ClassHolder* ptr = static_cast<ClassHolder*>(lua_newuserdatadtor(L, sizeof(ClassHolder), [](void* data) {
			ClassHolder* cls = static_cast<ClassHolder*>(data);
			if(ClassDB::getInstance()->getClassByName(cls->cls->name) != cls->cls) {
				std::println("[ERR] Class {} was instanced but not registered!", cls->cls->name);
			}
		}));

		if(luaL_newmetatable(L, "Class")) {
			luaL_register(L, nullptr, classMeth);
			lua_pushliteral(L, "Class");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		Class* cls = new Class;
		cls->name = name;
		ptr->cls = cls;

		return 1;
	}

	static int GetClass(lua_State* L) {
		if(!lua_isstring(L, 1)) {
			std::println("[ERR] [LUAU] Class.get takes only a string for class name");
			return 0;
		}

		const char* name = luaL_checkstring(L, 1);
		if(name == nullptr) return 0;

		const Class* cls = ClassDB::getInstance()->getClassByName(name);
		ClassHolder* ptr = static_cast<ClassHolder*>(lua_newuserdata(L, sizeof(ClassHolder)));
		ptr->cls = cls;

		if(luaL_newmetatable(L, "Class")) {
			luaL_register(L, nullptr, classMeth);
			lua_pushliteral(L, "Class");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		return 1;
	}

	static int RegisterClass(lua_State* L) {
		ClassHolder* cls = (ClassHolder*) luaL_checkudata(L, 1, "Class");
		ClassHolder* parent = (ClassHolder*) luaL_checkudata(L, 2, "Class");

		ClassDB::getInstance()->registerClass(cls->cls, parent->cls);

		return 0;
	}

	static int ClassToString(lua_State* L) {
		ClassHolder* cls = static_cast<ClassHolder*>(lua_touserdata(L, 1));
		lua_pushstring(L, cls->cls->name);
		return 1;
	}
	
	static int ClassGet(lua_State* L) {
		return 0;
	}
	
	static int ClassSet(lua_State* L) {
		return 0;
	}
	
	static int ClassCall(lua_State* L) {
		return 0;
	}

	static int ClassEq(lua_State* L) {
		if(!lua_istable(L, 2)) {
			lua_pushboolean(L, false);
			return 1;
		}

		try {
			ClassHolder* LHS = static_cast<ClassHolder*>(luaL_checkudata(L, 1, "Class"));
			ClassHolder* RHS = static_cast<ClassHolder*>(luaL_checkudata(L, 2, "Class"));
			lua_pushboolean(L, LHS->cls == RHS->cls);
			return 1;
		} catch(std::exception& ex) {	}

		lua_pushboolean(L, false);
		return 1;
	}
}
