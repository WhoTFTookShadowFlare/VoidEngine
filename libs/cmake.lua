-- Common functions for CMake based libraries.

local module = {}

module.outputArgs = table.concat({
	"", -- Ensure a space before
	"-DCMAKE_RUNTIME_OUTPUT_DIRECTORY='" .. path.join(path.getabsolute(_MAIN_SCRIPT_DIR), "bin/%{cfg.buildcfg}") .. "'",
	"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY='" .. path.join(path.getabsolute(_MAIN_SCRIPT_DIR), "bin/%{cfg.buildcfg}") .. "'",
	"-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY='" .. path.join(path.getabsolute(_MAIN_SCRIPT_DIR), "bin/%{cfg.buildcfg}") .. "'",
	"" -- Ensure a space after
}, " ")

return module
