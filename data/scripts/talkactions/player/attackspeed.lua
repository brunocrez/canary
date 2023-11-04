local attackSpeed = TalkAction("!attackspeed")

function attackSpeed.onSay(player, words, param)
	local attackSpeed = player:getSkillLevel(SKILL_FIST) * configManager.getNumber(configKeys.MULTIPLIER_ATTACKONFIST)
	local finalSpeed = 1000 - attackSpeed
	local text = "AttackSpeed Atual: " .. tostring(1000 / finalSpeed):sub(1, 4) .. " ataques por segundo.\n" .. "\nPara aumentar sua velocidade de ataque treine seu Fist Fighting!"

	player:popupFYI(text)
	return true
end

attackSpeed:separator(" ")
attackSpeed:groupType("normal")
attackSpeed:register()
