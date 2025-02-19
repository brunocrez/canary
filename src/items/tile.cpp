/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "pch.hpp"

#include "items/tile.hpp"
#include "creatures/creature.hpp"
#include "creatures/combat/combat.hpp"
#include "game/game.hpp"
#include "game/zones/zone.hpp"
#include "items/containers/mailbox/mailbox.hpp"
#include "creatures/monsters/monster.hpp"
#include "lua/creature/movement.hpp"
#include "game/movement/teleport.hpp"
#include "items/trashholder.hpp"
#include "io/iomap.hpp"
#include "map/spectators.hpp"

auto real_nullptr_tile = std::make_shared<StaticTile>(0xFFFF, 0xFFFF, 0xFF);
const std::shared_ptr<Tile> &Tile::nullptr_tile = real_nullptr_tile;

bool Tile::hasProperty(ItemProperty prop) const {
	switch (prop) {
		case CONST_PROP_BLOCKSOLID:
			return hasFlag(TILESTATE_BLOCKSOLID);
		case CONST_PROP_HASHEIGHT:
			return hasFlag(TILESTATE_HASHEIGHT);
		case CONST_PROP_BLOCKPROJECTILE:
			return hasFlag(TILESTATE_BLOCKPROJECTILE);
		case CONST_PROP_BLOCKPATH:
			return hasFlag(TILESTATE_BLOCKPATH);
		case CONST_PROP_ISVERTICAL:
			return hasFlag(TILESTATE_ISVERTICAL);
		case CONST_PROP_ISHORIZONTAL:
			return hasFlag(TILESTATE_ISHORIZONTAL);
		case CONST_PROP_MOVEABLE:
			return hasFlag(TILESTATE_MOVEABLE);
		case CONST_PROP_IMMOVABLEBLOCKSOLID:
			return hasFlag(TILESTATE_IMMOVABLEBLOCKSOLID);
		case CONST_PROP_IMMOVABLEBLOCKPATH:
			return hasFlag(TILESTATE_IMMOVABLEBLOCKPATH);
		case CONST_PROP_IMMOVABLENOFIELDBLOCKPATH:
			return hasFlag(TILESTATE_IMMOVABLENOFIELDBLOCKPATH);
		case CONST_PROP_NOFIELDBLOCKPATH:
			return hasFlag(TILESTATE_NOFIELDBLOCKPATH);
		case CONST_PROP_SUPPORTHANGABLE:
			return hasFlag(TILESTATE_SUPPORTS_HANGABLE);
		default:
			return false;
	}
}

bool Tile::hasProperty(std::shared_ptr<Item> exclude, ItemProperty prop) const {
	assert(exclude);

	if (ground && exclude != ground && ground->hasProperty(prop)) {
		return true;
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto &item : *items) {
			if (item != exclude && item->hasProperty(prop)) {
				return true;
			}
		}
	}

	return false;
}

bool Tile::hasHeight(uint32_t n) const {
	uint32_t height = 0;

	if (ground) {
		if (ground->hasProperty(CONST_PROP_HASHEIGHT)) {
			++height;
		}

		if (n == height) {
			return true;
		}
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto &item : *items) {
			if (item->hasProperty(CONST_PROP_HASHEIGHT)) {
				++height;
			}

			if (n == height) {
				return true;
			}
		}
	}
	return false;
}

size_t Tile::getCreatureCount() const {
	if (const CreatureVector* creatures = getCreatures()) {
		return creatures->size();
	}
	return 0;
}

size_t Tile::getItemCount() const {
	if (const TileItemVector* items = getItemList()) {
		return items->size();
	}
	return 0;
}

uint32_t Tile::getTopItemCount() const {
	if (const TileItemVector* items = getItemList()) {
		return items->getTopItemCount();
	}
	return 0;
}

uint32_t Tile::getDownItemCount() const {
	if (const TileItemVector* items = getItemList()) {
		return items->getDownItemCount();
	}
	return 0;
}

std::string Tile::getDescription(int32_t) {
	return "You dont know why, but you cant see anything!";
}

std::shared_ptr<Teleport> Tile::getTeleportItem() const {
	if (!hasFlag(TILESTATE_TELEPORT)) {
		return nullptr;
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getTeleport()) {
				return (*it)->getTeleport();
			}
		}
	}
	return nullptr;
}

std::shared_ptr<MagicField> Tile::getFieldItem() const {
	if (!hasFlag(TILESTATE_MAGICFIELD)) {
		return nullptr;
	}

	if (ground && ground->getMagicField()) {
		return ground->getMagicField();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getMagicField()) {
				return (*it)->getMagicField();
			}
		}
	}
	return nullptr;
}

std::shared_ptr<TrashHolder> Tile::getTrashHolder() const {
	if (!hasFlag(TILESTATE_TRASHHOLDER)) {
		return nullptr;
	}

	if (ground && ground->getTrashHolder()) {
		return ground->getTrashHolder();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getTrashHolder()) {
				return (*it)->getTrashHolder();
			}
		}
	}
	return nullptr;
}

std::shared_ptr<Mailbox> Tile::getMailbox() const {
	if (!hasFlag(TILESTATE_MAILBOX)) {
		return nullptr;
	}

	if (ground && ground->getMailbox()) {
		return ground->getMailbox();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getMailbox()) {
				return (*it)->getMailbox();
			}
		}
	}
	return nullptr;
}

std::shared_ptr<BedItem> Tile::getBedItem() const {
	if (!hasFlag(TILESTATE_BED)) {
		return nullptr;
	}

	if (ground && ground->getBed()) {
		return ground->getBed();
	}

	if (const TileItemVector* items = getItemList()) {
		for (auto it = items->rbegin(), end = items->rend(); it != end; ++it) {
			if ((*it)->getBed()) {
				return (*it)->getBed();
			}
		}
	}
	return nullptr;
}

std::shared_ptr<Creature> Tile::getTopCreature() const {
	if (const CreatureVector* creatures = getCreatures()) {
		if (!creatures->empty()) {
			return *creatures->begin();
		}
	}
	return nullptr;
}

std::shared_ptr<Creature> Tile::getBottomCreature() const {
	if (const CreatureVector* creatures = getCreatures()) {
		if (!creatures->empty()) {
			return *creatures->rbegin();
		}
	}
	return nullptr;
}

std::shared_ptr<Creature> Tile::getTopVisibleCreature(std::shared_ptr<Creature> creature) const {
	if (const CreatureVector* creatures = getCreatures()) {
		if (creature) {
			std::shared_ptr<Player> player = creature->getPlayer();
			if (player && player->isAccessPlayer()) {
				return getTopCreature();
			}

			for (auto &tileCreature : *creatures) {
				if (creature->canSeeCreature(tileCreature)) {
					return tileCreature;
				}
			}
		} else {
			for (auto &tileCreature : *creatures) {
				if (!tileCreature->isInvisible()) {
					std::shared_ptr<Player> player = tileCreature->getPlayer();
					if (!player || !player->isInGhostMode()) {
						return tileCreature;
					}
				}
			}
		}
	}
	return nullptr;
}

