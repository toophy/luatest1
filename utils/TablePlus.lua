TablePlus = {}

local function checkTable( t )
	-- body
	if type(t) ~= "table" then 
		error("t is not table")
	end 
end

local function checkType(_type)
	if _type ~= "array" and _type ~= "hashmap" and _type ~= nil then 
		error("invalid type .." .. tostring(_type))
	end
	
end 

--[[
	设置元表属性__type，取值自["array","hashmap"]
]]
local function genmetatable(_type)
	checkType(_type)
	local __type = _type or "hashmap"
	local mt = {
		__index = function(t,k)
			if k == "__type" then 
				return __type
			else 
				return rawget(t,k)
			end
		end,
		__newindex = function(t,k,v)
			if k == "__type" then 
				checkType(v)
				__type = v
			else 
				rawset(t,k,v)
			end
		end
	}

	return mt

end


function TablePlus.new(_type)
	local t = {}
	setmetatable(t,genmetatable(_type))
	return t 
end 


function TablePlus:foreach(f)
	if self.__type == "array" then 
		for k,v in ipairs(self) do 
			if f(k,v) then break end --拓展可中断
		end
	else 
		for k,v in pairs(self) do 
			if f(k,v) then break end --拓展可中断
		end 
	end 

end 

--[[
	递归打印table	
]]
function TablePlus.toString(t,isRecur)
	if (type(t) ~= "table") then 
		return tostring(t) 
	else
		local result = "{"
		TablePlus.foreach(t,function(k,v)
			result = result .. "['" .. tostring(k) .. "']=" 
			if type(v) == "table" and isRecur == true then 
				result = result .. TablePlus.toString(v,true) .. "',"
			elseif type(v) == "string" then
				result = result .. "'" .. tostring(v) .. "',"
			else
				result = result  .. tostring(v) .. ","
			end 
		end 
		)
		return result .. "}"
	end
end 



local function wordsIndentBy(xn)
	local result = ""
    for i=1,xn do  
        result = result .."\t"  
    end 
	return result
end  


local function _toTreeString(t,deep)
	if (type(t) ~= "table") then 
		return tostring(t) 
	else
		local indent = wordsIndentBy(deep)
		local result = indent .. "table{\n" 

		TablePlus.foreach(t,function(k,v)
			result = result ..  wordsIndentBy(deep+1)
			result = result .. "['" .. tostring(k) .. "']=" 
			
			if type(v) == "table" then 
				local subT = _toTreeString(v,deep+2) 
				result = result .. "\n" ..  subT.. "'," .. "\n"
			else
				result = result  .. tostring(v) .. ",".. "\n"
			end 
		end 
		)
		return result .. indent ..  "}"
	end
end 

--[[
	将table打印为树形结构	
]]
function TablePlus.toTreeString(t)
	return _toTreeString(t,0)
end

--[[
--示例
t={  
    school = {  
        name = "scau",  
        location = "gz"  
    },  
    age = 13,  
    name = "Lily",  
}  
  
print("print table directly " )  
print("" )  
print(TablePlus.toString(t,true))  
  
print("" )  
  
print("print table in tree pattern " )  
print("" )  
print(TablePlus.toTreeString(t))  

--]]

return TablePlus

