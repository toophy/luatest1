local M = {}

--lua������󣺸��������ϵ�ʵ��
local _class={}

function class(super)
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



-- ���ڣ�������������ôʹ�ã�
base_type=class()		-- ����һ������ base_type

function base_type:ctor(x)	-- ���� base_type �Ĺ��캯��
	print("base_type ctor")
	self.x=x
end

function base_type:print_x()	-- ����һ����Ա���� base_type:print_x
	print(self.x)
end

function base_type:hello()	-- ������һ����Ա���� base_type:hello
	print("hello base_type")
end

-- �����ǻ����� class ������﷨����ȫ���� lua �ı��ϰ�ߡ���������һ������ ctor �Ĵʣ���Ϊ���캯�������֡�
-- ���濴�������̳У�
test=class(base_type)	-- ����һ���� test �̳��� base_type

function test:ctor()	-- ���� test �Ĺ��캯��
	print("test ctor")
end

function test:hello()	-- ���� base_type:hello Ϊ test:hello
	print("hello test")
end

-- ���ڿ�����һ���ˣ�
a=test.new(1)	-- ������У�base_type ctor �� test ctor �����������ȷ�Ĺ����ˡ�
a:print_x()	-- ��� 1 ������ǻ��� base_type �еĳ�Ա������
a:hello()	-- ��� hello test ����������������ˡ�

M.TablePlus = require("utils.TablePlus")
M.Class = class

return M
