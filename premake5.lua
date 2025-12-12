workspace "VoidEngine"
	configurations { "debug", "release" }
	platforms { "win64", "nix64", "mac" }

	if _TARGET_OS == "windows" then
		defaultplatform "win64"
	elseif _TARGET_OS == "linux" then
		defaultplatform "nix64"
	elseif _TARGET_OS == "macosx" then
		defaultplatform "mac"
	end

require("VoidEngine")
