local components = {}

components.graphics = include("graphics")
components.audio = include("audio")
components.physics2D = include("physics2D")
components.scripts = include("scripts")

function components.runCodegen()
	components.graphics.runCodegen()
	components.audio.runCodegen()
	components.physics2D.runCodegen()
	components.scripts.runCodegen()
end

function components.setupProjects()
	components.graphics.setupProjects()
	components.audio.setupProjects()
	components.physics2D.setupProjects()
	components.scripts.setupProjects()
end

function components.applyUses()
	components.graphics.applyUses()
	components.audio.applyUses()
	components.physics2D.applyUses()
	components.scripts.applyUses()
end

function components.setupExternal()
	components.graphics.setupExternal()
	components.audio.setupExternal()
	components.physics2D.setupExternal()
	components.scripts.setupExternal()
end

return components
