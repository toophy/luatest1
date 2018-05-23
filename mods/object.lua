local utils = require("utils")

local M = utils.Class()

function M:ctor(battle,nam,pos,dir,width,startFrame)
	self.Battle		= battle
	self.Name		= nam
	self.Pos		= pos
	self.Dir		= dir
	self.Width		= width
	self.StartFrame = startFrame
	self.Speed		= 3	
end

function M:Run()
	local status = math.random()
	if status<0.1 then
		self.Battle:MoveObj(-1)
	elseif status<0.3 then
		self.Battle:MoveObj(1)
	end
end

function M:OnMove(dir)
	if dir < 0 then
		local objs = self.Battle:Collide(self,self.Pos-self.Speed)
		if table.maxn(objs)>0  then
			return true
		end
		self.Pos = self.Pos - self.Speed
	else
		local objs = self.Battle:Collide(self,self.Pos+self.Speed)
		if table.maxn(objs)>0  then
			return true
		end
		self.Pos = self.Pos + self.Speed
	end
	return false
end

return M
