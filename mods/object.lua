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
	self.Hp			= 100
	self.PhyAttack	= 10
	self.Dead		= false
end

function M:GetPos()
	return self.Pos
end

function M:GetName()
	return self.Name
end

function M:IsDead()
	return self.Dead
end

function M:ChangeHp(v)
	if not self:IsDead() then
		self.Hp = self.Hp + v
	end
end


function M:Run()
	if self.Dead then
		return
	end
	
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
			if math.random(1,100)<50 and objs[1]~=nil then
				self:OnSkill(dir,self.Pos-self.Speed,objs[1])
			else
				utils.Log("|%s| 向左移动碰到%s, 停止移动", self.Name,objs_name)
			end
			
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
			if math.random(1,100)<50 and objs[1]~=nil then
				self:OnSkill(dir,self.Pos+self.Speed,objs[1])
			else
				utils.Log("|%s| 向右移动碰到%s, 停止移动", self.Name,objs_name)
			end
			return true
		end
		self.Pos = self.Pos + self.Speed
		utils.Log("|%s| 向右移动到 %d", self.Name,self.Pos)
	end
	return false
end

function M:OnSkill(dir,new_pos,target)
	-- 靠近对方时, 使用技能, 冲撞一下, 之后, 对方位置(可能)后退
	-- 下一步移动时发生碰撞, 才能使用这个技能
	-- 自己移动, 目标移动
	if dir < 0 then
		-- 向左
		local objs,ret = self.Battle:Collide(target,new_pos-self.Width)
		if ret then
			-- 对方不能移动, 贴近他	
			self:ChangeHp(-5)
			target:ChangeHp(-5)
			self.Pos = target.Pos + target.Width
			utils.Log("|%s| 碰撞攻击后 向左移动到 %d", self.Name,self.Pos)
			return
		end
		
		self:ChangeHp(2)
		target:ChangeHp(-8)
		target.Pos = new_pos-self.Width
		utils.Log("|%s| 被攻击后退 向左移动到 %d", target.Name,target.Pos)
	else
		-- 向右
		local objs,ret = self.Battle:Collide(target,new_pos+self.Width)
		if ret then
			-- 对方不能移动, 贴近他	
			self:ChangeHp(-5)
			target:ChangeHp(-5)
			self.Pos = target.Pos - self.Width
			utils.Log("|%s| 碰撞攻击后 向右移动到 %d", self.Name,self.Pos)
			return
		end
		
		self:ChangeHp(2)
		target:ChangeHp(-8)
		target.Pos = new_pos+self.Width
		utils.Log("|%s| 被攻击后退 向右移动到 %d", target.Name,target.Pos)
	end
end
 
return utils.Class(M)
