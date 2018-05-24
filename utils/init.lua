local M = {}

--lua������󣺸��������ϵ�ʵ��
local _class={}

local function class(super)
	local class_type={}
	--ע�⣺��Ϊ������__newindex����, ����ctor��Ҫ����Ϊnil
	class_type.ctor=false
	class_type.super=super
	class_type.new=function (...)
		local obj={}
		--����Ŀ�ֻ����һ���£����δӸ��ൽ��ǰ������ù��캯��ctor
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
	
	--�¼ӳ�Ա����ֹ��������ú���
	local vtbl={}
	_class[class_type]=vtbl
	
	setmetatable(class_type,{__newindex=
	function (t,k,v)
		vtbl[k]=v
	end
	})
	
	--ֻ�ж������޸���__newindex
	--vbtlֻ���ڶ�����
	--new�����Ķ��������ж���������ã��������Լ������ӵĳ�Ա����
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
