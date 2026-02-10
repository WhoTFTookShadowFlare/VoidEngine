require("VoidEngineCSAPI")

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

	files { "src/**.hpp", "src/**.cpp" }

	usage "PUBLIC"
		filter "options:not disableOpenGL"
			defines { "GFX_BACKEND_GL" }

	usage "PRIVATE"
		includedirs { "stb" }

	usage "INTERFACE"
		links { "SDL3",  "glbinding" }
		filter "platforms:not win*"
			links { "mono-2.0" }
		filter "platforms:win*"
			libdirs { "C:/Program Files/Mono/lib" }
			links { "mono-2.0" }

	usage "PUBLIC"
		includedirs { "include" }

