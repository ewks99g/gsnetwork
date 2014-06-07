local simplefunctionset = {}

simplefunctionset.add = function(x,y) return x + y end
simplefunctionset.sub = function(x,y) return x - y end
simplefunctionset.multi = function(x,y) return x * y end
simplefunctionset.devide = function(x,y) return x/y end

function simplefunctionset.multi_add(x,y,z)
	local func = function() return x + y + z end  ----this function can share the multi_add's env
	return func()
end

return simplefunctionset
