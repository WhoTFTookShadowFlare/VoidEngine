local module = {}

local cmake = require("cmake")

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "toml++")

module.buildArgs = table.concat({
	"",
	""
}, " ")

function module.use()
	includedirs { module.libPath }
	dependson { "TomlBuild" }
	uses { "TomlBuild" }
end

function module.setupExternal()
	externalproject("TomlBuild")
	kind "Makefile"
	location(module.libPath)
	uuid(os.uuid("TomlBuild"))
end

local tomlSrcDir = module.libPath
local tomlBuildDir = path.join(module.libPath, "build")

project("TomlBuild")
	kind "Makefile"
	location(module.libPath)

	buildcommands {
		"{MKDIR} " .. tomlBuildDir,
		"cmake " .. module.buildArgs .. cmake.outputArgs .. "-S " .. tomlSrcDir .. " -B " .. tomlBuildDir,
		"cmake --build " .. tomlBuildDir
	}

	cleancommands {
		"cmake --build " .. tomlBuildDir .. " --target clean"
	}

	usage "PUBLIC"
		includedirs { }

return module
