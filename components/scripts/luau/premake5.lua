local module = {}

local codegen = dofile("../../../codegen.lua")
local cmake = dofile("../../../libs/cmake.lua")
local utils = dofile("../../../utils.lua")

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "luau")

module.buildArgs = table.concat({
	"",
	"-Wno-author",
	""
}, " ")

function module.runCodegen(includeSection, entrySection)

end

function module.setupProject()
    local luauSrcDir = module.libPath
    local luauBuildDir = path.join(module.libPath, "build")

    project "LuauBuild"
        kind "Makefile"
        location(module.libPath)
        targetdir "bin/%{cfg.buildcfg}"

        buildcommands {
            "{MKDIR} " .. luauBuildDir,
            "cmake " .. cmake.getOutputArgs() .. module.buildArgs .. " -S " .. luauSrcDir .. " -B " .. luauBuildDir,
            "cmake --build " .. luauBuildDir .. " --target help",
        }

        cmake.setupBuildCleanup(module.libPath)
end

function module.use()
    if not module.enabled then
        print("[WARN] Cannot use luau, --disable luau was passed")
        return
    end

    includedirs {
        path.getdirectory(module.libPath)
    }

    dependson { "LuauBuild" }
    uses { "LuauBuild" }

    local basePath = path.getrelative(path.getdirectory(_SCRIPT), path.join(path.getdirectory(module.libPath)))
    files {
        path.join(basePath, "*.cpp"),
        path.join(basePath, "types/*.cpp")
    }
end

function module.setupExternal()
    externalproject "LuauBuild"
    location(module.libPath)
	uuid(os.uuid("LuauBuild"))
	kind("Makefile")
end

return module