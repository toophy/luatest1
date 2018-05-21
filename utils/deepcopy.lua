--lua������󣺼򵥴ֱ���ʵ��
function copytable(tbArg)
    local tbCollsion = {}
    
    --local������������
    local copy    
    copy = function (obj)
        if type(obj) ~= "table" then
            return obj;
        end
        --����Ƿ���Ƕ��ѭ����table
        if tbCollsion[obj] then
            return tbCollsion[obj];
        end
        
        local tbNew = {}
        tbCollsion[obj] = tbNew;
        --�ݹ鸴��
        for k, v in pairs(obj) do
            tbNew[k] = copy(v);
        end
        --������֮��Ԫ���ϵҲҪ��������
        return setmetatable(tbNew, getmetatable(obj))
    end

    return copy(tbArg);
end

function inherit(tbBase, tbClass)
    --���ƻ���
    local tbNew = copytable(tbBase)
    
    
    local tm = {}
    tm.__index = tbClass;
    setmetatable(tbNew, tm)
    
    --�޸�tbBaseΪtbClass�еĳ�Ա����������tbClass�еĳ�Ա
    if tbClass then
        for k, v in pairs(tbClass) do
            tbNew[k] = v
        end
    end

    return tbNew;
end

--ʹ��, ֻ���������, û�м̳�,�������ص�
--[[

local tbObject = {}
local tbFruit = inherit(tbObject)
local tbApple = inherit(tbFruit)
local tbBanana = inherit(tbFruit)
local tbBanana1 = inherit(tbFruit)
local tbBanana2 = inherit(tbFruit, tbBanana1)

--]]