std::shared_ptr<Creature> Tile::getBottomVisibleCreature(std::shared_ptr<Creature> creature) const {
	if (const CreatureVector* creatures = getCreatures()) {
		if (creature) {
			std::shared_ptr<Player> player = creature->getPlayer();
			if (player && player->isAccessPlayer()) {
				return getBottomCreature();
			}

			for (auto it = creatures->rbegin(), end = creatures->rend(); it != end; ++it) {
				if (creature->canSeeCreature(*it)) {
					return *it;
				}
			}
		} else {
			for (auto it = creatures->rbegin(), end = creatures->rend(); it != end; ++it) {
				if (!(*it)->isInvisible()) {
					std::shared_ptr<Player> player = (*it)->getPlayer();
					if (!player || !player->isInGhostMode()) {
						return *it;
					}
				}
			}
		}
	}
	return nullptr;
}

std::shared_ptr<Item> Tile::getTopDownItem() const {
	if (const TileItemVector* items = getItemList()) {
		return items->getTopDownItem();
	}
	return nullptr;
}

std::shared_ptr<Item> Tile::getTopTopItem() const {
	if (const TileItemVector* items = getItemList()) {
		return items->getTopTopItem();
	}
	return nullptr;
}

std::shared_ptr<Item> Tile::getItemByTopOrder(int32_t topOrder) {
	// topOrder:
	// 1: borders
	// 2: ladders, signs, splashes
	// 3: doors etc
	// 4: creatures
	if (TileItemVector* items = getItemList()) {
		for (auto it = ItemVector::const_reverse_iterator(items->getEndTopItem()), end = ItemVector::const_reverse_iterator(items->getBeginTopItem()); it != end; ++it) {
			if (Item::items[(*it)->getID()].alwaysOnTopOrder == topOrder) {
				return (*it);
			}
		}
	}
	return nullptr;
}

std::shared_ptr<Thing> Tile::getTopVisibleThing(std::shared_ptr<Creature> creature) {
	std::shared_ptr<Thing> thing = getTopVisibleCreature(creature);
	if (thing) {
		return thing;
	}

	TileItemVector* items = getItemList();
	if (items) {
		for (ItemVector::const_iterator it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
			const ItemType &iit = Item::items[(*it)->getID()];
			if (!iit.lookThrough) {
				return (*it);
			}
		}

		for (auto it = ItemVector::const_reverse_iterator(items->getEndTopItem()), end = ItemVector::const_reverse_iterator(items->getBeginTopItem()); it != end; ++it) {
			const ItemType &iit = Item::items[(*it)->getID()];
			if (!iit.lookThrough) {
				return (*it);
			}
		}
	}

	return ground;
}

void Tile::onAddTileItem(std::shared_ptr<Item> item) {
	if ((item->hasProperty(CONST_PROP_MOVEABLE) || item->getContainer()) || (item->isWrapable() && !item->hasProperty(CONST_PROP_MOVEABLE) && !item->hasProperty(CONST_PROP_BLOCKPATH))) {
		auto it = g_game().browseFields.find(static_self_cast<Tile>());
		if (it != g_game().browseFields.end()) {
			auto lockedCylinder = it->second.lock();
			if (lockedCylinder) {
				lockedCylinder->addItemBack(item);
				item->setParent(getTile());
			}
		}
	}

	setTileFlags(item);

	const Position &cylinderMapPos = getPosition();

	auto spectators = Spectators().find<Creature>(cylinderMapPos, true);

	// send to client
	for (const auto &spectator : spectators) {
		if (const auto &tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendAddTileItem(static_self_cast<Tile>(), cylinderMapPos, item);
		}
	}

	// event methods
	for (const auto &spectator : spectators) {
		spectator->onAddTileItem(static_self_cast<Tile>(), cylinderMapPos);
	}

	if ((!hasFlag(TILESTATE_PROTECTIONZONE) || g_configManager().getBoolean(CLEAN_PROTECTION_ZONES))
		&& item->isCleanable()) {
		if (!this->getHouse()) {
			g_game().addTileToClean(static_self_cast<Tile>());
		}
	}

	if (item->isCarpet() && !item->isMoveable()) {
		if (getTopTopItem() && getTopTopItem()->canReceiveAutoCarpet()) {
			return;
		}
		auto house = getHouse();
		if (!house) {
			return;
		}

		for (const auto &tile : getSurroundingTiles()) {
			if (!tile || !tile->getGround() || tile->getGround()->getID() != getGround()->getID()) {
				continue;
			}
			auto topItem = tile->getTopTopItem();
			if (!topItem || !topItem->canReceiveAutoCarpet()) {
				continue;
			}
			// Check if tile is part of the same house
			if (auto tileHouse = tile->getHouse(); !tileHouse || house != tileHouse) {
				continue;
			}

			// Clear any existing carpet
			for (auto tileItem : *tile->getItemList()) {
				if (tileItem && tileItem->isCarpet()) {
					tile->removeThing(tileItem, tileItem->getItemCount());
				}
			}

			auto carpet = item->clone();
			carpet->setAttribute(ItemAttribute_t::ACTIONID, IMMOVABLE_ACTION_ID);
			tile->addThing(carpet);
		}
	}
}

void Tile::onUpdateTileItem(std::shared_ptr<Item> oldItem, const ItemType &oldType, std::shared_ptr<Item> newItem, const ItemType &newType) {
	if ((newItem->hasProperty(CONST_PROP_MOVEABLE) || newItem->getContainer()) || (newItem->isWrapable() && newItem->hasProperty(CONST_PROP_MOVEABLE) && !oldItem->hasProperty(CONST_PROP_BLOCKPATH))) {
		auto it = g_game().browseFields.find(getTile());
		if (it != g_game().browseFields.end()) {
			auto lockedCylinder = it->second.lock();
			if (lockedCylinder) {
				int32_t index = lockedCylinder->getThingIndex(oldItem);
				if (index != -1) {
					lockedCylinder->replaceThing(index, newItem);
					newItem->setParent(static_self_cast<Tile>());
				}
			}
		}
	} else if ((oldItem->hasProperty(CONST_PROP_MOVEABLE) || oldItem->getContainer()) || (oldItem->isWrapable() && !oldItem->hasProperty(CONST_PROP_MOVEABLE) && !oldItem->hasProperty(CONST_PROP_BLOCKPATH))) {
		auto it = g_game().browseFields.find(getTile());
		if (it != g_game().browseFields.end()) {
			auto lockedCylinder = it->second.lock();
			if (lockedCylinder) {
				std::shared_ptr<Cylinder> oldParent = oldItem->getParent();
				lockedCylinder->removeThing(oldItem, oldItem->getItemCount());
				oldItem->setParent(oldParent);
			}
		}
	}

	const Position &cylinderMapPos = getPosition();

	auto spectators = Spectators().find<Creature>(cylinderMapPos, true);

	// send to client
	for (const auto &spectator : spectators) {
		if (const auto &tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendUpdateTileItem(static_self_cast<Tile>(), cylinderMapPos, newItem);
		}
	}

	// event methods
	for (const auto &spectator : spectators) {
		spectator->onUpdateTileItem(static_self_cast<Tile>(), cylinderMapPos, oldItem, oldType, newItem, newType);
	}
}

