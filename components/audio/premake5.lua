local module = {}

local codegen = dofile("../../codegen.lua")

module.components = {}

for _, v in pairs(os.matchdirs(
	path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "*")
)) do
	local auxModuleName = path.getname(v)
	local auxModule = include(v)
	module.components[auxModuleName] = auxModule

	auxModule.enabled = true
	if _OPTIONS["disable-" .. auxModuleName] then
		auxModule.enabled = false
	end

	newoption {
		trigger = "disable-" .. auxModuleName,
		description = "Weather " .. auxModuleName .. " is disabled",
		category = "Components/AUX"
	}
end

local currentScript = _SCRIPT
function module.runCodegen()
	local targetFile = path.join(path.getabsolute(path.getdirectory(currentScript)), "../../generated/audio_load_order.hpp")
	os.mkdir(path.getdirectory(targetFile))
	os.touchfile(targetFile)

	local output = codegen.new()
	output.prefixWrap = "// This file is auto generated, use 'premake codegne' to modify this file.\n\n"
	output:addStringPart("#pragma once")
	output:addStringPart("#include <vector>")
	output:addStringPart("#include <functional>")
	output:addStringPart("#include <ve/io/sfx/audio_backend.hpp>")
	output:addStringPart("#include <ve/io/sfx/dummy/backend_dummy.hpp>")

	local includeSection = output:addCodegenPart()
	includeSection.stringEntryPrefix = "#include <"
	includeSection.stringEntrySuffix = ">\n"

	output:addStringPart("namespace VoidEngine::IO::SFX {")
	output:addStringPart("\t::std::vector<std::function<AudioBackend*()> backendLoaders = {")
	
	local entrySection = output:addCodegenPart()
	entrySection.stringEntryPrefix = "\t\t[]() { return new "
	entrySection.stringEntrySuffix = "; },\n"

	output:addStringPart("\t\t[]() { return new ::VoidEngine::IO::SFX::Dummy::DummyBackend; }")
	output:addStringPart("\t};")
	output:addStringPart("}")

	for _, v in pairs(module.components) do
		if v.enabled then
			v.runCodegen(includeSection, entrySection)
		end
	end

	output:write(targetFile)
end

function module.applyUses()
	for _, v in pairs(module.components) do
		filter {}
		if v.enabled then
			v.use()
		end
	end
end

function module.setupProjects()
	for _, v in pairs(module.components) do
		if v.enabled then
			v.setupProject()
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
