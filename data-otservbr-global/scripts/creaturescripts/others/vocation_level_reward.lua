local table = {
  -- Master Sorcerer | Elder Druid
  [{1, 2, 5, 6}] = {
    [80] = {
      items = {
        {3210}, -- Hat of the Mad
        {8043}, -- Focus Cape
        {3079}, -- Boots of Haste
        {8072}, -- Spellbook of Enlightment
        {10387}, -- Zaoan Legs
        {25700}, -- Dream Blossom Staff
      },
      storage = 40100,
      message = "Como recompensa por chegar ao level 80, te entregamos um presente!"
    },
  },
  -- Royal Paladin
  [{3, 7}] = {
    [80] = {
      items = {
        {3392}, -- Royal Helmet
        {8063}, -- Paladin Armor
        {3398}, -- Dwarven Legs
        {3079}, -- Boots of Haste
        {7438}, -- Elvish Bow
      },
      storage = 40101,
      message = "Como recompensa por chegar ao level 80, te entregamos um presente!"
    },
  },
  -- Elite Knight
  [{4, 8}] = {
    [80] = {
      items = {
        {10387}, -- Zaoan Legs
        {3392}, -- Royal Helmet
        {3360}, -- Golden Armor
        {3079}, -- Boots of Haste
        {3428}, -- Tower Shield
        {7404}, -- Assassin Dagger
        {3344}, -- Beastslayer Axe
        {3324}, -- Skull Staff
      },
      storage = 40102,
      message = "Como recompensa por chegar ao level 80, te entregamos um presente!"
    },
  },
}

local rewardLevel = CreatureEvent("RewardLevel")

function rewardLevel.onAdvance(player, skill, oldLevel, newLevel)
  if skill ~= SKILL_LEVEL or newLevel <= oldLevel then
    return true
  end

  for voc, attributes in pairs(table) do
    if isInArray(voc, player:getVocation():getId()) then
      for level, details in pairs(attributes) do
        if newLevel >= level and player:getStorageValue(details.storage) ~= 1 then
          local backpack = player:addItem(9605, 1) -- Crown Backpack
          if backpack then
            for i = 1, #details.items do
              backpack:addItem(details.items[i], 1)
              player:sendTextMessage(MESSAGE_EVENT_ADVANCE, details.message)
              player:setStorageValue(details.storage, 1)
            end
          end
        end
      end
      player:save()
      return true
    end
  end
end

rewardLevel:register()
