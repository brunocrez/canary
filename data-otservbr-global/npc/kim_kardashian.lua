local internalNpcName = "Kim Kardashian"
local npcType = Game.createNpcType(internalNpcName)
local npcConfig = {}

npcConfig.name = internalNpcName
npcConfig.description = internalNpcName

npcConfig.health = 100
npcConfig.maxHealth = npcConfig.health
npcConfig.walkInterval = 2000
npcConfig.walkRadius = 2

npcConfig.outfit = {
	lookType = 138,
	lookHead = 115,
	lookBody = 39,
	lookLegs = 96,
	lookFeet = 118,
	lookAddons = 3
}

npcConfig.flags = {
	floorchange = false
}

npcConfig.voices = {
	interval = 15000,
	chance = 50,
	{text = 'Pelo menos eu sou bonita!'}
}

local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)

npcType.onThink = function(npc, interval)
	npcHandler:onThink(npc, interval)
end

npcType.onAppear = function(npc, creature)
	npcHandler:onAppear(npc, creature)
end

npcType.onDisappear = function(npc, creature)
	npcHandler:onDisappear(npc, creature)
end

npcType.onMove = function(npc, creature, fromPosition, toPosition)
	npcHandler:onMove(npc, creature, fromPosition, toPosition)
end

npcType.onSay = function(npc, creature, type, message)
	npcHandler:onSay(npc, creature, type, message)
end

npcType.onCloseChannel = function(npc, creature)
	npcHandler:onCloseChannel(npc, creature)
end

addoninfo = {
	['citizen'] = {
		cost = 1000000,
		items = {7289, 4},
		outfit_female = 136,
		outfit_male = 128,
		addon = 3,
		firstAddon = Storage.OutfitQuest.Citizen.AddonBackpack,
		secondAddon = Storage.OutfitQuest.Citizen.AddonHat
	},
	['hunter'] = {
		cost = 1000000,
		items = {7289, 4},
		outfit_female = 137,
		outfit_male = 129,
		addon = 3,
		firstAddon = Storage.OutfitQuest.Hunter.AddonHat,
		secondAddon = Storage.OutfitQuest.Hunter.AddonGlove
	},
	['knight'] = {
		cost = 1000000,
		items = {7289, 4},
		outfit_female = 139,
		outfit_male = 131,
		addon = 3,
		firstAddon = Storage.OutfitQuest.Knight.AddonSword,
		secondAddon = Storage.OutfitQuest.Knight.AddonHelmet
	},
	['druid'] = {
		cost = 1000000,
		items = {7289, 8},
		outfit_female = 148,
		outfit_male = 144,
		addon = 3,
		firstAddon = Storage.OutfitQuest.DruidHatAddon,
		secondAddon = Storage.OutfitQuest.DruidBodyAddon
	},
	['mage'] = {
		cost = 500000,
		items = {7289, 4},
		outfit_female = 138,
		outfit_male = 130,
		addon = 1,
		firstAddon = Storage.OutfitQuest.MageSummoner.AddonWand,
		secondAddon = nil
	},
	['ferumbras hat'] = {
		cost = 10000000,
		items = {5903, 1},
		outfit_female = 138,
		outfit_male = 130,
		addon = 2,
		firstAddon = nil,
		secondAddon = Storage.OutfitQuest.MageSummoner.AddonHatCloak
	},
	['summoner'] = {
		cost = 5000000,
		items = {7289, 12},
		outfit_female = 141,
		outfit_male = 133,
		addon = 3,
		firstAddon = Storage.OutfitQuest.MageSummoner.AddonBelt,
		secondAddon = Storage.OutfitQuest.MageSummoner.AddonWandTimer
	},
	['barbarian'] = {
		cost = 5000000,
		items = {7289, 12},
		outfit_female = 147,
		outfit_male = 143,
		addon = 3,
		firstAddon = 51032,
		secondAddon = 51033
	},
	['nobleman'] = {
		cost = 5000000,
		items = {7289, 12},
		outfit_female = 140,
		outfit_male = 132,
		addon = 3,
		firstAddon = Storage.OutfitQuest.NoblemanFirstAddon,
		secondAddon = Storage.OutfitQuest.NoblemanSecondAddon
	},
	['oriental'] = {
		cost = 5000000,
		items = {7289, 12},
		outfit_female = 150,
		outfit_male = 146,
		addon = 3,
		firstAddon = Storage.OutfitQuest.FirstOrientalAddon,
		secondAddon = Storage.OutfitQuest.SecondOrientalAddon
	},
	['warrior'] = {
		cost = 5000000,
		items = {7289, 12},
		outfit_female = 142,
		outfit_male = 134,
		addon = 3,
		firstAddon = Storage.OutfitQuest.WarriorShoulderAddon,
		secondAddon = Storage.OutfitQuest.WarriorSwordAddon
	},
	['wizard'] = {
		cost = 5000000,
		items = {7289, 12},
		outfit_female = 149,
		outfit_male = 145,
		addon = 3,
		firstAddon = 51034,
		secondAddon = 51035
	},
	['assassin'] = {
		cost = 5000000,
		items = {7289, 16},
		outfit_female = 156,
		outfit_male = 152,
		addon = 3,
		firstAddon = Storage.OutfitQuest.AssassinFirstAddon,
		secondAddon = Storage.OutfitQuest.AssassinSecondAddon
	},
	['beggar'] = {
		cost = 5000000,
		items = {7289, 16},
		outfit_female = 157,
		outfit_male = 153,
		addon = 3,
		firstAddon = Storage.OutfitQuest.BeggarFirstAddonDoor,
		secondAddon = Storage.OutfitQuest.BeggarSecondAddon
	},
	['pirate'] = {
		cost = 5000000,
		items = {7289, 16},
		outfit_female = 155,
		outfit_male = 151,
		addon = 3,
		firstAddon = Storage.OutfitQuest.PirateSabreAddon,
		secondAddon = Storage.OutfitQuest.PirateHatAddon
	},
	['shaman'] = {
		cost = 5000000,
		items = {7289, 16},
		outfit_female = 158,
		outfit_male = 154,
		addon = 3,
		firstAddon = 51036,
		secondAddon = 51037
	},
	['norseman'] = {
		cost = 5000000,
		items = {7289, 12},
		outfit_female = 252,
		outfit_male = 251,
		addon = 3,
		firstAddon = 51038,
		secondAddon = 51039
	},
}

