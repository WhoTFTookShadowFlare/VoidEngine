local components = {}

components.graphics = include("graphics")
components.audio = include("audio")
components.scripts = include("scripts")

function components.runCodegen()
	components.graphics.runCodegen()
	components.audio.runCodegen()
	components.scripts.runCodegen()
end

function components.setupProjects()
	components.graphics.setupProjects()
	components.audio.setupProjects()
	components.scripts.setupProjects()
end

function components.applyUses()
	components.graphics.applyUses()
	components.audio.applyUses()
	components.scripts.applyUses()
end

function components.setupExternal()
	components.graphics.setupExternal()
	components.audio.setupExternal()
	components.scripts.setupExternal()
end

return components
