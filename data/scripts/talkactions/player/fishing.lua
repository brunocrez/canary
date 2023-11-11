local fishing = TalkAction("!fishing")

function fishing.onSay(player, words, param)
	local lootBonus = (player:getSkillLevel(SKILL_FISHING) - 10) * 0.235
	local text = "Loot Bonus: " .. math.floor(lootBonus) .. "%.\n" .. "\nPara aumentar sua chance de drop treine seu Fishing!"
	player:popupFYI(text)
	return true
end

fishing:separator(" ")
fishing:groupType("normal")
fishing:register()
