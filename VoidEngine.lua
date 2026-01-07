project "pocketpy"
	kind "SharedLib"
	language "C"
	cdialect "C11"
	targetdir(tostring(_MAIN_SCRIPT_DIR) .. "/bin/%{cfg.buildcfg}")

	files { "pocketpy/*.c" }

	usage "PUBLIC"
		includedirs { "pocketpy/include" }

	filter "platforms:win*"
		links { "ws2_32" }

project "VoidEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++23"
	targetdir(tostring(_MAIN_SCRIPT_DIR) .. "/bin/%{cfg.buildcfg}")

	files { "src/**.hpp", "src/**.cpp" }

	usage "PUBLIC"
		uses { "pocketpy" }
		links { "pocketpy" }

	usage "INTERFACE"
		links { "SDL3",  "glbinding" }

	usage "PUBLIC"
		defines { "PK_IS_PUBLIC_INCLUDE" }
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

