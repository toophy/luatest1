
local info = debug.getinfo(1, "S") -- 第二个参数 "S" 表示仅返回 source,short_src等字段， 其他还可以 "n", "f", "I", "L"等 返回不同的字段信息
local path = info.source
path = string.sub(path, 2, -1) -- 去掉开头的"@"
path = string.match(path, "^.*\\") -- 捕获最后一个 "/" 之前的部分 就是我们最终要的目录部分


package.path = path .. "?/init.lua" .. package.path

local skill = require("mods.skill")
local utils = require("utils")



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
	     __index = function(mytable, key)
		if key == "key2" then
		  return "metatablevalue"
		else
		  return nil
		end
	end
	})

print(mytable.key1,mytable.key2,mytable.key3)

print(utils.TablePlus.toTreeString(mytable))

print(package.path)