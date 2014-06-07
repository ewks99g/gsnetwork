--implement one simple actor 

actor = {x=0,y=0}

actor.__index = actor

function actor:new(x,y)
	local self = {}
	setmetatable(self,actor)
	self.x = x
	self.y = y
	return self
end

function actor:printpos()
	print(self.x,self.y)
end

function actor:plus()
	self.x = self.x + 1
	self.y = self.y + 1
end

-------------------------------------------------------------------
--implement son class 
player = {sex = 0}
setmetatable(player,actor)
player.__index = player

function player:new(x,y,sex)
	local self = actor:new(x,y)
	setmetatable(self,player)
	self.sex = sex
	return self
end

function player:getsex()
	return self.sex
end

function player:printpos()
	print(self.x,self.y)
end
-------------------------------------------------------------------
