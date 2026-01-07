workspace "VoidEngine"
	configurations { "debug", "release" }
	platforms { "win64", "linux64", "mac" }

	if _TARGET_OS == "windows" then
		defaultplatform "win64"
	elseif _TARGET_OS == "linux" then
		defaultplatform "linux64"
	elseif _TARGET_OS == "macosx" then
		defaultplatform "mac"
	end

require("VoidEngine")