void Tile::onRemoveTileItem(const CreatureVector &spectators, const std::vector<int32_t> &oldStackPosVector, std::shared_ptr<Item> item) {
	if ((item->hasProperty(CONST_PROP_MOVEABLE) || item->getContainer()) || (item->isWrapable() && !item->hasProperty(CONST_PROP_MOVEABLE) && !item->hasProperty(CONST_PROP_BLOCKPATH))) {
		auto it = g_game().browseFields.find(getTile());
		if (it != g_game().browseFields.end()) {
			auto lockedCylinder = it->second.lock();
			if (lockedCylinder) {
				lockedCylinder->removeThing(item, item->getItemCount());
			}
		}
	}
	for (auto &zone : getZones()) {
		zone->itemRemoved(item);
	}

	resetTileFlags(item);

	const Position &cylinderMapPos = getPosition();
	const ItemType &iType = Item::items[item->getID()];

	// send to client
	size_t i = 0;
	for (std::shared_ptr<Creature> spectator : spectators) {
		if (std::shared_ptr<Player> tmpPlayer = spectator->getPlayer()) {
			tmpPlayer->sendRemoveTileThing(cylinderMapPos, oldStackPosVector[i++]);
		}
	}

	// event methods
	for (std::shared_ptr<Creature> spectator : spectators) {
		spectator->onRemoveTileItem(static_self_cast<Tile>(), cylinderMapPos, iType, item);
	}

	if (!hasFlag(TILESTATE_PROTECTIONZONE) || g_configManager().getBoolean(CLEAN_PROTECTION_ZONES)) {
		auto items = getItemList();
		if (!items || items->empty()) {
			g_game().removeTileToClean(static_self_cast<Tile>());
			return;
		}

		bool ret = false;
		for (auto toCheck : *items) {
			if (toCheck->isCleanable()) {
				ret = true;
				break;
			}
		}

		if (!ret) {
			g_game().removeTileToClean(static_self_cast<Tile>());
		}
	}

	if (item->isCarpet() && !item->isMoveable()) {
		if (getTopTopItem() && getTopTopItem()->canReceiveAutoCarpet()) {
			return;
		}
		auto house = getHouse();
		if (!house) {
			return;
		}

		for (const auto &tile : getSurroundingTiles()) {
			if (!tile || !tile->getGround() || tile->getGround()->getID() != getGround()->getID()) {
				continue;
			}
			auto topItem = tile->getTopTopItem();
			if (!topItem || !topItem->canReceiveAutoCarpet()) {
				continue;
			}
			// Check if tile is part of the same house
			if (auto tileHouse = tile->getHouse(); !tileHouse || house != tileHouse) {
				continue;
			}

			for (auto tileItem : *tile->getItemList()) {
				if (tileItem && tileItem->getID() == item->getID()) {
					tile->removeThing(tileItem, tileItem->getItemCount());
				}
			}
		}
	}
}

void Tile::onUpdateTile(const CreatureVector &spectators) {
	const Position &cylinderMapPos = getPosition();

	// send to clients
	for (std::shared_ptr<Creature> spectator : spectators) {
		spectator->getPlayer()->sendUpdateTile(getTile(), cylinderMapPos);
	}
}

