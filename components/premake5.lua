local components = {}

components.graphics = include("graphics")
components.audio = include("audio")

function components.runCodegen()
	components.graphics.runCodegen()
	components.audio.runCodegen()
end

function components.setupProjects()
	components.graphics.setupProjects()
	components.audio.setupProjects()
end

function components.applyUses()
	components.graphics.applyUses()
	components.audio.applyUses()
end

function components.setupExternal()
	components.graphics.setupExternal()
	components.audio.setupExternal()
end

return components
