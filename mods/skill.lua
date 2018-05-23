local utils = require("utils")

local M = utils.Class()

function M:ctor()
end

function M:Check(id)
	print( string.format("检查技能%d",id) )
	return true
end

function M:Use(id)
	-- print( string.format("使用技能%d",id) )
	return true
end

return M


--[[
local skill = require("mods.skill")

function UseSkill(id)
	print("使用技能",id)
end

function PrintTable(fn)
	tab1 = {key="key1",val="val1","xxx"}
	for k,v in pairs( tab1) do
		fn(v)
	end
end

PrintTable(UseSkill)

local s,e = string.find("ww.lucid.com", "luc")
print(s,e)
print(string.gsub("zzzz", "z", "a",2))

print(skill.Check(2))

mytable = setmetatable({key1 = "value1"}, {
__index = function (mytable, key)
	if key == "key2" then
		return "metatablevalue"
	else
		return nil
	end
end
})

print(mytable.key1,mytable.key2,mytable.key3)
print(utils.TablePlus.toTreeString(mytable))
--]]
