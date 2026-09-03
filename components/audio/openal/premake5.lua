local module = {}

local cmake = dofile("../../../libs/cmake.lua")
local utils = dofile("../../../utils.lua")

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "openal")

module.buildArgs = table.concat({
	"",
	"-Wno-author",
	"-DALSOFT_EXAMPLES='OFF'",
	"-DALSOFT_UTILS='OFF'",
	"-DALSOFT_INSTALL='OFF'",
	""
}, " ")

function module.runCodegen(includeSection, entrySection)
	if includeSection == nil or type(includeSection) ~= "table" then
		print("[FATAL] Failed to do codegen for OpenAL, includeSection is not codegen")
		os.exit(1, true)
	end
	if entrySection == nil or type(entrySection) ~= "table" then
		print("[FATAL] Failed to do codegen for OpenAL, entrySection is not codegen")
		os.exit(1, true)
	end


end

function module.use()
	if not module.enabled then
		print("[WARN] Cannot use OpenAL, --disable-openal was passed")
		return
	end

	files {
		path.getrelative(path.getdirectory(_SCRIPT), path.join(path.getdirectory(module.libPath), "*.cpp"))
	}

	includedirs {
		path.join(module.libPath, "include"),
		path.getdirectory(module.libPath)
	}
	dependson { "OpenALBuild" }
	uses { "OpenALBuild" }

	if utils.isVS() then
		links { "OpenAL32", "alsoft.common" }
	else
		links { "openal" }
	end
end

function module.setupProject()
	local OpenALBuildSrcDir = module.libPath
	local OpenALBuildDir = path.join(module.libPath, "build")

	project("OpenALBuild")
		kind("Makefile")
		location(module.libPath)
		targetdir "bin/%{cfg.buildcfg}"

		buildcommands {
			"{MKDIR} " .. OpenALBuildDir,
			"cmake " .. cmake.getOutputArgs() .. module.buildArgs .. " -S " .. OpenALBuildSrcDir .. " -B " .. OpenALBuildDir,
			"cmake --build " .. OpenALBuildDir
		}

		cmake.setupBuildCleanup(module.libPath)

		usage "PUBLIC"
			includedirs {}
end

function module.setupExternal()
	externalproject("OpenALBuild")
	location(module.libPath)
	uuid(os.uuid("OpenALBuild"))
	kind("Makefile")
end

return module
