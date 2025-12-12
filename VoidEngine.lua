project "VoidEngine"
	kind "StaticLib"
	language "C++"
	toolset "gcc"
	targetdir(tostring(_MAIN_SCRIPT_DIR) .. "/bin/%{cfg.buildcfg}")

	files { "src/**.hpp", "src/**.cpp" }
	cppdialect "C++17"

	usage "INTERFACE"
		links { "SDL3",  "glbinding" }

	usage "PUBLIC"
		includedirs { "include" }
		links { "glm" }

	filter "configurations:debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:release"
		defines { "NDEBUG" }
		optimize "On"

	filter "platforms:mac"
		system "macosx"
		architecture "UNIVERSAL"

	filter "platforms:win64"
		system "windows"
		architecture "x86_64"

	filter "platforms:nix64"
		system "linux"
		architecture "x86_64"

