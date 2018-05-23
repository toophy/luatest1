local utils = require("utils")
local socket = require("socket")
local skill = require("mods.skill")
local battle = require("mods.battle")

local M = utils.Class()

function M:ctor()
	self.count = 0
	self.Battles = {}
end

function M:Run()
	self:CreateBattle("´óÌü", 1000)
	while true do
		self.count = self.count + 1
		self:OnFrame()
		socket.select(nil, nil, 1)
	end
end

function M:OnFrame()
	for i,v in ipairs(self.Battles) do
		self.Battles[i]:Run()	
	end
end

function M:CreateBattle(nam,width)
	local newBattleClass = utils.Class(battle)
	local newBattle = newBattleClass.new(self,nam,width)
	table.insert(self.Battles,newBattle)
	return newBattle
end

return M
