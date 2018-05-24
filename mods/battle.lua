local utils = require("utils")
local object = require("mods.object")

local M = utils.Class()

function M:ctor(frameSys,nam,width)
	self.Name		= nam
	self.Width		= width
	self.ObjWidth	= 20
	self.FrameSys	= frameSys
	self.Objects	= {}
	self.ObjectCount = 0
end

function M:Run()
	local rand = math.random(1,100)
	if rand<20 then
		for var = 1,10,1 do
			local pos = math.random(0,self.Width-self.ObjWidth-1)
			local objs,ret = self:Collide(nil,pos)
			if not ret then
				local dir = math.random(0,1)
				self:CreateObject(string.format("%d",self.ObjectCount),pos,dir)
				break
			end
		end
	end
	for i,v in ipairs(self.Objects) do
		self.Objects[i]:Run()
	end
end

function M:CreateObject(nam,pos,dir)
	local newObj     = object.new(self,nam,pos,dir,self.ObjWidth)
	table.insert(self.Objects,newObj)
	self.ObjectCount = self.ObjectCount + 1
	
	utils.Log("新建对象: %s", newObj.Name)
end

function M:DestroyObject(nam)
	for i,v in ipairs(self.Objects) do
		if self.Objects[i].Name == nam then
			utils.Log("摧毁对象: %s", nam)
			table.remove(self.Objects,i)
			self.ObjectCount = self.ObjectCount - 1
			break
		end
	end
end

function M:MoveObj(obj,dir)
	obj:OnMove(dir)
end

function M:Collide(obj,pos)
	local objs = {}
	local ret  = true
	if pos<0 or pos>self.Width then
		return objs,ret
	end
	
	ret = false
	for i,v in ipairs(self.Objects) do
		if self.Objects[i]~=obj then
			if not (pos > self.Objects[i]:GetPos()+self.ObjWidth or
				self.Objects[i]:GetPos()>pos+self.ObjWidth) then
				table.insert(objs,self.Objects[i])
				ret = true
			end
		end
	end
	
	return objs,ret
end

return utils.Class(M)
