local components = {}

components.graphics = include("graphics")

function components.runCodegen()
	components.graphics.runCodegen()
end

function components.setupProjects()
	components.graphics.setupProjects()
end

function components.applyUses()
	components.graphics.applyUses()
end

function components.setupExternal()
	components.graphics.setupExternal()
end

return components