ReturnValue Tile::queryAdd(int32_t, const std::shared_ptr<Thing> &thing, uint32_t, uint32_t tileFlags, std::shared_ptr<Creature>) {
	if (hasBitSet(FLAG_NOLIMIT, tileFlags)) {
		return RETURNVALUE_NOERROR;
	}

	if (auto creature = thing->getCreature()) {
		if (creature->getNpc()) {
			ReturnValue returnValue = checkNpcCanWalkIntoTile();
			if (returnValue != RETURNVALUE_NOERROR) {
				return returnValue;
			}
		}

		if (hasBitSet(FLAG_PATHFINDING, tileFlags) && hasFlag(TILESTATE_FLOORCHANGE | TILESTATE_TELEPORT)) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		if (creature->isMoveLocked() || ground == nullptr) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		if (std::shared_ptr<Monster> monster = creature->getMonster()) {
			if (hasFlag(TILESTATE_PROTECTIONZONE | TILESTATE_FLOORCHANGE | TILESTATE_TELEPORT) && (!monster->isFamiliar() || (monster->isFamiliar() && monster->getMaster() && monster->getMaster()->getAttackedCreature()))) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (monster->isSummon()) {
				if (ground->getID() >= ITEM_WALKABLE_SEA_START && ground->getID() <= ITEM_WALKABLE_SEA_END) {
					return RETURNVALUE_NOTPOSSIBLE;
				}
			}

			const CreatureVector* creatures = getCreatures();
			if (monster->canPushCreatures() && !monster->isSummon()) {
				if (creatures) {
					for (auto &tileCreature : *creatures) {
						if (tileCreature->getPlayer() && tileCreature->getPlayer()->isInGhostMode()) {
							continue;
						}

						std::shared_ptr<Monster> creatureMonster = tileCreature->getMonster();
						if (!creatureMonster || !tileCreature->isPushable() || (creatureMonster->isSummon() && creatureMonster->getMaster()->getPlayer())) {
							return RETURNVALUE_NOTPOSSIBLE;
						}
					}
				}
			} else if (creatures && !creatures->empty()) {
				for (auto &tileCreature : *creatures) {
					if (!tileCreature->isInGhostMode()) {
						return RETURNVALUE_NOTENOUGHROOM;
					}
				}
			}

			if (hasFlag(TILESTATE_IMMOVABLEBLOCKSOLID)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (hasBitSet(FLAG_PATHFINDING, tileFlags) && hasFlag(TILESTATE_IMMOVABLENOFIELDBLOCKPATH)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (hasFlag(TILESTATE_BLOCKSOLID) || (hasBitSet(FLAG_PATHFINDING, tileFlags) && hasFlag(TILESTATE_NOFIELDBLOCKPATH))) {
				if (!(monster->canPushItems() || hasBitSet(FLAG_IGNOREBLOCKITEM, tileFlags))) {
					return RETURNVALUE_NOTPOSSIBLE;
				}
			}

			if (hasHarmfulField()) {
				CombatType_t combatType = getFieldItem()->getCombatType();

				// There is 3 options for a monster to enter a magic field
				// 1) Monster is immune
				if (!monster->isImmune(combatType)) {
					// 1) Monster is able to walk over field type
					// 2) Being attacked while random stepping will make it ignore field damages
					if (hasBitSet(FLAG_IGNOREFIELDDAMAGE, tileFlags)) {
						if (!(monster->getIgnoreFieldDamage() || monster->canWalkOnFieldType(combatType))) {
							return RETURNVALUE_NOTPOSSIBLE;
						}
					} else {
						return RETURNVALUE_NOTPOSSIBLE;
					}
				}
			}

			return RETURNVALUE_NOERROR;
		}

		const CreatureVector* creatures = getCreatures();
		if (std::shared_ptr<Player> player = creature->getPlayer()) {
			if (creatures && !creatures->empty() && !hasBitSet(FLAG_IGNOREBLOCKCREATURE, tileFlags) && !player->isAccessPlayer()) {
				for (auto &tileCreature : *creatures) {
					if (!player->canWalkthrough(tileCreature)) {
						return RETURNVALUE_NOTPOSSIBLE;
					}
				}
			}

			if (hasBitSet(FLAG_PATHFINDING, tileFlags) && hasFlag(TILESTATE_BLOCKPATH)) {
				return RETURNVALUE_NOTPOSSIBLE;
			}

			if (player->getParent() == nullptr && hasFlag(TILESTATE_NOLOGOUT)) {
				// player is trying to login to a "no logout" tile
				return RETURNVALUE_NOTPOSSIBLE;
			}

			const auto playerTile = player->getTile();
			if (playerTile && player->isPzLocked()) {
				if (!playerTile->hasFlag(TILESTATE_PVPZONE)) {
					// player is trying to enter a pvp zone while being pz-locked
					if (hasFlag(TILESTATE_PVPZONE)) {
						return RETURNVALUE_PLAYERISPZLOCKEDENTERPVPZONE;
					}
				} else if (!hasFlag(TILESTATE_PVPZONE)) {
					// player is trying to leave a pvp zone while being pz-locked
					return RETURNVALUE_PLAYERISPZLOCKEDLEAVEPVPZONE;
				}

				if ((!playerTile->hasFlag(TILESTATE_NOPVPZONE) && hasFlag(TILESTATE_NOPVPZONE)) || (!playerTile->hasFlag(TILESTATE_PROTECTIONZONE) && hasFlag(TILESTATE_PROTECTIONZONE))) {
					// player is trying to enter a non-pvp/protection zone while being pz-locked
					return RETURNVALUE_PLAYERISPZLOCKED;
				}
			}
		} else if (creatures && !creatures->empty() && !hasBitSet(FLAG_IGNOREBLOCKCREATURE, tileFlags)) {
			for (auto &tileCreature : *creatures) {
				if (!tileCreature->isInGhostMode()) {
					return RETURNVALUE_NOTENOUGHROOM;
				}
			}
		}

		if (!hasBitSet(FLAG_IGNOREBLOCKITEM, tileFlags)) {
			// If the FLAG_IGNOREBLOCKITEM bit isn't set we dont have to iterate every single item
			if (hasFlag(TILESTATE_BLOCKSOLID)) {
				// NO PVP magic wall or wild growth field check
				if (creature && creature->getPlayer()) {
					if (const auto fieldList = getItemList()) {
						for (auto &findfield : *fieldList) {
							if (findfield && (findfield->getID() == ITEM_WILDGROWTH_SAFE || findfield->getID() == ITEM_MAGICWALL_SAFE)) {
								if (!creature->isInGhostMode()) {
									g_game().internalRemoveItem(findfield, 1);
								}
								return RETURNVALUE_NOERROR;
							}
						}
					}
				}
				return RETURNVALUE_NOTENOUGHROOM;
			}
		} else {
			// FLAG_IGNOREBLOCKITEM is set
			if (ground) {
				const ItemType &iiType = Item::items[ground->getID()];
				if (iiType.blockSolid && (!iiType.moveable || ground->hasAttribute(ItemAttribute_t::UNIQUEID))) {
					return RETURNVALUE_NOTPOSSIBLE;
				}
			}

			if (const auto items = getItemList()) {
				for (auto &item : *items) {
					const ItemType &iiType = Item::items[item->getID()];
					if (iiType.blockSolid && (!iiType.moveable || item->hasAttribute(ItemAttribute_t::UNIQUEID))) {
						return RETURNVALUE_NOTPOSSIBLE;
					}
				}
			}
		}
	} else if (auto item = thing->getItem()) {
		const TileItemVector* items = getItemList();
		if (items && items->size() >= 0x3E8) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		bool itemIsHangable = item->isHangable();
		if (ground == nullptr && !itemIsHangable) {
			return RETURNVALUE_NOTPOSSIBLE;
		}

		const CreatureVector* creatures = getCreatures();
		if (creatures && !creatures->empty() && item->isBlocking() && !hasBitSet(FLAG_IGNOREBLOCKCREATURE, tileFlags)) {
			for (auto &tileCreature : *creatures) {
				if (!tileCreature->isInGhostMode()) {
					return RETURNVALUE_NOTENOUGHROOM;
				}
			}
		}

		if (itemIsHangable && hasFlag(TILESTATE_SUPPORTS_HANGABLE)) {
			if (items) {
				for (auto &tileItem : *items) {
					if (tileItem->isHangable()) {
						return RETURNVALUE_NEEDEXCHANGE;
					}
				}
			}
		} else {
			if (ground) {
				const ItemType &iiType = Item::items[ground->getID()];
				if (iiType.blockSolid) {
					if (!iiType.pickupable && iiType.type != ITEM_TYPE_TRASHHOLDER || item->isMagicField() || item->isBlocking()) {
						if (!item->isPickupable() && !item->isCarpet()) {
							return RETURNVALUE_NOTENOUGHROOM;
						}

						if (!iiType.hasHeight) {
							return RETURNVALUE_NOTENOUGHROOM;
						}
					}
				}
			}

			if (items) {
				for (auto &tileItem : *items) {
					const ItemType &iiType = Item::items[tileItem->getID()];
					if (!iiType.blockSolid || iiType.type == ITEM_TYPE_TRASHHOLDER) {
						continue;
					}

					if (iiType.pickupable && !item->isMagicField() && !item->isBlocking()) {
						continue;
					}

					if (!item->isPickupable()) {
						return RETURNVALUE_NOTENOUGHROOM;
					}

					if (!iiType.hasHeight || iiType.pickupable) {
						return RETURNVALUE_NOTENOUGHROOM;
					}
				}
			}
		}
	}
	return RETURNVALUE_NOERROR;
}

ReturnValue Tile::checkNpcCanWalkIntoTile() const {
	if (hasHarmfulField()) {
		return RETURNVALUE_NOTPOSSIBLE;
	} else {
		return RETURNVALUE_NOERROR;
	}
}

bool Tile::hasHarmfulField() const {
	return hasFlag(TILESTATE_MAGICFIELD) && getFieldItem() && !getFieldItem()->isBlocking() && getFieldItem()->getDamage() > 0;
}

ReturnValue Tile::queryMaxCount(int32_t, const std::shared_ptr<Thing> &, uint32_t count, uint32_t &maxQueryCount, uint32_t) {
	maxQueryCount = std::max<uint32_t>(1, count);
	return RETURNVALUE_NOERROR;
}

ReturnValue Tile::queryRemove(const std::shared_ptr<Thing> &thing, uint32_t count, uint32_t tileFlags, std::shared_ptr<Creature> /*= nullptr */) {
	int32_t index = getThingIndex(thing);
	if (index == -1) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	std::shared_ptr<Item> item = thing->getItem();
	if (item == nullptr) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (count == 0 || (item->isStackable() && count > item->getItemCount())) {
		return RETURNVALUE_NOTPOSSIBLE;
	}

	if (!item->isMoveable() && !hasBitSet(FLAG_IGNORENOTMOVEABLE, tileFlags)) {
		return RETURNVALUE_NOTMOVEABLE;
	}

	return RETURNVALUE_NOERROR;
}

std::shared_ptr<Cylinder> Tile::queryDestination(int32_t &, const std::shared_ptr<Thing> &, std::shared_ptr<Item>* destItem, uint32_t &tileFlags) {
	std::shared_ptr<Tile> destTile = nullptr;
	*destItem = nullptr;

	if (hasFlag(TILESTATE_FLOORCHANGE_DOWN)) {
		uint16_t dx = tilePos.x;
		uint16_t dy = tilePos.y;
		uint8_t dz = tilePos.z + 1;

		std::shared_ptr<Tile> southDownTile = g_game().map.getTile(dx, dy - 1, dz);
		if (southDownTile && southDownTile->hasFlag(TILESTATE_FLOORCHANGE_SOUTH_ALT)) {
			dy -= 2;
			destTile = g_game().map.getTile(dx, dy, dz);
		} else {
			std::shared_ptr<Tile> eastDownTile = g_game().map.getTile(dx - 1, dy, dz);
			if (eastDownTile && eastDownTile->hasFlag(TILESTATE_FLOORCHANGE_EAST_ALT)) {
				dx -= 2;
				destTile = g_game().map.getTile(dx, dy, dz);
			} else {
				std::shared_ptr<Tile> downTile = g_game().map.getTile(dx, dy, dz);
				if (downTile) {
					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_NORTH)) {
						++dy;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_SOUTH)) {
						--dy;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_SOUTH_ALT)) {
						dy -= 2;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_EAST)) {
						--dx;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_EAST_ALT)) {
						dx -= 2;
					}

					if (downTile->hasFlag(TILESTATE_FLOORCHANGE_WEST)) {
						++dx;
					}

					destTile = g_game().map.getTile(dx, dy, dz);
				}
			}
		}
	} else if (hasFlag(TILESTATE_FLOORCHANGE)) {
		uint16_t dx = tilePos.x;
		uint16_t dy = tilePos.y;
		uint8_t dz = tilePos.z - 1;

		if (hasFlag(TILESTATE_FLOORCHANGE_NORTH)) {
			--dy;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_SOUTH)) {
			++dy;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_EAST)) {
			++dx;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_WEST)) {
			--dx;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_SOUTH_ALT)) {
			dy += 2;
		}

		if (hasFlag(TILESTATE_FLOORCHANGE_EAST_ALT)) {
			dx += 2;
		}

		destTile = g_game().map.getTile(dx, dy, dz);
	}

	if (destTile == nullptr) {
		destTile = static_self_cast<Tile>();
	} else {
		tileFlags |= FLAG_NOLIMIT; // Will ignore that there is blocking items/creatures
	}

	if (destTile) {
		std::shared_ptr<Thing> destThing = destTile->getTopDownItem();
		if (destThing) {
			*destItem = destThing->getItem();
		}
	}
	return destTile;
}

