local LibBinPath = path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}/libs")

local CMakeBuildType = ""
if _ACTION == "gmake" then
	CMakeBuildType = "Unix Makefiles"
elseif _ACTION == "vs2019" then
	CMakeBuildType = "Visual Studio 16 2019"
else
	print("Action " .. _ACTION .. " is currently not supported (see VELibs.lua line " .. debug.getinfo(1).currentline .. ")")
end

local function externCMakeProject(LibName, CMakeListsPath, CMakeTarget, CompilerArgs)
	CompilerArgs = CompilerArgs or ""

	local buildCmdList = {
		"{MKDIR} " .. path.join(LibBinPath, LibName),
		"cmake -B\"" .. path.join(LibBinPath, LibName) .. "\" -H\"" .. CMakeListsPath .. "\" -G \"" .. CMakeBuildType .. "\" "
		.. "-DCMAKE_CXX_FLAGS=\"" .. CompilerArgs .. "\"",
		"{CHDIR} " .. path.join(LibBinPath, LibName),
		"cmake --build " .. path.join(LibBinPath, LibName) .. " --target " .. CMakeTarget .. " --parallel " .. os.getnumcpus(),

		"{COPYFILE} " .. path.join(path.join(LibBinPath, LibName), "lib*.so*") .. " bin/%{cfg.buildcfg}",
		"{COPYFILE} " .. path.join(path.join(LibBinPath, LibName), "*.dll") .. " bin/%{cfg.buildcfg}"
	}

	project(LibName)
		kind "Makefile"

		buildcommands(buildCmdList)
		rebuildcommands(buildCmdList)

		cleancommands {
			"{RMDIR} " .. path.join(LibBinPath, LibName)
		}

		usage "PUBLIC"
			links(LibName)
			libdirs { path.join(LibBinPath, LibName) }
end

externCMakeProject("SDL3", "SDL", "SDL3-shared")
	usage "PUBLIC"
		includedirs { "SDL/include" }

externCMakeProject("glbinding", "glbinding", "glbinding")
	usage "PUBLIC"
		includedirs {
			"glbinding/source/glbinding-aux/include",
			"glbinding/source/glbinding/include",
			"glbinding/source/3rdparty/KHR/include",
			path.join(LibBinPath, "glbinding/source/include"),
			path.join(LibBinPath, "glbinding/source/glbinding-aux/include"),
			path.join(LibBinPath, "glbinding/source/glbinding/include")
		}

