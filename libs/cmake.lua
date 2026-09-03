-- Common functions for CMake based libraries.

local module = {}

local utils = dofile("../utils.lua")

function module.getOutputArgs()
	if utils.isVS() then
		return table.concat({
			"", -- Ensure a space before
			"-DCMAKE_RUNTIME_OUTPUT_DIRECTORY='" .. path.join(path.getabsolute(_MAIN_SCRIPT_DIR), "bin") .. "'",
			"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY='" .. path.join(path.getabsolute(_MAIN_SCRIPT_DIR), "bin") .. "'",
			"-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY='" .. path.join(path.getabsolute(_MAIN_SCRIPT_DIR), "bin") .. "'",
			"" -- Ensure a space after
		}, " ")
	end
	return table.concat({
		"", -- Ensure a space before
		"-DCMAKE_RUNTIME_OUTPUT_DIRECTORY='" .. path.join(path.getabsolute(_MAIN_SCRIPT_DIR), "bin/%{cfg.buildcfg}") .. "'",
		"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY='" .. path.join(path.getabsolute(_MAIN_SCRIPT_DIR), "bin/%{cfg.buildcfg}") .. "'",
		"-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY='" .. path.join(path.getabsolute(_MAIN_SCRIPT_DIR), "bin/%{cfg.buildcfg}") .. "'",
		"" -- Ensure a space after
	}, " ")
end

function module.setupBuildCleanup(libPath)
	cleancommands {
		"{RMDIR} " .. path.join(libPath, "build")
	}
end

return module
