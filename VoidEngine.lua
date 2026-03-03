require("VoidEngineCSAPI")
require("VELibs")

newoption {
	trigger = "disableOpenGL",
	value = "bool",
	default = "true",
	description = "Removes the OpenGL renderer backend",
	category = "Renderer Backends",
}

project "VoidEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++23"
	targetdir(tostring(_MAIN_SCRIPT_DIR) .. "/bin/%{cfg.buildcfg}")

	rtti "On"

	files { "src/**.hpp", "src/**.cpp" }

	usage "PUBLIC"
		uses { "SDL3" }
		filter "options:not disableOpenGL"
			uses { "glbinding" }
			defines { "GFX_BACKEND_GL" }

	usage "PRIVATE"
		includedirs { "stb" }

	usage "INTERFACE"
		filter "platforms:not win*"
			links { "mono-2.0" }
		filter "platforms:win*"
			libdirs { "C:/Program Files/Mono/lib" }
			links { "mono-2.0" }

	usage "PUBLIC"
		includedirs { "include" }