std::vector<std::shared_ptr<Tile>> Tile::getSurroundingTiles() {
	const auto position = getPosition();
	return {
		g_game().map.getTile(position.x - 1, position.y, position.z),
		g_game().map.getTile(position.x + 1, position.y, position.z),
		g_game().map.getTile(position.x, position.y - 1, position.z),
		g_game().map.getTile(position.x, position.y + 1, position.z),
		g_game().map.getTile(position.x - 1, position.y - 1, position.z),
		g_game().map.getTile(position.x + 1, position.y + 1, position.z),
		g_game().map.getTile(position.x + 1, position.y - 1, position.z),
		g_game().map.getTile(position.x - 1, position.y + 1, position.z)
	};
}

void Tile::addThing(std::shared_ptr<Thing> thing) {
	addThing(0, thing);
}

void Tile::addThing(int32_t, std::shared_ptr<Thing> thing) {
	if (!thing) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	std::shared_ptr<Creature> creature = thing->getCreature();
	if (creature) {
		Spectators::clearCache();
		creature->setParent(static_self_cast<Tile>());

		CreatureVector* creatures = makeCreatures();
		creatures->insert(creatures->begin(), creature);
	} else {
		std::shared_ptr<Item> item = thing->getItem();
		if (item == nullptr) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		TileItemVector* items = getItemList();
		if (items && items->size() >= 0xFFFF) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		item->setParent(static_self_cast<Tile>());

		const ItemType &itemType = Item::items[item->getID()];
		if (itemType.isGroundTile()) {
			if (ground == nullptr) {
				ground = item;
				onAddTileItem(item);
			} else {
				const ItemType &oldType = Item::items[ground->getID()];

				std::shared_ptr<Item> oldGround = ground;
				ground->resetParent();
				ground = item;
				resetTileFlags(oldGround);
				setTileFlags(item);
				onUpdateTileItem(oldGround, oldType, item, itemType);
				postRemoveNotification(oldGround, nullptr, 0);
			}
		} else if (item->isAlwaysOnTop()) {
			if (itemType.isSplash() && items) {
				// remove old splash if exists
				for (ItemVector::const_iterator it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
					std::shared_ptr<Item> oldSplash = *it;
					if (!Item::items[oldSplash->getID()].isSplash()) {
						continue;
					}

					removeThing(oldSplash, 1);
					oldSplash->resetParent();
					postRemoveNotification(oldSplash, nullptr, 0);
					break;
				}
			}

			bool isInserted = false;

			if (items) {
				for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
					// Note: this is different from internalAddThing
					if (itemType.alwaysOnTopOrder <= Item::items[(*it)->getID()].alwaysOnTopOrder) {
						items->insert(it, item);
						isInserted = true;
						break;
					}
				}
			} else {
				items = makeItemList();
			}

			if (!isInserted) {
				items->push_back(item);
			}

			onAddTileItem(item);
		} else {
			if (itemType.isMagicField()) {
				// remove old field item if exists
				if (items) {
					for (ItemVector::const_iterator it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
						std::shared_ptr<MagicField> oldField = (*it)->getMagicField();
						if (oldField) {
							if (oldField->isReplaceable()) {
								removeThing(oldField, 1);

								oldField->resetParent();
								postRemoveNotification(oldField, nullptr, 0);
								break;
							} else {
								// This magic field cannot be replaced.
								item->resetParent();
								return;
							}
						}
					}
				}
			}

			items = makeItemList();
			items->insert(items->getBeginDownItem(), item);
			items->increaseDownItemCount();
			onAddTileItem(item);
		}
	}
}

void Tile::updateThing(std::shared_ptr<Thing> thing, uint16_t itemId, uint32_t count) {
	int32_t index = getThingIndex(thing);
	if (index == -1) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	std::shared_ptr<Item> item = thing->getItem();
	if (item == nullptr) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	const ItemType &oldType = Item::items[item->getID()];
	const ItemType &newType = Item::items[itemId];
	resetTileFlags(item);
	item->setID(itemId);
	item->setSubType(count);
	setTileFlags(item);
	onUpdateTileItem(item, oldType, item, newType);
}

