local module = {}

local cmake = require("cmake")

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "assimp")

module.buildArgs = table.concat({
	"",
	"-DASSIMP_BUILD_ZLIB='ON'",
	"-DASSIMP_BUILD_TESTS='OFF'",
	"-DASSIMP_INSTALL='OFF'",
	""
}, " ")

function module.use()
	links { "assimp" }
	includedirs {
		path.join(module.libPath, "include"),
		path.join(module.libPath, "build/include")
	}
	dependson { "AssimpBuild" }
	uses { "AssimpBuild" }
end

function module.setupExternal()
	externalproject("AssimpBuild")
	kind "Makefile"
	location(module.libPath)
	uuid(os.uuid("AssimpBuild"))
end

local assimpSrcDir = module.libPath
local assimpBuildDir = path.join(module.libPath, "build")

project("AssimpBuild")
	kind "Makefile"
	location(module.libPath)
	targetdir "bin/%{cfg.buildcfg}"

	buildcommands {
		"{MKDIR} " .. assimpBuildDir,
		"cmake " .. module.buildArgs .. cmake.outputArgs .. "-S " .. assimpSrcDir .. " -B " .. assimpBuildDir,
		"cmake --build " .. assimpBuildDir
	}

	cleancommands {
		"cmake --build " .. assimpBuildDir .. " --target clean"
	}

	usage "PUBLIC"
		includedirs {}

return module
