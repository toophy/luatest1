--lua面向对象：简单粗暴的实现
function copytable(tbArg)
    local tbCollsion = {}
    
    --local的作用域问题
    local copy    
    copy = function (obj)
        if type(obj) ~= "table" then
            return obj;
        end
        --检查是否有嵌套循环的table
        if tbCollsion[obj] then
            return tbCollsion[obj];
        end
        
        local tbNew = {}
        tbCollsion[obj] = tbNew;
        --递归复制
        for k, v in pairs(obj) do
            tbNew[k] = copy(v);
        end
        --复制完之后，元表关系也要保留下来
        return setmetatable(tbNew, getmetatable(obj))
    end

    return copy(tbArg);
end

function inherit(tbBase, tbClass)
    --复制基类
    local tbNew = copytable(tbBase)
    
    
    local tm = {}
    tm.__index = tbClass;
    setmetatable(tbNew, tm)
    
    --修改tbBase为tbClass中的成员或者新增加tbClass中的成员
    if tbClass then
        for k, v in pairs(tbClass) do
            tbNew[k] = v
        end
    end

    return tbNew;
end

--使用, 只是面向对象, 没有继承,函数重载等
--[[

local tbObject = {}
local tbFruit = inherit(tbObject)
local tbApple = inherit(tbFruit)
local tbBanana = inherit(tbFruit)
local tbBanana1 = inherit(tbFruit)
local tbBanana2 = inherit(tbFruit, tbBanana1)

--]]
