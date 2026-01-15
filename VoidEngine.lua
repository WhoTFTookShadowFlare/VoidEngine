require("VoidEngineCSAPI")

project "VoidEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	targetdir(tostring(_MAIN_SCRIPT_DIR) .. "/bin/%{cfg.buildcfg}")

	files { "src/**.hpp", "src/**.cpp" }

	usage "INTERFACE"
		links { "SDL3",  "glbinding" }
		filter "platforms:not win*"
			links { "mono-2.0" }
		filter "platforms:win*"
			libdirs { "C:/Program Files/Mono/lib" }
			links { "mono-2.0-sgen" }

	usage "PUBLIC"
		includedirs { "include" }

	filter "configurations:debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:release"
		defines { "NDEBUG" }
		optimize "On"

	filter "platforms:mac"
		system "macosx"
		architecture "UNIVERSAL"

	filter "platforms:win*"
		system "windows"

	filter "platforms:linux*"
		system "linux"

	filter "platforms:*64"
		architecture "x86_64"

