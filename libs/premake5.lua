local module = {}

module.glm = require("glm")
module.stb = require("stb")
module.sdl3 = require("sdl3")
module.assimp = require("assimp")
module.toml = require("toml")

function module.setupExternal()
	module.glm.setupExternal()
	module.stb.setupExternal()
	module.sdl3.setupExternal()
	module.assimp.setupExternal()
	module.toml.setupExternal()
end

return module
