local module = {}

module.libPath = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "glm") 

function module.use()
	includedirs { module.libPath }
	dependson { "GLMBuild" }
	uses { "GLMBuild" }
end

function module.setupExternal()
	externalproject("GLMBuild")
	kind "Makefile"
	location(module.libPath)
	uuid(os.uuid("GLMBuild"))
end

project("GLMBuild")
	kind "Makefile"
	location(module.libPath)

	buildcommands {

	}

	cleancommands {

	}

	usage "PUBLIC"
		defines { "GLM_ENABLE_EXPERIMENTAL" }

return module
