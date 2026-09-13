local module = {}

local cmake = require("cmake")
local utils = dofile("../utils.lua")

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "assimp")

module.buildArgs = table.concat({
	"",
	"-DASSIMP_BUILD_ZLIB='ON'",
	"-DASSIMP_BUILD_TESTS='OFF'",
	"-DASSIMP_INSTALL='OFF'",
	""
}, " ")

function module.use()
	if utils.isVS() then
		local toLink = os.matchfiles(
			path.join(_MAIN_SCRIPT_DIR, "bin/*/assimp*.lib")
		)
		
		if #toLink == 0 then
			print("[INFO] Be sure to rerun the command to link properly!")
		end
		
		for _, v in pairs(toLink) do
			links { v }
		end
	else
		links { "assimp" }
	end

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
		"cmake " .. cmake.getOutputArgs() .. module.buildArgs .. "-S " .. assimpSrcDir .. " -B " .. assimpBuildDir,
		"cmake --build " .. assimpBuildDir
	}

	if utils.isVS() then
		buildcommands {
			"{COPYFILE} " .. path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}/%{cfg.buildcfg}/*") .. " " ..
				path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}")
		}
	end

	cmake.setupBuildCleanup(module.libPath)

	usage "PUBLIC"
		includedirs {}

return module
