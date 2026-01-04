newoption {
	trigger = "pyversion",
	value = "version",
	description = "The python version to build against",
	allowed = {
		{ "3.13" },
		{ "3.14" }
	},
	default = "3.13"
}

project "VoidEngine"
	kind "StaticLib"
	language "C++"
	toolset "gcc"
	targetdir(tostring(_MAIN_SCRIPT_DIR) .. "/bin/%{cfg.buildcfg}")

	files { "src/**.hpp", "src/**.cpp" }
	cppdialect "C++23"

	usage "INTERFACE"
		links { "SDL3",  "glbinding" }

		filter "platforms:win*"
			if _OPTIONS["pyversion"] == "3.13" then
				links { "python313" }
			elseif _OPTIONS["pyversion"] == "3.14" then
				links { "python314" }
			end

		filter "platforms:linux*"
			links { "python3.13" }

		filter "platforms:macosx"
			if _OPTIONS["pyversion"] == "3.13" then
				links { "python3.13" }
			elseif _OPTIONS["pyversion"] == "3.14" then
				links { "python3.14" }
			end

	usage "PUBLIC"
		includedirs { "include" }
		
		if _OPTIONS["pyversion"] == "3.13" then
			defines { "python3_13" }
		elseif _OPTIONS["pyversion"] == "3.14" then
			defines { "python3_14" }
		end

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

