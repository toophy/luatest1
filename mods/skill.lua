local utils = require("utils")

local M = utils.Class()

function M:ctor()
end

function M:Check(id)
	utils.Log("检查技能%d",id)
	return true
end

function M:Use(id)
	utils.Log("使用技能%d",id)
	return true
end

return utils.Class(M)
