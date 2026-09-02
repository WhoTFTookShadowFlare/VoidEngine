local module = {}

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "stb")

function module.use()
	includedirs { module.libPath }
	dependson { "STBBuild" }
end

function module.setupExternal()
	externalproject("STBBuild")
	kind "Makefile"
	location(module.libPath)
	uuid(os.uuid("STBBuild"))
end

project("STBBuild")
	kind "Makefile"
	location(module.libPath)
	targetdir "bin/%{cfg.buildcfg}"

	buildcommands {

	}

	cleancommands {

	}

return module
