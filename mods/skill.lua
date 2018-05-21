skill = {}

function skill.Check(id)
	print( string.format("检查技能%d",id) )
	return true
end

function skill.Use(id)
	print( string.format("使用技能%d",id) )
	return true

end

return skill
					