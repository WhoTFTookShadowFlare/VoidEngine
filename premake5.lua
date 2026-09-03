local module = {}

workspace "VoidEngine"
	configurations { "Debug", "Release" }
	cppdialect "C++23"
	targetdir "bin/%{cfg.buildcfg}"
	location(path.join(_MAIN_SCRIPT_DIR, "VoidEngine"))

	rtti "Off"

	architecture "amd64"

	-- fatalwarnings "On"

local libs = include("libs")
local components = include("components")

components.setupProjects()

project "VoidEngine"
	kind "StaticLib" --TODO: DLL exports to make this a SharedLib
	targetdir(path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}"))
	language "C++"

	files { "src/**.cpp" }
	includedirs { "generated" }

	libs.glm.use()
	libs.stb.use()
	libs.sdl3.use()
	libs.assimp.use()
	libs.toml.use()

	components.applyUses()

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		optimize "On"

	filter {}

	usage "PUBLIC"
		includedirs { "include" }

function module.useVoidEngine()
	uses { "VoidEngine" }
	links { "VoidEngine" }
	libdirs { path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}") }
	libs.glm.use()
end

function module.addVoidEngine()
	externalproject("VoidEngine")
	location("VoidEngine")
	uuid(os.uuid("VoidEngine"))
	kind("SharedLib")

	libs.setupExternal()
	components.setupExternal()
end

newaction {
	trigger = "codegen",
	description = "Generates c++ code for enabled optional components.",

	onStart = function ()
		components.runCodegen()
	end
}

return module
