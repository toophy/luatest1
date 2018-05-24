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

function M:GetPos()
	return self.Pos
end

function M:GetName()
	return self.Name
end

function M:Run()
	local status = math.random(1,100)
	if status<10 then
		self.Battle:MoveObj(self,-1)
	elseif status<30 then
		self.Battle:MoveObj(self,1)
	end
end

function M:OnMove(dir)
	if dir < 0 then
		local objs,ret = self.Battle:Collide(self,self.Pos-self.Speed)
		if ret then
			local objs_name = ""
			for i,v in ipairs(objs) do
				objs_name = objs[i]:GetName() .. ","				
			end
			utils.Log("|%s| 向左移动碰到%s, 停止移动", self.Name,objs_name)
			return true
		end
		self.Pos = self.Pos - self.Speed
		utils.Log("|%s| 向左移动到 %d", self.Name,self.Pos)
	else
		local objs,ret = self.Battle:Collide(self,self.Pos+self.Speed)
		if ret then
			local objs_name = ""
			for i,v in ipairs(objs) do
				objs_name = objs[i]:GetName() .. ","				
			end
			utils.Log("|%s| 向右移动碰到%s, 停止移动", self.Name,objs_name)
			return true
		end
		self.Pos = self.Pos + self.Speed
		utils.Log("|%s| 向右移动到 %d", self.Name,self.Pos)
	end
	return false
end
 
return utils.Class(M)