void Tile::replaceThing(uint32_t index, std::shared_ptr<Thing> thing) {
	int32_t pos = index;

	std::shared_ptr<Item> item = thing->getItem();
	if (item == nullptr) {
		return /*RETURNVALUE_NOTPOSSIBLE*/;
	}

	std::shared_ptr<Item> oldItem = nullptr;
	bool isInserted = false;

	if (ground) {
		if (pos == 0) {
			oldItem = ground;
			ground = item;
			isInserted = true;
		}

		--pos;
	}

	TileItemVector* items = getItemList();
	if (items && !isInserted) {
		int32_t topItemSize = getTopItemCount();
		if (pos < topItemSize) {
			auto it = items->getBeginTopItem();
			it += pos;

			oldItem = (*it);
			it = items->erase(it);
			items->insert(it, item);
			isInserted = true;
		}

		pos -= topItemSize;
	}

	CreatureVector* creatures = getCreatures();
	if (creatures) {
		if (!isInserted && pos < static_cast<int32_t>(creatures->size())) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		pos -= static_cast<uint32_t>(creatures->size());
	}

	if (items && !isInserted) {
		int32_t downItemSize = getDownItemCount();
		if (pos < downItemSize) {
			auto it = items->getBeginDownItem() + pos;
			oldItem = *it;
			it = items->erase(it);
			items->insert(it, item);
			isInserted = true;
		}
	}

	if (isInserted) {
		item->setParent(static_self_cast<Tile>());

		resetTileFlags(oldItem);
		setTileFlags(item);
		const ItemType &oldType = Item::items[oldItem->getID()];
		const ItemType &newType = Item::items[item->getID()];
		onUpdateTileItem(oldItem, oldType, item, newType);

		oldItem->resetParent();
		return /*RETURNVALUE_NOERROR*/;
	}
}

void Tile::removeThing(std::shared_ptr<Thing> thing, uint32_t count) {
	std::shared_ptr<Creature> creature = thing->getCreature();
	if (creature) {
		CreatureVector* creatures = getCreatures();
		if (creatures) {
			auto it = std::find(creatures->begin(), creatures->end(), thing);
			if (it != creatures->end()) {
				Spectators::clearCache();
				creatures->erase(it);
			}
		}
		return;
	}

	std::shared_ptr<Item> item = thing->getItem();
	if (!item) {
		return;
	}

	int32_t index = getThingIndex(item);
	if (index == -1) {
		return;
	}

	if (item == ground) {
		ground->resetParent();
		ground = nullptr;

		auto spectators = Spectators().find<Creature>(getPosition(), true);
		onRemoveTileItem(spectators.data(), std::vector<int32_t>(spectators.size(), 0), item);
		return;
	}

	TileItemVector* items = getItemList();
	if (!items) {
		return;
	}

	if (item->isAlwaysOnTop()) {
		auto it = std::find(items->getBeginTopItem(), items->getEndTopItem(), item);
		if (it == items->getEndTopItem()) {
			return;
		}

		std::vector<int32_t> oldStackPosVector;

		auto spectators = Spectators().find<Creature>(getPosition(), true);
		for (const auto &spectator : spectators) {
			if (const auto &tmpPlayer = spectator->getPlayer()) {
				oldStackPosVector.push_back(getStackposOfItem(tmpPlayer, item));
			}
		}

		item->resetParent();
		items->erase(it);
		onRemoveTileItem(spectators.data(), oldStackPosVector, item);
	} else {
		auto it = std::find(items->getBeginDownItem(), items->getEndDownItem(), item);
		if (it == items->getEndDownItem()) {
			return;
		}

		const ItemType &itemType = Item::items[item->getID()];
		if (itemType.stackable && count != item->getItemCount()) {
			uint8_t newCount = static_cast<uint8_t>(std::max<int32_t>(0, static_cast<int32_t>(item->getItemCount() - count)));
			item->setItemCount(newCount);
			onUpdateTileItem(item, itemType, item, itemType);
		} else {
			std::vector<int32_t> oldStackPosVector;

			auto spectators = Spectators().find<Creature>(getPosition(), true);
			for (const auto &spectator : spectators) {
				if (const auto &tmpPlayer = spectator->getPlayer()) {
					oldStackPosVector.push_back(getStackposOfItem(spectator->getPlayer(), item));
				}
			}

			item->resetParent();
			items->erase(it);
			items->decreaseDownItemCount();
			onRemoveTileItem(spectators.data(), oldStackPosVector, item);
		}
	}
}

void Tile::removeCreature(std::shared_ptr<Creature> creature) {
	g_game().map.getQTNode(tilePos.x, tilePos.y)->removeCreature(creature);
	removeThing(creature, 0);
}

int32_t Tile::getThingIndex(std::shared_ptr<Thing> thing) const {
	int32_t n = -1;
	if (ground) {
		if (ground == thing) {
			return 0;
		}
		++n;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		std::shared_ptr<Item> item = thing->getItem();
		if (item && item->isAlwaysOnTop()) {
			for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
				++n;
				if (*it == item) {
					return n;
				}
			}
		} else {
			n += items->getTopItemCount();
		}
	}

	if (const CreatureVector* creatures = getCreatures()) {
		if (thing->getCreature()) {
			for (auto &creature : *creatures) {
				++n;
				if (creature == thing) {
					return n;
				}
			}
		} else {
			n += creatures->size();
		}
	}

	if (items) {
		std::shared_ptr<Item> item = thing->getItem();
		if (item && !item->isAlwaysOnTop()) {
			for (auto it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
				++n;
				if (*it == item) {
					return n;
				}
			}
		}
	}
	return -1;
}

int32_t Tile::getClientIndexOfCreature(std::shared_ptr<Player> player, std::shared_ptr<Creature> creature) const {
	int32_t n;
	if (ground) {
		n = 1;
	} else {
		n = 0;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		n += items->getTopItemCount();
	}

	if (const CreatureVector* creatures = getCreatures()) {
		for (auto it = creatures->rbegin(); it != creatures->rend(); ++it) {
			if (*it == creature) {
				return n;
			} else if (player->canSeeCreature(*it)) {
				++n;
			}
		}
	}
	return -1;
}

int32_t Tile::getStackposOfCreature(std::shared_ptr<Player> player, std::shared_ptr<Creature> creature) const {
	int32_t n;
	if (ground) {
		n = 1;
	} else {
		n = 0;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		n += items->getTopItemCount();
		if (n >= 10) {
			return -1;
		}
	}

	if (const CreatureVector* creatures = getCreatures()) {
		for (auto it = creatures->rbegin(); it != creatures->rend(); ++it) {
			if (*it == creature) {
				return n;
			} else if (player->canSeeCreature(*it)) {
				if (++n >= 10) {
					return -1;
				}
			}
		}
	}
	return -1;
}

int32_t Tile::getStackposOfItem(std::shared_ptr<Player> player, std::shared_ptr<Item> item) const {
	int32_t n = 0;
	if (ground) {
		if (ground == item) {
			return n;
		}
		++n;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		if (item->isAlwaysOnTop()) {
			for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
				if (*it == item) {
					return n;
				} else if (++n == 10) {
					return -1;
				}
			}
		} else {
			n += items->getTopItemCount();
			if (n >= 10) {
				return -1;
			}
		}
	}

	if (const CreatureVector* creatures = getCreatures()) {
		for (auto &creature : *creatures) {
			if (player->canSeeCreature(creature)) {
				if (++n >= 10) {
					return -1;
				}
			}
		}
	}

	if (items && !item->isAlwaysOnTop()) {
		for (auto it = items->getBeginDownItem(), end = items->getEndDownItem(); it != end; ++it) {
			if (*it == item) {
				return n;
			} else if (++n >= 10) {
				return -1;
			}
		}
	}
	return -1;
}

