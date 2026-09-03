local module = {}

local cmake = require("cmake")

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "toml++")

module.buildArgs = table.concat({
	"",
	""
}, " ")

function module.use()
	includedirs { path.join(module.libPath, "include") }
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
	targetdir "bin/%{cfg.buildcfg}"

	buildcommands {
		"{MKDIR} " .. tomlBuildDir,
		"cmake " .. module.buildArgs .. cmake.getOutputArgs() .. "-S " .. tomlSrcDir .. " -B " .. tomlBuildDir,
		"cmake --build " .. tomlBuildDir
	}

	cmake.setupBuildCleanup(module.libPath)

	usage "PUBLIC"
		includedirs { }

return module
