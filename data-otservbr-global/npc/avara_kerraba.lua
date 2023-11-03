local internalNpcName = "Avara Kerraba"
local npcType = Game.createNpcType(internalNpcName)
local npcConfig = {}

npcConfig.name = internalNpcName
npcConfig.description = internalNpcName

npcConfig.health = 100
npcConfig.maxHealth = npcConfig.health
npcConfig.walkInterval = 2000
npcConfig.walkRadius = 2

npcConfig.outfit = {
	lookType = 141,
	lookHead = 41,
	lookBody = 72,
	lookLegs = 39,
	lookFeet = 96,
	lookAddons = 3,
	lookMount = 688,
}

npcConfig.flags = {
	floorchange = false,
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

npcHandler:setMessage(MESSAGE_GREET, "Pega na minha e balanssa!")
npcHandler:setMessage(MESSAGE_SENDTRADE, "Rasta tabaca na vara.")
npcHandler:setMessage(MESSAGE_FAREWELL, "Vai sentando na vassoura.")
npcHandler:setMessage(MESSAGE_WALKAWAY, "Ui, que varinha em?")

npcHandler:addModule(FocusModule:new(), npcConfig.name, true, true, true)

npcConfig.shop = {
	{ itemName = "basic exercise axe", clientId = 28553, buy = 525000, count = 1500 },
	{ itemName = "basic exercise bow", clientId = 28555, buy = 525000, count = 1500 },
	{ itemName = "basic exercise club", clientId = 28554, buy = 525000, count = 1500 },
	{ itemName = "basic exercise shield", clientId = 44065, buy = 525000, count = 1500 },
	{ itemName = "basic exercise sword", clientId = 28552, buy = 525000, count = 1500 },
	{ itemName = "basic exercise rod", clientId = 28556, buy = 525000, count = 1500 },
	{ itemName = "basic exercise wand", clientId = 28557, buy = 525000, count = 1500 },
	{ itemName = "durable exercise axe", clientId = 35280, buy = 1890000, count = 4000 },
	{ itemName = "durable exercise bow", clientId = 35282, buy = 1890000, count = 4000 },
	{ itemName = "durable exercise club", clientId = 35281, buy = 1890000, count = 4000 },
	{ itemName = "durable exercise shield", clientId = 44066, buy = 1890000, count = 4000 },
	{ itemName = "durable exercise sword", clientId = 35279, buy = 1890000, count = 4000 },
	{ itemName = "durable exercise rod", clientId = 35283, buy = 1890000, count = 4000 },
	{ itemName = "durable exercise wand", clientId = 35284, buy = 1890000, count = 4000 },
	{ itemName = "lasting exercise axe", clientId = 35286, buy = 15120000, count = 17000 },
	{ itemName = "lasting exercise bow", clientId = 35288, buy = 15120000, count = 17000 },
	{ itemName = "lasting exercise club", clientId = 35287, buy = 15120000, count = 17000 },
	{ itemName = "lasting exercise shield", clientId = 44067, buy = 15120000, count = 17000 },
	{ itemName = "lasting exercise sword", clientId = 35285, buy = 15120000, count = 17000 },
	{ itemName = "lasting exercise rod", clientId = 35289, buy = 15120000, count = 17000 },
	{ itemName = "lasting exercise wand", clientId = 35290, buy = 15120000, count = 17000 },
}
-- On buy npc shop message
npcType.onBuyItem = function(npc, player, itemId, subType, amount, ignore, inBackpacks, totalCost)
	npc:sellItem(player, itemId, amount, subType, 0, ignore, inBackpacks)
end
-- On sell npc shop message
npcType.onSellItem = function(npc, player, itemId, subtype, amount, ignore, name, totalCost)
	player:sendTextMessage(MESSAGE_INFO_DESCR, string.format("Sold %ix %s for %i gold.", amount, name, totalCost))
end
-- On check npc shop message (look item)
npcType.onCheckItem = function(npc, player, clientId, subType) end

npcType:register(npcConfig)
