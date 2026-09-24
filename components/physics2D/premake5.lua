local module = {}

local codegen = dofile("../../codegen.lua")

module.components = {}

for _, v in pairs(os.matchdirs(
	path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "*")
)) do
	local physModuleName = path.getname(v)
	local physModule = include(v)
	module.components[physModuleName] = physModule

	physModule.enabled = true
	if _OPTIONS["disable-" .. physModuleName] then
		physModule.enabled = false
	end

	newoption {
		trigger = "disable-" .. physModuleName,
		description = "Weather " .. physModuleName .. " is disabled",
		category = "Components/Physics2D",
	}
end

local currentScript = _SCRIPT
function module.runCodegen()
    local targetFile = path.join(path.getabsolute(path.getdirectory(currentScript)), "../../generated/physics2d_load_order.hpp")
	os.mkdir(path.getdirectory(targetFile))
	os.touchfile(targetFile)

	local output = codegen.new()
	output.prefixWrap = "// This file is auto generated, use 'premake codegen' to modify this file.\n\n"
	output:addStringPart("#pragma once")
	output:addStringPart("#include <vector>")
	output:addStringPart("#include <functional>")
	output:addStringPart("#include <ve/physics2d/a_2d_physics_engine.hpp>")

	local includeSection = output:addCodegenPart()
	includeSection.stringEntryPrefix = "#include <"
	includeSection.stringEntrySuffix = ">\n"

	output:addStringPart("namespace VoidEngine::Physics2D {")
	output:addStringPart("\t::std::vector<::std::function<A2DPhysicsEngine*()>> engineLoaders = {")

	local entrySection = output:addCodegenPart()
	entrySection.stringEntryPrefix = "\t\t[]() { return new "
	entrySection.stringEntrySuffix = "; },\n"

	output:addStringPart("\t};")
	output:addStringPart("}")

	for _, v in pairs(module.components) do
		if v.enabled then
			v.runCodegen(includeSection, entrySection)
		end
	end

	output:write(targetFile)
end

function module.setupProjects()
    for _, v in pairs(module.components) do
        if v.enabled then
            v.setupProject()
        end
    end
end

function module.applyUses()
    for _, v in pairs(module.components) do
        if v.enabled then
            v.applyUses()
        end
    end
end

function module.setupExternal()
    for _, v in pairs(module.components) do
        if v.enabled then
            v.setupExternal()
        end
    end
end

return module