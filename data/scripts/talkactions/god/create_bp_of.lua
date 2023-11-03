local createBackpackOf = TalkAction("/createbp")

function createBackpackOf.onSay(player, words, param)
	-- create log
	logCommand(player, words, param)

	local split = param:split(",")
	local itemType = split[1]
	local exerciseWeapon = tonumber(itemType)

	if itemType == "" then
		player:sendCancelMessage("You must inform the ID.")
		return true
	end

	local count = tonumber(split[2])
	if not count then
		local backpack = player:addItem(8860, 1)
		for i = 1, 19 do
			backpack:addItem(exerciseWeapon, 17000)
		end
	else
		for i = 1, count do
			local backpack = player:addItem(8860, 1)
			if backpack then
				for i = 1, 19 do
					backpack:addItem(exerciseWeapon, 17000)
				end
			end
		end
	end

	player:getPosition():sendMagicEffect(CONST_ME_MAGIC_GREEN)
	return true
end

createBackpackOf:separator(" ")
createBackpackOf:groupType("god")
createBackpackOf:register()
