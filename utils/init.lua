local M = {}

--lua面向对象：概念意义上的实现
local _class={}

function class(super)
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



-- 现在，我们来看看怎么使用：
base_type=class()		-- 定义一个基类 base_type

function base_type:ctor(x)	-- 定义 base_type 的构造函数
	print("base_type ctor")
	self.x=x
end

function base_type:print_x()	-- 定义一个成员函数 base_type:print_x
	print(self.x)
end

function base_type:hello()	-- 定义另一个成员函数 base_type:hello
	print("hello base_type")
end

-- 以上是基本的 class 定义的语法，完全兼容 lua 的编程习惯。我增加了一个叫做 ctor 的词，作为构造函数的名字。
-- 下面看看怎样继承：
test=class(base_type)	-- 定义一个类 test 继承于 base_type

function test:ctor()	-- 定义 test 的构造函数
	print("test ctor")
end

function test:hello()	-- 重载 base_type:hello 为 test:hello
	print("hello test")
end

-- 现在可以试一下了：
a=test.new(1)	-- 输出两行，base_type ctor 和 test ctor 。这个对象被正确的构造了。
a:print_x()	-- 输出 1 ，这个是基类 base_type 中的成员函数。
a:hello()	-- 输出 hello test ，这个函数被重载了。

M.TablePlus = require("utils.TablePlus")
M.Class = class

return M
