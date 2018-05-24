local M = {}

--lua面向对象：概念意义上的实现
local _class={}

local function class(super)
	local class_type={}
	--注意：因为重载了__newindex函数, 所以ctor不要定义为nil
	class_type.ctor=false
	class_type.super=super
	class_type.new=function (...)
		local obj={}
		--下面的块只做了一件事：依次从父类到当前子类调用构造函数ctor
		do
			local create
			create = function (c,...)
				if c.super then
					create(c.super,...)
				end
				if c.ctor then
					c.ctor(obj,...)
				end
			end
			
			create(class_type,...)
		end
		setmetatable(obj,{ __index=_class[class_type] })
		return obj
	end
	
	--新加成员：防止定义类调用函数
	local vtbl={}
	_class[class_type]=vtbl
	
	setmetatable(class_type,{__newindex=
	function (t,k,v)
		vtbl[k]=v
	end
	})
	
	--只有定义类修改了__newindex
	--vbtl只属于定义类
	--new出来的对象共享所有定义类的引用，但独享自己新增加的成员变量
	if super then
		setmetatable(vtbl,{__index=
		function (t,k)
			local ret=_class[super][k]
			vtbl[k]=ret
			return ret
		end
		})
	end
	
	return class_type
end

local function log(fmt,...)
	local s = "[I]" .. string.format(fmt,...)
	print(s)
end

local function logWarn(fmt,...)
	local s = "[W]" .. string.format(fmt,...)
	print(s)
end

local function logError(fmt,...)
	local s = "[E]" .. string.format(fmt,...)
	print(s)
end

local function logFatal(fmt,...)
	local s = "[F]" .. string.format(fmt,...)
	print(s)
end


M.Class     = class
M.Log       = log
M.LogWarn   = logWarn
M.LogError  = logError
M.LogFatal  = logFatal
M.TablePlus = require("utils.TablePlus")

return M
