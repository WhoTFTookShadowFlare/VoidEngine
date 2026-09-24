local module = {}

module.libPath = path.join(path.getdirectory(_SCRIPT), "box2d")

function module.runCodegen(includeSection, entrySection)
    if includeSection == nil or type(includeSection) ~= "table" then
		print("[FATAL] Failed to do codegen for OpenGL, includeSection is not codegen")
		os.exit(1, true)
	end
	if entrySection == nil or type(entrySection) ~= "table" then
		print("[FATAL] Failed to do codegen for OpenGL, entrySection is not a codegen")
		os.exit(1, true)
	end

    includeSection:addStringPart("box2d_engine.hpp")
    entrySection:addStringPart("::VoidEngine::Physics2D::Box2D::Box2DEngine")
end

function module.setupProject()
    project "Box2D"
        kind "SharedLib"
        language "C"
        cdialect "C17"
        location(module.libPath)
		targetdir(path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}"))
        objdir(path.join(_MAIN_SCRIPT_DIR, "obj/%{cfg.platform}/%{cfg.buildcfg}"))

        filter "platforms:Windows"
            links { "kernel32" }
            defines { "BOX2D_EXPORT=__declspec(dllexport)" }
        filter "platforms:not Windows"
            links { "m" }
        filter {}

        files { path.join(module.libPath, "src/**.c") }

        includedirs { path.join(module.libPath, "include") }
end

function module.applyUses()
    includedirs { path.join(module.libPath, "include") }
    links { "Box2D" }

    includedirs { path.getdirectory(module.libPath) }
    files { path.join(path.getdirectory(module.libPath), "**.cpp") }
    removefiles { path.join(module.libPath, "**.cpp") }
end

function module.setupExternal()
    externalproject "Box2D"
        kind "SharedLib"
        location(module.libPath)
        uuid(os.uuid("Box2D"))
        targetdir(path.join(_MAIN_SCRIPT_DIR, "bin/%{cfg.buildcfg}"))
end

return module