local module = {}

local cmake = require("cmake")

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "SDL3")

module.buildArgs = table.concat({
	"",
	"-DSDL_TESTS='OFF'",
	"-DSDL_EXAMPLES='OFF'",
	""
}, " ")

function module.use()
	links { "SDL3" }
	includedirs { path.join(module.libPath, "include") }
	dependson { "SDL3Build" }
	uses { "SDL3Build" }
end

function module.setupExternal()
	externalproject("SDL3Build")
	kind "Makefile"
	location(module.libPath)
	uuid(os.uuid("SDL3Build"))
end

local SDL3SrcDir = module.libPath
local SDL3BuildDir = path.join(module.libPath, "build")

project("SDL3Build")
	kind("Makefile")
	location(module.libPath)

	buildcommands {
		"{MKDIR} " .. SDL3BuildDir,
		"cmake " .. cmake.outputArgs .. module.buildArgs .. " -S " .. SDL3SrcDir .. " -B " .. SDL3BuildDir,
		"cmake --build " .. SDL3BuildDir
	}

	cleancommands {
		"cmake --build " .. SDL3BuildDir .. " --target clean"
	}

	usage "PUBLIC"
		includedirs {}

return module
