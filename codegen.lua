local codegen = {}
codegen.__index = codegen

codegen.generatedPathPrefix = path.join(path.getdirectory(path.getabsolute(_SCRIPT)), "generated")

function codegen.new()
	local self = {}
	self.parts = {}
	self.prefixWrap = ""
	self.suffixWrap = ""
	self.stringEntryPrefix = ""
	self.stringEntrySuffix = "\n"
	return setmetatable(self, codegen)
end

function codegen:addStringPart(text)
	self.parts[#self.parts+1] = text
end

function codegen:addCodegenPart()
	local part = codegen:new()
	self.parts[#self.parts+1] = part
	return part
end

function codegen:getGeneratedResult()
	local generated = self.prefixWrap

	for _, v in pairs(self.parts) do
		if type(v) == "string" then
			generated = generated .. self.stringEntryPrefix .. v .. self.stringEntrySuffix
		elseif type(v) == "table" and getmetatable(v) == codegen then
			generated = generated .. v:getGeneratedResult()
		else
			print("[WARN] Unknown type in codegen " .. type(v))
		end
	end

	return generated .. self.suffixWrap
end

function codegen:write(fileName)
	io.writefile(fileName, self:getGeneratedResult())
end

return codegen
