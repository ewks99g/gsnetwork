package.cpath=package.cpath..";luaclib/?.so"
local mathlib = require "game_math_lib"
assert(mathlib)

local modulename = ...  --filename's prefix such as takplace.lua

function getMaxLevNum(valI,valII)
	--print("valis"..valI..valII)
end

function addNumber(a,b)
return mathlib.add_two_num(a,b)					--defined through func lib
end

function test_c_lib(v1,v2)
end
