package.cpath=package.cpath..";luaclib/?.so"
local mytestlib = require "mytestlib"
assert(mytestlib)
local modulename = ...  --filename's prefix such as takplace.lua

function getMaxLevNum(valI,valII)
	--print("valis"..valI..valII)
end

G_width=30
G_height=40

function addNumber(a,b)
--	return add_two_int(a,b)			--defined through func register
	return mytestlib.add(a,b)					--defined through func lib
end

function test_c_lib(v1,v2)
end