size_t Tile::getFirstIndex() const {
	return 0;
}

size_t Tile::getLastIndex() const {
	return getThingCount();
}

uint32_t Tile::getItemTypeCount(uint16_t itemId, int32_t subType /*= -1*/) const {
	uint32_t count = 0;
	if (ground && ground->getID() == itemId) {
		count += Item::countByType(ground, subType);
	}

	const TileItemVector* items = getItemList();
	if (items) {
		for (auto &item : *items) {
			if (item->getID() == itemId) {
				count += Item::countByType(item, subType);
			}
		}
	}
	return count;
}

std::shared_ptr<Thing> Tile::getThing(size_t index) const {
	if (ground) {
		if (index == 0) {
			return ground;
		}

		--index;
	}

	const TileItemVector* items = getItemList();
	if (items) {
		uint32_t topItemSize = items->getTopItemCount();
		if (index < topItemSize) {
			return items->at(items->getDownItemCount() + index);
		}
		index -= topItemSize;
	}

	if (const CreatureVector* creatures = getCreatures()) {
		if (index < creatures->size()) {
			return (*creatures)[index];
		}
		index -= creatures->size();
	}

	if (items && index < items->getDownItemCount()) {
		return items->at(index);
	}
	return nullptr;
}

void Tile::postAddNotification(std::shared_ptr<Thing> thing, std::shared_ptr<Cylinder> oldParent, int32_t index, CylinderLink_t link /*= LINK_OWNER*/) {
	for (const auto &spectator : Spectators().find<Player>(getPosition(), true)) {
		spectator->getPlayer()->postAddNotification(thing, oldParent, index, LINK_NEAR);
	}

	// add a reference to this item, it may be deleted after being added (mailbox for example)
	std::shared_ptr<Creature> creature = thing->getCreature();
	std::shared_ptr<Item> item;
	if (creature) {
		item = nullptr;
	} else {
		item = thing->getItem();
	}

	if (link == LINK_OWNER) {
		if (hasFlag(TILESTATE_TELEPORT)) {
			std::shared_ptr<Teleport> teleport = getTeleportItem();
			if (teleport) {
				teleport->addThing(thing);
			}
		} else if (hasFlag(TILESTATE_TRASHHOLDER)) {
			std::shared_ptr<TrashHolder> trashholder = getTrashHolder();
			if (trashholder) {
				trashholder->addThing(thing);
			}
		} else if (hasFlag(TILESTATE_MAILBOX)) {
			std::shared_ptr<Mailbox> mailbox = getMailbox();
			if (mailbox) {
				mailbox->addThing(thing);
			}
		}

		// calling movement scripts
		if (creature) {
			g_moveEvents().onCreatureMove(creature, static_self_cast<Tile>(), MOVE_EVENT_STEP_IN);
		} else if (item) {
			g_moveEvents().onItemMove(item, static_self_cast<Tile>(), true);
		}
	}
}

void Tile::postRemoveNotification(std::shared_ptr<Thing> thing, std::shared_ptr<Cylinder> newParent, int32_t index, CylinderLink_t) {
	auto spectators = Spectators().find<Player>(getPosition(), true);

	if (getThingCount() > 8) {
		onUpdateTile(spectators.data());
	}

	for (const auto &spectator : spectators) {
		spectator->getPlayer()->postRemoveNotification(thing, newParent, index, LINK_NEAR);
	}

	// calling movement scripts
	std::shared_ptr<Creature> creature = thing->getCreature();
	if (creature) {
		g_moveEvents().onCreatureMove(creature, static_self_cast<Tile>(), MOVE_EVENT_STEP_OUT);
	} else {
		std::shared_ptr<Item> item = thing->getItem();
		if (item) {
			g_moveEvents().onItemMove(item, static_self_cast<Tile>(), false);
		}
	}
}

void Tile::internalAddThing(std::shared_ptr<Thing> thing) {
	internalAddThing(0, thing);
	if (!thing || !thing->getParent()) {
		return;
	}

	if (auto house = thing->getTile()->getHouse()) {
		if (std::shared_ptr<Item> item = thing->getItem()) {
			if (item->getParent().get() != this) {
				return;
			}

			std::shared_ptr<Door> door = item->getDoor();
			if (door && door->getDoorId() != 0) {
				house->addDoor(door);
			}
		}
	}
}

void Tile::internalAddThing(uint32_t, std::shared_ptr<Thing> thing) {
	if (!thing) {
		return;
	}
	for (const auto zone : getZones()) {
		zone->thingAdded(thing);
	}

	thing->setParent(static_self_cast<Tile>());

	std::shared_ptr<Creature> creature = thing->getCreature();
	if (creature) {
		Spectators::clearCache();

		CreatureVector* creatures = makeCreatures();
		creatures->insert(creatures->begin(), creature);
	} else {
		std::shared_ptr<Item> item = thing->getItem();
		if (item == nullptr) {
			return;
		}

		const ItemType &itemType = Item::items[item->getID()];
		if (itemType.isGroundTile()) {
			if (ground == nullptr) {
				ground = item;
				setTileFlags(item);
			}
			return;
		}

		TileItemVector* items = makeItemList();
		if (items->size() >= 0xFFFF) {
			return /*RETURNVALUE_NOTPOSSIBLE*/;
		}

		if (item->isAlwaysOnTop()) {
			bool isInserted = false;
			for (auto it = items->getBeginTopItem(), end = items->getEndTopItem(); it != end; ++it) {
				if (Item::items[(*it)->getID()].alwaysOnTopOrder > itemType.alwaysOnTopOrder) {
					items->insert(it, item);
					isInserted = true;
					break;
				}
			}

			if (!isInserted) {
				items->push_back(item);
			}
		} else {
			items->insert(items->getBeginDownItem(), item);
			items->increaseDownItemCount();
		}

		setTileFlags(item);
	}
}

void Tile::updateTileFlags(const std::shared_ptr<Item> &item) {
	resetTileFlags(item);
	setTileFlags(item);
}

