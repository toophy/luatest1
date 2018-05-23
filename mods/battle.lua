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
	if math.random()<0.2 then
		self:CreateObject(string.format("%d",self.ObjectCount),2,1)
	end
	for i,v in ipairs(self.Objects) do
		self.Objects[i]:Run()
	end
end

function M:CreateObject(nam,pos,dir)
	local newObj = utils.Class(object)
    newObj:new(self,nam,pos,dir,self.ObjWidth)
	table.insert(self.Objects,newObj)
	self.ObjectCount = self.ObjectCount + 1
end

function M:DestroyObject(nam)
	for i,v in ipairs(self.Objects) do
		if self.Objects[i].Name == nam then
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
	if pos<0 or pos>self.Width then
		return objs
	end
	
	for i,v in ipairs(self.Objects) do
		if self.Objects[i]~=obj then
			if not (pos > self.Objects[i]:GetPos()+self.ObjWidth or
				self.Objects[i]:GetPos()>pos+self.ObjWidth) then
				table.insert(objs,self.Objects[i])
			end
		end
	end
	
	return objs
end

return M
