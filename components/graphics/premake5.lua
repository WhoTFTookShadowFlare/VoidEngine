local module = {}

local codegen = dofile("../../codegen.lua")

module.components = {}

for _, v in pairs(os.matchdirs(
	path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "*")
)) do
	local gfxModuleName = path.getname(v)
	local gfxModule = include(v)
	module.components[gfxModuleName] = gfxModule

	gfxModule.enabled = true
	if _OPTIONS["disable-" .. gfxModuleName] then
		local str2Bool = { ["true"] = true, ["false"] = false }
		gfxModule.enabled = str2Bool[_OPTIONS["disable-" .. gfxModuleName]] or false
	end

	newoption {
		trigger = "disable-" .. gfxModuleName,
		description = "Weather " .. gfxModuleName .. " is enabled",
		category = "Components/GFX",
	}
end


local currentScript = _SCRIPT
function module.runCodegen()
	local targetFile = path.join(path.getabsolute(path.getdirectory(currentScript)), "../../generated/graphics_load_order.hpp")
	os.mkdir(path.getdirectory(targetFile))
	os.touchfile(targetFile)

	local output = codegen.new()
	output.prefixWrap = "// This file is auto generated, use 'premake codegen' to modify this file.\n\n"
	output:addStringPart("#pragma once")
	output:addStringPart("#include <vector>")
	output:addStringPart("#include <functional>")

	local includeSection = output:addCodegenPart()
	includeSection.stringEntryPrefix = "#include <"
	includeSection.stringEntrySuffix = ">\n"

	output:addStringPart("namespace VoidEngine::IO::GFX {")
	output:addStringPart("\t::std::vector<std::function<ARendererBackend*()>> backendLoaders = {")

	local entrySection = output:addCodegenPart()
	entrySection.stringEntryPrefix = "\t\t[]() { return new "
	entrySection.stringEntrySuffix = "; },\n"

	output:addStringPart("\t\t[]() { return new ::VoidEngine::IO::GFX::Dummy::DummyBackend; }")
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