void Tile::setTileFlags(const std::shared_ptr<Item> &item) {
	if (!hasFlag(TILESTATE_FLOORCHANGE)) {
		const auto &it = Item::items[item->getID()];
		if (it.floorChange != 0) {
			setFlag(it.floorChange);
		}
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLEBLOCKSOLID)) {
		setFlag(TILESTATE_IMMOVABLEBLOCKSOLID);
	}

	if (item->hasProperty(CONST_PROP_BLOCKPATH)) {
		setFlag(TILESTATE_BLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_NOFIELDBLOCKPATH)) {
		setFlag(TILESTATE_NOFIELDBLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLENOFIELDBLOCKPATH)) {
		setFlag(TILESTATE_IMMOVABLENOFIELDBLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_SUPPORTHANGABLE)) {
		setFlag(TILESTATE_SUPPORTS_HANGABLE);
	}

	if (item->getTeleport()) {
		setFlag(TILESTATE_TELEPORT);
	}

	if (item->getMagicField()) {
		setFlag(TILESTATE_MAGICFIELD);
	}

	if (item->getMailbox()) {
		setFlag(TILESTATE_MAILBOX);
	}

	if (item->getTrashHolder()) {
		setFlag(TILESTATE_TRASHHOLDER);
	}

	if (item->hasProperty(CONST_PROP_BLOCKSOLID)) {
		setFlag(TILESTATE_BLOCKSOLID);
	}

	if (item->getBed()) {
		setFlag(TILESTATE_BED);
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLEBLOCKPATH)) {
		setFlag(TILESTATE_IMMOVABLEBLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_MOVEABLE)) {
		setFlag(TILESTATE_MOVEABLE);
	}

	if (item->hasProperty(CONST_PROP_ISHORIZONTAL)) {
		setFlag(TILESTATE_ISHORIZONTAL);
	}

	if (item->hasProperty(CONST_PROP_ISVERTICAL)) {
		setFlag(TILESTATE_ISVERTICAL);
	}

	if (item->hasProperty(CONST_PROP_BLOCKPROJECTILE)) {
		setFlag(TILESTATE_BLOCKPROJECTILE);
	}

	if (item->hasProperty(CONST_PROP_HASHEIGHT)) {
		setFlag(TILESTATE_HASHEIGHT);
	}

	if (const auto &container = item->getContainer()) {
		if (container->getDepotLocker()) {
			setFlag(TILESTATE_DEPOT);
		}
	}

	if (item->hasProperty(CONST_PROP_SUPPORTHANGABLE)) {
		setFlag(TILESTATE_SUPPORTS_HANGABLE);
	}
}

void Tile::resetTileFlags(const std::shared_ptr<Item> &item) {
	const ItemType &it = Item::items[item->getID()];
	if (it.floorChange != 0) {
		resetFlag(TILESTATE_FLOORCHANGE);
	}

	if (item->hasProperty(CONST_PROP_BLOCKSOLID) && !hasProperty(item, CONST_PROP_BLOCKSOLID)) {
		resetFlag(TILESTATE_BLOCKSOLID);
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLEBLOCKSOLID) && !hasProperty(item, CONST_PROP_IMMOVABLEBLOCKSOLID)) {
		resetFlag(TILESTATE_IMMOVABLEBLOCKSOLID);
	}

	if (item->hasProperty(CONST_PROP_BLOCKPATH) && !hasProperty(item, CONST_PROP_BLOCKPATH)) {
		resetFlag(TILESTATE_BLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_NOFIELDBLOCKPATH) && !hasProperty(item, CONST_PROP_NOFIELDBLOCKPATH)) {
		resetFlag(TILESTATE_NOFIELDBLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLEBLOCKPATH) && !hasProperty(item, CONST_PROP_IMMOVABLEBLOCKPATH)) {
		resetFlag(TILESTATE_IMMOVABLEBLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_IMMOVABLENOFIELDBLOCKPATH) && !hasProperty(item, CONST_PROP_IMMOVABLENOFIELDBLOCKPATH)) {
		resetFlag(TILESTATE_IMMOVABLENOFIELDBLOCKPATH);
	}

	if (item->hasProperty(CONST_PROP_MOVEABLE) && !hasProperty(item, CONST_PROP_MOVEABLE)) {
		resetFlag(TILESTATE_MOVEABLE);
	}

	if (item->hasProperty(CONST_PROP_ISHORIZONTAL) && !hasProperty(item, CONST_PROP_ISHORIZONTAL)) {
		resetFlag(TILESTATE_ISHORIZONTAL);
	}

	if (item->hasProperty(CONST_PROP_ISVERTICAL) && !hasProperty(item, CONST_PROP_ISVERTICAL)) {
		resetFlag(TILESTATE_ISVERTICAL);
	}

	if (item->hasProperty(CONST_PROP_BLOCKPROJECTILE) && !hasProperty(item, CONST_PROP_BLOCKPROJECTILE)) {
		resetFlag(TILESTATE_BLOCKPROJECTILE);
	}

	if (item->hasProperty(CONST_PROP_HASHEIGHT) && !hasProperty(item, CONST_PROP_HASHEIGHT)) {
		resetFlag(TILESTATE_HASHEIGHT);
	}

	if (item->getTeleport()) {
		resetFlag(TILESTATE_TELEPORT);
	}

	if (item->getMagicField()) {
		resetFlag(TILESTATE_MAGICFIELD);
	}

	if (item->getMailbox()) {
		resetFlag(TILESTATE_MAILBOX);
	}

	if (item->getTrashHolder()) {
		resetFlag(TILESTATE_TRASHHOLDER);
	}

	if (item->getBed()) {
		resetFlag(TILESTATE_BED);
	}

	if (const auto &container = item->getContainer()) {
		if (container->getDepotLocker()) {
			resetFlag(TILESTATE_DEPOT);
		}
	}

	if (item->hasProperty(CONST_PROP_SUPPORTHANGABLE)) {
		resetFlag(TILESTATE_SUPPORTS_HANGABLE);
	}
}

bool Tile::isMoveableBlocking() const {
	return !ground || hasFlag(TILESTATE_BLOCKSOLID);
}

std::shared_ptr<Item> Tile::getUseItem(int32_t index) const {
	const TileItemVector* items = getItemList();
	if (!items || items->size() == 0) {
		return ground;
	}

	if (std::shared_ptr<Thing> thing = getThing(index)) {
		return thing->getItem();
	}

	return nullptr;
}

std::shared_ptr<Item> Tile::getDoorItem() const {
	const TileItemVector* items = getItemList();
	if (!items || items->size() == 0) {
		return ground;
	}

	if (items) {
		for (auto &item : *items) {
			const ItemType &it = Item::items[item->getID()];
			if (it.isDoor()) {
				return item;
			}
		}
	}

	return nullptr;
}

phmap::flat_hash_set<std::shared_ptr<Zone>> Tile::getZones() {
	return zones;
}

void Tile::addZone(std::shared_ptr<Zone> zone) {
	zones.insert(zone);
	const auto &items = getItemList();
	if (items) {
		for (const auto &item : *items) {
			zone->itemAdded(item);
		}
	}
	const auto &creatures = getCreatures();
	if (creatures) {
		for (const auto &creature : *creatures) {
			zone->creatureAdded(creature);
		}
	}
}

void Tile::clearZones() {
	phmap::flat_hash_set<std::shared_ptr<Zone>> zonesToRemove;
	for (const auto &zone : zones) {
		if (zone->isStatic()) {
			continue;
		}
		zonesToRemove.insert(zone);
		const auto &items = getItemList();
		if (items) {
			for (const auto &item : *items) {
				zone->itemRemoved(item);
			}
		}
		const auto &creatures = getCreatures();
		if (creatures) {
			for (const auto &creature : *creatures) {
				zone->creatureRemoved(creature);
			}
		}
	}
	for (const auto &zone : zonesToRemove) {
		zones.erase(zone);
	}
}
