local module = {}

local codegen = dofile("../../../codegen.lua")
local cmake = dofile("../../../libs/cmake.lua")
local utils = dofile("../../../utils.lua")

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "glbinding")

module.buildArgs = table.concat({
	"",
	"-Wno-author",
	"-DOPTION_BUILD_TOOLS='OFF'",
	"-DOPTION_BUILD_EXAMPLES='OFF'",
	"-DOPTION_BUILD_TESTS='OFF'",
	""
}, " ")

function module.runCodegen(includeSection, entrySection)
	if includeSection == nil or type(includeSection) ~= "table" then
		print("[FATAL] Failed to do codegen for OpenGL, includeSection is not codegen")
		os.exit(1, true)
	end
	if entrySection == nil or type(entrySection) ~= "table" then
		print("[FATAL] Failed to do codegen for OpenGL, entrySection is not a codegen")
		os.exit(1, true)
	end

	includeSection:addStringPart("backend_opengl.hpp")
	entrySection:addStringPart("::VoidEngine::IO::GFX::OpenGL::RendererOpenGL")
end

function module.use()
	if not module.enabled then
		print("[WARN] Cannot use OpenGL, --disable-opengl was passed")
		return
	end

	includedirs {
		path.join(module.libPath, "source/glbinding/include"),
		path.join(module.libPath, "source/glbinding-aux/include"),
		path.join(module.libPath, "source/3rdparty/KHR/include"),
		path.join(module.libPath, "build", "source/glbinding/include"),
		path.join(module.libPath, "build", "source/glbinding-aux/include"),
		path.join(module.libPath, "build", "source/include"),
		path.getdirectory(module.libPath)
	}
	dependson { "GLBindingBuild" }
	uses { "GLBindingBuild" }

	files {
		path.getrelative(path.getdirectory(_SCRIPT), path.join(path.getdirectory(module.libPath), "*.cpp"))
	}

	if utils.isVS() then
		filter "configurations:Debug"
			links { "glbindingd.lib", "glbinding-auxd" }
		filter "configurations:Release"
			links { "glbinding", "glbinding-aux" }
		filter {}
	else
		links { "glbinding", "glbinding-aux" }
	end
end

function module.setupProject()
	local GLBindingSrcDir = module.libPath
	local GLBindingBuildDir = path.join(module.libPath, "build")

	project("GLBindingBuild")
		kind("Makefile")
		location(module.libPath)
		targetdir "bin/%{cfg.buildcfg}"

		buildcommands {
			"{MKDIR} " .. GLBindingBuildDir,
			"cmake " .. cmake.getOutputArgs() .. module.buildArgs .. " -S " .. GLBindingSrcDir .. " -B " .. GLBindingBuildDir,
			"cmake --build " .. GLBindingBuildDir,
			"{MKDIR} " .. path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}")
		}

		-- this fucking library does not respect any options I throw at it.
		if utils.isVS() then
			filter "configurations:Debug"
				buildcommands {
					"{COPYFILE} " .. path.join(GLBindingBuildDir, "%{cfg.buildcfg}/*glbindingd.*") .. ' ' ..
						path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}"),
					"{COPYFILE} " .. path.join(GLBindingBuildDir, "%{cfg.buildcfg}/*glbinding-auxd.*") .. ' ' ..
						path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}")
				}
			filter "configurations:Release"
				buildcommands {
					"{COPYFILE} " .. path.join(GLBindingBuildDir, "%{cfg.buildcfg}/*glbinding.*") .. ' ' ..
						path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}"),
					"{COPYFILE} " .. path.join(GLBindingBuildDir, "%{cfg.buildcfg}/*glbinding-aux.*") .. ' ' ..
						path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}")
				}
			filter {}
		else
			buildcommands {
				"{COPYFILE} " .. path.join(GLBindingBuildDir, "*glbinding.*") .. ' ' ..
					path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}"),
				"{COPYFILE} " .. path.join(GLBindingBuildDir, "*glbinding-aux.*") .. ' ' ..
					path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}")
			}
		end

		cmake.setupBuildCleanup(module.libPath)

		usage "PUBLIC"
			libdirs { path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}") }

		
end

function module.setupExternal()
	externalproject("GLBindingBuild")
	location(module.libPath)
	uuid(os.uuid("GLBindingBuild"))
	kind("Makefile")
end

return module
