local module = {}

local codegen = dofile("../../../codegen.lua")
local utils = dofile("../../../utils.lua")

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "lua")

function module.runCodegen(includeSection, entrySection)
	if includeSection == nil or type(includeSection) ~= "table" then
		print("[FATAL] Failed to do codegen for Lua, includeSection is not codegen")
		os.exit(1, true)
	end
	if entrySection == nil or type(entrySection) ~= "table" then
		print("[FATAL] Failed to do codegen for Lua, entrySection is not a codegen")
		os.exit(1, true)
	end

	includeSection:addStringPart("lua_script_engine.hpp")
	entrySection:addStringPart("::VoidEngine::Scripts::Lua::LuaScriptEngine")
end

function module.setupProject()
	project "Lua"
		kind "SharedLib"
		targetdir(path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}"))
		location(module.libPath)
		language "C"
		if utils.isVS() then
			defines { "LUA_BUILD_AS_DLL" }
		end

		includedirs {
			module.libPath
		}

		files {
			path.join(module.libPath, "*.c")
		}

		removefiles {
			path.join(module.libPath, "onelua.c"),
			path.join(module.libPath, "lua.c")
		}

		filter "configurations:Debug"
			defines { "DEBUG" }
			symbols "On"

		filter "configurations:Release"
			defines { "NDEBUG" }
			optimize "On"
end

function module.use()
	print("links Lua")
	links { "Lua" }
	includedirs {
		module.libPath,
		path.getdirectory(module.libPath)
	}

	files {
		path.join(path.getdirectory(module.libPath), "**.cpp")
	}
end

function module.setupExternal()
	externalproject "Lua"
	kind "SharedLib"
	uuid(os.uuid("Lua"))
	location(module.libPath)
	targetdir(path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}"))
end

return module