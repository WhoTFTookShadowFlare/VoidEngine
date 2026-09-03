local module = {}

function module.isVS()
	return string.find(tostring(_ACTION), "vs")
end

function module.isGMake()
	return string.find(tostring(_ACTION), "gmake")
end

-- TODO: Find out codelite output antics that need to be done.
function module.isCodeLite()
	return string.find(tostring(_ACTION), "codelite")
end

-- TODO: Find out xcode output antics that need to be done.
function module.isXCode()
	return string.find(tostring(_ACTION), "xcode")
end

return module