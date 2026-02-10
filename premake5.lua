workspace "VoidEngine"
	configurations { "debug", "release" }
	platforms {
		"win_x64", "win_x86", "win_ARM64",
		"linux_x64", "linux_x86", "linux_ARM64",
		"mac"
	}

	if _TARGET_OS == "windows" then
		defaultplatform "win64"
	elseif _TARGET_OS == "linux" then
		defaultplatform "linux64"
	elseif _TARGET_OS == "macosx" then
		defaultplatform "mac"
	end

filter "platforms:win*"
	system "windows"
filter "platforms:linux*"
	system "linux"
filter "platforms:mac"
	system "macosx"
	architecture "universal"

filter "platforms:*x86"
	architecture "x86"
filter "platforms:*x64"
	architecture "x64"
filter "platforms:*ARM64"
	architecture "ARM64"

filter "configurations:debug"
	symbols "On"
	defines { "DEBUG" }
filter "configurations:release"
	optimize "On"
	defines { "NDEBUG" }

require("VoidEngine")