local o = {'citizen', 'hunter', 'knight', 'mage', 'nobleman', 'summoner', 'warrior', 'barbarian', 'druid', 'wizard', 'oriental', 'pirate', 'assassin', 'beggar', 'shaman', 'norseman'}
local rtnt = {}
local function creatureSayCallback(npc, creature, type, message)
local talkUser = creature
local player = Player(creature)
local playerId = player:getId()

local talkState = {}
	if not npcHandler:checkInteraction(npc, creature) then
		return false
	end

	if addoninfo[message] ~= nil then
		local items = addoninfo[message].items
		local items_list = ''

		if (player:getStorageValue(addoninfo[message].firstAddon) ~= -1 and player:getStorageValue(addoninfo[message].secondAddon) ~= -1) then
			npcHandler:say('You already have this addon!', npc, creature)
			npcHandler:resetNpc(creature)
			return true
		elseif table.maxn(items) > 0 then
			items_list = items_list .. items[2] .. ' ' .. ItemType(items[1]):getName()
		end

		local text = ''

		if (addoninfo[message].cost > 0) and table.maxn(addoninfo[message].items) then
			text = items_list .. ' and ' .. addoninfo[message].cost .. ' gp'
		end

		npcHandler:say('For ' .. message .. ' outfit, you will need ' .. text .. '. Do you have it all with you?', npc, creature)
		rtnt = message
		talkState[talkUser] = {addoninfo[message].firstAddon, addoninfo[message].secondAddon}
		npcHandler:setTopic(playerId, 2)
		return true
	elseif npcHandler:getTopic(playerId) == 2 then
		if MsgContains(message, "yes") then
			local hasEnoughItems = false
			local item = addoninfo[rtnt].items
			if (player:getItemCount(item[1]) >= item[2]) then
				hasEnoughItems = true
			end

			if (player:getMoney() >= addoninfo[rtnt].cost) and hasEnoughItems then
				player:removeMoney(addoninfo[rtnt].cost)
				local item = addoninfo[rtnt].items
				player:removeItem(item[1], item[2])

				player:getPosition():sendMagicEffect(CONST_ME_MAGIC_BLUE)
				player:addOutfitAddon(addoninfo[rtnt].outfit_male, addoninfo[rtnt].addon)
				player:addOutfitAddon(addoninfo[rtnt].outfit_female, addoninfo[rtnt].addon)

				-- Mage Addons Exception
				if (rtnt == 'mage') then
					player:setStorageValue(addoninfo[rtnt].firstAddon, 1)
				elseif (rtnt == 'ferumbras hat') then
					player:setStorageValue(addoninfo[rtnt].secondAddon, 1)
				else -- Regular Addons
					player:setStorageValue(addoninfo[rtnt].firstAddon, 1)
					player:setStorageValue(addoninfo[rtnt].secondAddon, 1)
				end

				npcHandler:say('Here you are.', npc, creature)
			else
				local item = addoninfo[rtnt].items
				npcHandler:say('You do not have needed items!', npc, creature)
			end

			rtnt = nil
			talkState[talkUser] = 0
			npcHandler:resetNpc(creature)
			return true
		end
	elseif MsgContains(message, "help") then
		npcHandler:say('You must say the oufit name in order to get the full outfit like this \'citizen\', \'hunter\', \'mage\', etc.', npc, creature)
		rtnt = nil
		talkState[talkUser] = 0
		npcHandler:resetNpc(creature)
		return true
	else
		if talkState[talkUser] ~= nil then
			if talkState[talkUser] > 0 then
				npcHandler:say('Come back when you get these items.', npc, creature)
				rtnt = nil
				talkState[talkUser] = 0
				npcHandler:resetNpc(creature)
				return true
			end
		end
	end
	return true
end

npcHandler:setMessage(MESSAGE_GREET, 'Welcome |PLAYERNAME|! If you want some addons, just ask me! Do you want some {help} or are you decided? If you are decided, just say the name of the outfit like this: {citizen}')
npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new(), npcConfig.name, true, true, true)
npcType:register(npcConfig)
