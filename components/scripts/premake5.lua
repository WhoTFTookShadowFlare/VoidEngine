local module = {}

local codegen = dofile("../../codegen.lua")

module.components = {}

for _, v in pairs(os.matchdirs(
	path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "*")
)) do
	local scriptModuleName = path.getname(v)
	local scriptModule = include(v)
	module.components[scriptModuleName] = scriptModule

	scriptModule.enabled = true
	if _OPTIONS["disable-" .. scriptModuleName] then
		scriptModule.enabled = false
	end

	newoption {
		trigger = "disable-" .. scriptModuleName,
		description = "Weather " .. scriptModuleName .. " is disabled",
		category = "Components/Scripts",
	}
end

local currentScript = _SCRIPT
function module.runCodegen()
    local targetFile = path.join(path.getabsolute(path.getdirectory(currentScript)), "../../generated/script_engine_load_order.hpp")
	os.mkdir(path.getdirectory(targetFile))
	os.touchfile(targetFile)

	local output = codegen.new()
	output.prefixWrap = "// This file is auto generated, use 'premake codegen' to modify this file.\n\n"
	output:addStringPart("#pragma once")
	output:addStringPart("#include <vector>")
	output:addStringPart("#include <functional>")
	output:addStringPart("#include <memory>")
	output:addStringPart("#include <ve/script/a_script_engine.hpp>")

	local includeSection = output:addCodegenPart()
	includeSection.stringEntryPrefix = "#include <"
	includeSection.stringEntrySuffix = ">\n"

	output:addStringPart("namespace VoidEngine::Scripts {")
	output:addStringPart("\t::std::vector<::std::function<::std::shared_ptr<AScriptEngine>()>> engineLoaders = {")

	local entrySection = output:addCodegenPart()
	entrySection.stringEntryPrefix = "\t\t[]() { return "
	entrySection.stringEntrySuffix = "::getInstance(); },\n"

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
			v.use()
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