workspace "VoidEngine"
	configurations { "debug", "release" }
	platforms {
		"win_x64", "win_x86", "win_ARM64",
		"linux_x64", "linux_x86", "linux_ARM64",
		"mac"
	}

	local defaulttarget = "debug_"
	if _TARGET_OS == "windows" then
		defaulttarget = defaulttarget .. "win_"
	elseif _TARGET_OS == "linux" then
		defaulttarget = defaulttarget .. "linux_"
	elseif _TARGET_OS == "macosx" then
		defaulttarget = defaulttarget .. "mac"
	end

	if _TARGET_OS ~= "macosx" then
		if os.hostarch() == "x86_64" then
			defaulttarget = defaulttarget .. "x64"
		elseif os.hostarch() == "x86" then
			defaulttarget = defaulttarget .. "x86"
		elseif os.hostarch() == "AARCH64" then
			defaulttarget = defaulttarget .. "ARM64"
		end
	end

	defaultplatform(defaulttarget)

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

