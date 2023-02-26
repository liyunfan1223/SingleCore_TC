#include "../pchdef.h"
#include "playerbot.h"
#include "PlayerbotFactory.h"
#include "../../server/game/Guilds/GuildMgr.h"
#include "../Entities/Item/ItemTemplate.h"
#include "PlayerbotAIConfig.h"
#include "../../shared/DataStores/DBCStore.h"
#include "../Miscellaneous/SharedDefines.h"
#include "../ahbot/AhBot.h"
#include "../Entities/Pet/Pet.h"
#include "RandomPlayerbotFactory.h"
#include "AiFactory.h"

using namespace ai;
using namespace std;

uint32 PlayerbotFactory::tradeSkills[] =
{
    SKILL_ALCHEMY,
    SKILL_ENCHANTING,
    SKILL_SKINNING,
    SKILL_JEWELCRAFTING,
    SKILL_INSCRIPTION,
    SKILL_TAILORING,
    SKILL_LEATHERWORKING,
    SKILL_ENGINEERING,
    SKILL_HERBALISM,
    SKILL_MINING,
    SKILL_BLACKSMITHING,
    SKILL_COOKING,
    SKILL_FIRST_AID,
    SKILL_FISHING
};

void PlayerbotFactory::Randomize()
{
    Randomize(true);
}

void PlayerbotFactory::Refresh()
{
    Prepare();
    InitEquipment(true);
    InitAmmo();
    InitFood();
    InitClassItems();
    InitPotions();
    bot->DurabilityRepairAll(false, 1.0f, false);
    uint32 money = urand(level * 1000, level * 5 * 1000);
    if (bot->GetMoney() < money)
        bot->SetMoney(money);
    bot->SaveToDB();
}

void PlayerbotFactory::CleanRandomize()
{
    Randomize(false);
}

void PlayerbotFactory::Prepare()
{
    if (!itemQuality)
    {
        if (level <= 10)
            // itemQuality = urand(ITEM_QUALITY_NORMAL, ITEM_QUALITY_UNCOMMON);
            itemQuality = urand(ITEM_QUALITY_UNCOMMON, ITEM_QUALITY_UNCOMMON);
        else if (level <= 20)
            // itemQuality = urand(ITEM_QUALITY_UNCOMMON, ITEM_QUALITY_RARE);
            itemQuality = urand(ITEM_QUALITY_RARE, ITEM_QUALITY_RARE);
        else if (level <= 40)
            // itemQuality = urand(ITEM_QUALITY_UNCOMMON, ITEM_QUALITY_EPIC);
            itemQuality = urand(ITEM_QUALITY_RARE, ITEM_QUALITY_RARE);
        else if (level < 60)
            // itemQuality = urand(ITEM_QUALITY_UNCOMMON, ITEM_QUALITY_EPIC);
            itemQuality = urand(ITEM_QUALITY_RARE, ITEM_QUALITY_RARE);
        else if (level < 80)
            // itemQuality = urand(ITEM_QUALITY_RARE, ITEM_QUALITY_EPIC);
            itemQuality = urand(ITEM_QUALITY_RARE, ITEM_QUALITY_RARE);
        else
            itemQuality = urand(ITEM_QUALITY_EPIC, ITEM_QUALITY_EPIC);
    }

    if (bot->isDead())
        bot->ResurrectPlayer(1.0f, false);

    bot->CombatStop(true);
    bot->SetLevel(level);
	
	//thesawolf - refill hp/sp since level resets can leave a vacuum
    bot->SetHealth(bot->GetMaxHealth());
    bot->SetPower(POWER_MANA, bot->GetMaxPower(POWER_MANA));    

	if (sPlayerbotAIConfig.randomBotShowHelmet)
    {
        bot->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_HIDE_HELM);
        bot->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_HIDE_CLOAK);
    }
}

void PlayerbotFactory::Randomize(bool incremental)
{
    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Preparing to randomize...");
    Prepare();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Resetting player...");
    bot->ResetTalents(true);
    ClearSpells();
    ClearInventory();
    bot->SaveToDB();

	if (sPlayerbotAIConfig.randomBotInitQuest)
	{
		sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing quests...");
		InitQuests();
	}
    bot->SetLevel(level); // quest rewards boost bot level, so reduce back
    bot->InitStatsForLevel();
    
    //thesawolf - refill hp/sp since level resets can leave a vacuum
    bot->SetHealth(bot->GetMaxHealth());
    bot->SetPower(POWER_MANA, bot->GetMaxPower(POWER_MANA));
	
    ClearInventory();
    bot->SetUInt32Value(PLAYER_XP, 0);
    CancelAuras();
    bot->SaveToDB();

    InitClassSpells();
    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing spells (step 1)...");
    InitAvailableSpells();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing skills (step 1)...");
    InitSkills();
    InitTradeSkills();
    InitSpecialSpells();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing talents...");
    InitTalents();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing spells (step 2)...");
    InitAvailableSpells();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing mounts...");
    InitMounts();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing skills (step 2)...");
    UpdateTradeSkills();
    bot->SaveToDB();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing equipmemt...");
    InitEquipment(incremental);

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing bags...");
    InitBags();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing ammo...");
    InitAmmo();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing food...");
    InitFood();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing poison...");
    InitClassItems();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing potions...");
    InitPotions();

    // sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing second equipment set...");
    // InitSecondEquipmentSet();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing inventory...");
    InitInventory();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing glyphs...");
    InitGlyphs();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing guilds...");
    bot->SaveToDB(); //thesawolf - save save save (hopefully avoids dupes)
    InitGuild(); //thesawolf - duplicate guild leaders causing segfault CHECK

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Initializing pet...");
    InitPet();

    sLog->outMessage("playerbot", LOG_LEVEL_INFO, "Saving to DB...");
    bot->SetMoney(urand(level * 1000, level * 5 * 1000));
    bot->SaveToDB();
}

void PlayerbotFactory::InitPet()
{
    Pet* pet = bot->GetPet();
    if (!pet)
    {
        if (bot->getClass() != CLASS_HUNTER)
            return;

        Map* map = bot->GetMap();
        if (!map)
            return;

		vector<uint32> ids;
	    CreatureTemplateContainer const* creatureTemplateContainer = sObjectMgr->GetCreatureTemplates();
	    for (CreatureTemplateContainer::const_iterator i = creatureTemplateContainer->begin(); i != creatureTemplateContainer->end(); ++i)
	    {
	        CreatureTemplate const& co = i->second;
            if (!co.IsTameable(false))
                continue;

            if (co.minlevel > bot->getLevel())
                continue;

			PetLevelInfo const* petInfo = sObjectMgr->GetPetLevelInfo(co.Entry, bot->getLevel());
            if (!petInfo)
                continue;

			ids.push_back(i->first);
		}

        if (ids.empty())
        {
            sLog->outMessage("playerbot", LOG_LEVEL_ERROR, "No pets available for bot %s (%d level)", bot->GetName().c_str(), bot->getLevel());
            return;
        }

		for (int i = 0; i < 100; i++)
		{
			int index = urand(0, ids.size() - 1);
			CreatureTemplate const* co = sObjectMgr->GetCreatureTemplate(ids[index]);

            PetLevelInfo const* petInfo = sObjectMgr->GetPetLevelInfo(co->Entry, bot->getLevel());
            if (!petInfo)
                continue;

            uint32 guid = map->GenerateLowGuid<HighGuid::Pet>();
            pet = new Pet(bot, HUNTER_PET);
            if (!pet->Create(guid, map, 0, ids[index], sObjectMgr->GeneratePetNumber()))
            {
                delete pet;
                pet = NULL;
                continue;
            }

            pet->SetPosition(bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ(), bot->GetOrientation());
            pet->setFaction(bot->getFaction());
            pet->SetLevel(bot->getLevel());
            bot->SetPetGUID(pet->GetGUID());
            bot->GetMap()->AddToMap(pet->ToCreature());
            bot->SetMinion(pet, true);
            pet->InitTalentForLevel();
            bot->PetSpellInitialize();
            bot->InitTamedPet(pet, bot->getLevel(), 0);

            sLog->outMessage("playerbot", LOG_LEVEL_DEBUG,  "Bot %s: assign pet %d (%d level)", bot->GetName().c_str(), co->Entry, bot->getLevel());
            pet->SavePetToDB(PET_SAVE_AS_CURRENT);
            break;
        }
    }

    if (!pet)
    {
        sLog->outMessage("playerbot", LOG_LEVEL_ERROR, "Cannot create pet for bot %s", bot->GetName().c_str());
        return;
    }

    for (PetSpellMap::const_iterator itr = pet->m_spells.begin(); itr != pet->m_spells.end(); ++itr)
    {
        if(itr->second.state == PETSPELL_REMOVED)
            continue;

        uint32 spellId = itr->first;
        const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (spellInfo->IsPassive())
            continue;

        pet->ToggleAutocast(spellInfo, true);
    }
}

void PlayerbotFactory::ClearSpells()
{
    list<uint32> spells;
    for(PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
    {
        uint32 spellId = itr->first;
        const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if(itr->second->state == PLAYERSPELL_REMOVED || itr->second->disabled || spellInfo->IsPassive())
            continue;

        spells.push_back(spellId);
    }

    for (list<uint32>::iterator i = spells.begin(); i != spells.end(); ++i)
    {
        bot->RemoveSpell(*i, false, false);
    }
}

void PlayerbotFactory::InitSpells()
{
    for (int i = 0; i < 15; i++)
        InitAvailableSpells();
}

void PlayerbotFactory::InitTalents()
{
    uint32 point = urand(0, 100);
    uint8 cls = bot->getClass();
    uint32 p1 = sPlayerbotAIConfig.specProbability[cls][0];
    uint32 p2 = p1 + sPlayerbotAIConfig.specProbability[cls][1];

    uint32 specNo = (point < p1 ? 0 : (point < p2 ? 1 : 2));
    InitTalents(specNo);

    if (bot->GetFreeTalentPoints())
        InitTalents(2 - specNo);
}


class DestroyItemsVisitor : public IterateItemsVisitor
{
public:
    DestroyItemsVisitor(Player* bot) : IterateItemsVisitor(), bot(bot) {}

    virtual bool Visit(Item* item)
    {
        uint32 id = item->GetTemplate()->ItemId;
        if (CanKeep(id))
        {
            keep.insert(id);
            return true;
        }

        bot->DestroyItem(item->GetBagSlot(), item->GetSlot(), true);
        return true;
    }

private:
    bool CanKeep(uint32 id)
    {
        if (keep.find(id) != keep.end())
            return false;

        if (sPlayerbotAIConfig.IsInRandomQuestItemList(id))
            return true;


        ItemTemplate const* proto = sObjectMgr->GetItemTemplate(id);
        if (proto->Class == ITEM_CLASS_MISC && (proto->SubClass == ITEM_SUBCLASS_JUNK_REAGENT || proto->SubClass == ITEM_SUBCLASS_JUNK))
            return true;

        return false;
    }

private:
    Player* bot;
    set<uint32> keep;

};

bool PlayerbotFactory::CanEquipArmor(ItemTemplate const* proto)
{
    if (bot->HasSkill(SKILL_SHIELD) && proto->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
        return true;

    // if (bot->HasSkill(SKILL_PLATE_MAIL))
    // {
    //     if (proto->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
    //         return false;
    // }
    // else if (bot->HasSkill(SKILL_MAIL))
    // {
    //     if (proto->SubClass != ITEM_SUBCLASS_ARMOR_MAIL)
    //         return false;
    // }
    // else if (bot->HasSkill(SKILL_LEATHER))
    // {
    //     if (proto->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER)
    //         return false;
    // }

    if (proto->Quality <= ITEM_QUALITY_NORMAL)
        return true;

    // uint8 sp = 0, ap = 0, tank = 0;
    // for (int j = 0; j < MAX_ITEM_PROTO_STATS; ++j)
    // {
    //     // for ItemStatValue != 0
    //     if(!proto->ItemStat[j].ItemStatValue)
    //         continue;

    //     AddItemStats(proto->ItemStat[j].ItemStatType, sp, ap, tank);
    // }
    return true;
    // return CheckItemStats(sp, ap, tank);
}

bool PlayerbotFactory::CheckItemStats(uint8 sp, uint8 ap, uint8 tank)
{
    switch (bot->getClass())
    {
    case CLASS_PRIEST:
    case CLASS_MAGE:
    case CLASS_WARLOCK:
        if (!sp || ap > sp || tank > sp)
            return false;
        break;
    case CLASS_PALADIN:
    case CLASS_WARRIOR:
	case CLASS_DEATH_KNIGHT:
        if ((!ap && !tank) || sp > ap || sp > tank)
            return false;
        break;
    case CLASS_HUNTER:
    case CLASS_ROGUE:
        if (!ap || sp > ap || sp > tank)
            return false;
        break;
    }

    return sp || ap || tank;
}

void PlayerbotFactory::AddItemStats(uint32 mod, uint8 &sp, uint8 &ap, uint8 &tank)
{
    switch (mod)
    {
    case ITEM_MOD_HIT_RATING:
    case ITEM_MOD_CRIT_RATING:
    case ITEM_MOD_HASTE_RATING:
    case ITEM_MOD_HEALTH:
    case ITEM_MOD_STAMINA:
    case ITEM_MOD_HEALTH_REGEN:
    case ITEM_MOD_MANA:
    case ITEM_MOD_INTELLECT:
    case ITEM_MOD_SPIRIT:
    case ITEM_MOD_MANA_REGENERATION:
    case ITEM_MOD_SPELL_POWER:
    case ITEM_MOD_SPELL_PENETRATION:
    case ITEM_MOD_HIT_SPELL_RATING:
    case ITEM_MOD_CRIT_SPELL_RATING:
    case ITEM_MOD_HASTE_SPELL_RATING:
        sp++;
        break;
    }

    switch (mod)
    {
    case ITEM_MOD_HIT_RATING:
    case ITEM_MOD_CRIT_RATING:
    case ITEM_MOD_HASTE_RATING:
    case ITEM_MOD_AGILITY:
    case ITEM_MOD_STRENGTH:
    case ITEM_MOD_HEALTH:
    case ITEM_MOD_STAMINA:
    case ITEM_MOD_HEALTH_REGEN:
    case ITEM_MOD_DEFENSE_SKILL_RATING:
    case ITEM_MOD_DODGE_RATING:
    case ITEM_MOD_PARRY_RATING:
    case ITEM_MOD_BLOCK_RATING:
    case ITEM_MOD_HIT_TAKEN_MELEE_RATING:
    case ITEM_MOD_HIT_TAKEN_RANGED_RATING:
    case ITEM_MOD_HIT_TAKEN_SPELL_RATING:
    case ITEM_MOD_CRIT_TAKEN_MELEE_RATING:
    case ITEM_MOD_CRIT_TAKEN_RANGED_RATING:
    case ITEM_MOD_CRIT_TAKEN_SPELL_RATING:
    case ITEM_MOD_HIT_TAKEN_RATING:
    case ITEM_MOD_CRIT_TAKEN_RATING:
    case ITEM_MOD_RESILIENCE_RATING:
    case ITEM_MOD_BLOCK_VALUE:
        tank++;
        break;
    }

    switch (mod)
    {
    case ITEM_MOD_HEALTH:
    case ITEM_MOD_STAMINA:
    case ITEM_MOD_HEALTH_REGEN:
    case ITEM_MOD_AGILITY:
    case ITEM_MOD_STRENGTH:
    case ITEM_MOD_HIT_MELEE_RATING:
    case ITEM_MOD_HIT_RANGED_RATING:
    case ITEM_MOD_CRIT_MELEE_RATING:
    case ITEM_MOD_CRIT_RANGED_RATING:
    case ITEM_MOD_HASTE_MELEE_RATING:
    case ITEM_MOD_HASTE_RANGED_RATING:
    case ITEM_MOD_HIT_RATING:
    case ITEM_MOD_CRIT_RATING:
    case ITEM_MOD_HASTE_RATING:
    case ITEM_MOD_EXPERTISE_RATING:
    case ITEM_MOD_ATTACK_POWER:
    case ITEM_MOD_RANGED_ATTACK_POWER:
    case ITEM_MOD_ARMOR_PENETRATION_RATING:
        ap++;
        break;
    }
}

bool PlayerbotFactory::CanEquipWeapon(ItemTemplate const* proto)
{
    switch (bot->getClass())
    {
    case CLASS_PRIEST:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_WAND &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE)
            return false;
        break;
    case CLASS_MAGE:
    case CLASS_WARLOCK:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_WAND &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD)
            return false;
        break;
    case CLASS_WARRIOR:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
			proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE &&
			proto->SubClass != ITEM_SUBCLASS_WEAPON_POLEARM &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_GUN &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_CROSSBOW &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_BOW &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_THROWN)
            return false;
        break;
    case CLASS_PALADIN:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD)
            return false;
        break;
	case CLASS_DEATH_KNIGHT:
		if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
			proto->SubClass != ITEM_SUBCLASS_WEAPON_POLEARM &&
			proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
			proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
			proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE &&
            proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
            proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD)
			return false;
		break;
    case CLASS_SHAMAN:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_FIST &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_FIST &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF)
            return false;
        break;
    case CLASS_DRUID:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF)
            return false;
        break;
    case CLASS_HUNTER:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_POLEARM &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_FIST &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_GUN &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_CROSSBOW &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_BOW)
            return false;
        break;
    case CLASS_ROGUE:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD &&
				proto->SubClass != ITEM_SUBCLASS_WEAPON_FIST &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_GUN &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_CROSSBOW &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_BOW &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_THROWN)
            return false;
        break;
    }

    return true;
}

bool PlayerbotFactory::CanEquipItem(ItemTemplate const* proto, uint32 desiredQuality)
{
    if (proto->Duration & 0x80000000)
        return false;

    if (proto->Quality != desiredQuality)
        return false;

    if (proto->Bonding == BIND_QUEST_ITEM || proto->Bonding == BIND_WHEN_USE)
        return false;

    if (proto->Class == ITEM_CLASS_CONTAINER)
        return true;

    uint32 requiredLevel = proto->RequiredLevel;
    if (!requiredLevel)
        return false;

    uint32 level = bot->getLevel();
    uint32 delta = 2;
    if (level < 15)
        delta = 15; // urand(7, 15);
    // else if (proto->Class == ITEM_CLASS_WEAPON || proto->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
    //     delta = urand(2, 3);
    // else if (!(level % 10) || (level % 10) == 9)
    //     delta = 2;
    else if (level < 40)
        delta = 10; //urand(5, 10);
    else if (level < 60)
        delta = 8; // urand(3, 7);
    else if (level < 70)
        delta = 6; // urand(2, 5);
    else if (level < 80)
        delta = 6; // urand(2, 4);

    if (desiredQuality > ITEM_QUALITY_NORMAL &&
            (requiredLevel > level || requiredLevel < level - delta))
        return false;

    // for (uint32 gap = 60; gap <= 80; gap += 10)
    // {
    //     if (level > gap && requiredLevel <= gap)
    //         return false;
    // }

    return true;
}

void PlayerbotFactory::InitEquipment(bool incremental)
{
    //thesawolf - lets stick the gearlock check here
    QueryResult gresults = CharacterDatabase.PQuery("SELECT * FROM ai_playerbot_locks WHERE name_id = '%u'",  bot->GetGUID());
    if (gresults)
        return;

    DestroyItemsVisitor visitor(bot);
    IterateItems(&visitor, ITERATE_ALL_ITEMS);

    map<uint8, vector<uint32> > items;
    int tab = AiFactory::GetPlayerSpecTab(bot);
    for(uint8 slot = 0; slot < EQUIPMENT_SLOT_END; ++slot)
    {
        if (slot == EQUIPMENT_SLOT_TABARD || slot == EQUIPMENT_SLOT_BODY)
            continue;

        uint32 desiredQuality = itemQuality;
        // if (urand(0, 100) < 100 * sPlayerbotAIConfig.randomGearLoweringChance && desiredQuality > ITEM_QUALITY_NORMAL) {
        //     desiredQuality--;
        // }

        do
        {
            ItemTemplateContainer const* itemTemplates = sObjectMgr->GetItemTemplateStore();
            for (ItemTemplateContainer::const_iterator i = itemTemplates->begin(); i != itemTemplates->end(); ++i)
            {
                uint32 itemId = i->first;
                ItemTemplate const* proto = &i->second;
                if (!proto)
                    continue;

                if (proto->Class != ITEM_CLASS_WEAPON &&
                    proto->Class != ITEM_CLASS_ARMOR &&
                    proto->Class != ITEM_CLASS_CONTAINER &&
                    proto->Class != ITEM_CLASS_PROJECTILE)
                    continue;

                if (!CanEquipItem(proto, desiredQuality))
                    continue;

                if (proto->Class == ITEM_CLASS_ARMOR && (
                    slot == EQUIPMENT_SLOT_HEAD ||
                    slot == EQUIPMENT_SLOT_SHOULDERS ||
                    slot == EQUIPMENT_SLOT_CHEST ||
                    slot == EQUIPMENT_SLOT_WAIST ||
                    slot == EQUIPMENT_SLOT_LEGS ||
                    slot == EQUIPMENT_SLOT_FEET ||
                    slot == EQUIPMENT_SLOT_WRISTS ||
                    slot == EQUIPMENT_SLOT_HANDS) && !CanEquipArmor(proto))
                        continue;

                if (proto->Class == ITEM_CLASS_WEAPON && !CanEquipWeapon(proto))
                    continue;

                if (slot == EQUIPMENT_SLOT_OFFHAND && bot->getClass() == CLASS_ROGUE && proto->Class != ITEM_CLASS_WEAPON)
                    continue;

                // if (IsShieldTank()) {
                //     if (slot == EQUIPMENT_SLOT_MAINHAND && 
                //     (proto->Class != ITEM_CLASS_WEAPON || !(ITEM_SUBCLASS_SINGLE_HAND & (1 << proto->SubClass)))) {
                //         continue;
                //     }
                //     if (slot == EQUIPMENT_SLOT_OFFHAND && 
                //     (proto->Class != ITEM_CLASS_ARMOR || proto->SubClass != ITEM_SUBCLASS_ARMOR_SHIELD)) {
                //         continue;
                //     }
                // }
                uint16 dest = 0;
                if (CanEquipUnseenItem(slot, dest, itemId))
                    items[slot].push_back(itemId);
            }
        } while (items[slot].size() < 25 && desiredQuality-- > ITEM_QUALITY_NORMAL);
    }

    for(uint8 slot = 0; slot < EQUIPMENT_SLOT_END; ++slot)
    {
        if (slot == EQUIPMENT_SLOT_TABARD || slot == EQUIPMENT_SLOT_BODY)
            continue;

        vector<uint32>& ids = items[slot];
        if (ids.empty())
        {
            sLog->outMessage("playerbot", LOG_LEVEL_DEBUG,  "%s: no items to equip for slot %d", bot->GetName().c_str(), slot);
            continue;
        }
        Item* oldItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);

        if (incremental && !IsDesiredReplacement(oldItem)) {
            sLog->outMessage("playerbot", LOG_LEVEL_DEBUG,  "%s: doesn't desire to replace current slot %d", bot->GetName().c_str(), slot);
            continue;
        }

        float bestScoreForSlot = -1;
        uint32 bestItemForSlot = 0;
        for (int attempts = 0; attempts < min((int)ids.size(), 25); attempts++)
        {
            uint32 index = urand(0, ids.size() - 1);
            uint32 newItemId = ids[index];
            
            uint16 dest;
            if (!CanEquipUnseenItem(slot, dest, newItemId))
                continue;
            
            float cur_score = CalculateItemScore(newItemId);
            if (cur_score > bestScoreForSlot) {
                bestScoreForSlot = cur_score;
                bestItemForSlot = newItemId;
            }
        }
        if (bestItemForSlot == 0) {
            // sLog->outMessage("playerbot", LOG_LEVEL_INFO,  "%s: equip failed for slot %d(bestItemForSlot == 0))", bot->GetName().c_str(), slot);
            continue;
        }
        if (oldItem)
        {
            bot->RemoveItem(INVENTORY_SLOT_BAG_0, slot, true);
            oldItem->DestroyForPlayer(bot, false);
        }
        uint16 dest;
        if (!CanEquipUnseenItem(slot, dest, bestItemForSlot)) {
            sLog->outMessage("playerbot", LOG_LEVEL_DEBUG,  "%s: equip failed for slot %d", bot->GetName().c_str(), slot);
            continue;
        }
        Item* newItem = bot->EquipNewItem(dest, bestItemForSlot, true);
        if (newItem)
        {
            newItem->AddToWorld();
            newItem->AddToUpdateQueueOf(bot);
            bot->AutoUnequipOffhandIfNeed();
            EnchantItem(newItem);
        }
    }
}

bool PlayerbotFactory::IsDesiredReplacement(Item* item)
{
    if (!item)
        return true;

    ItemTemplate const* proto = item->GetTemplate();
    int delta = 1 + (80 - bot->getLevel()) / 10;
    return (int)bot->getLevel() - (int)proto->RequiredLevel > delta;
}

void PlayerbotFactory::InitSecondEquipmentSet()
{
    if (bot->getClass() == CLASS_MAGE || bot->getClass() == CLASS_WARLOCK || bot->getClass() == CLASS_PRIEST)
        return;

    map<uint32, vector<uint32> > items;

    uint32 desiredQuality = itemQuality;
    while (urand(0, 100) < 100 * sPlayerbotAIConfig.randomGearLoweringChance && desiredQuality > ITEM_QUALITY_NORMAL) {
        desiredQuality--;
    }

    do
    {
        ItemTemplateContainer const* itemTemplates = sObjectMgr->GetItemTemplateStore();
        for (ItemTemplateContainer::const_iterator i = itemTemplates->begin(); i != itemTemplates->end(); ++i)
        {
            uint32 itemId = i->first;
            ItemTemplate const* proto = &i->second;
            if (!proto)
                continue;

            if (!CanEquipItem(proto, desiredQuality))
                continue;

            if (proto->Class == ITEM_CLASS_WEAPON)
            {
                if (!CanEquipWeapon(proto))
                    continue;

                Item* existingItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                if (existingItem)
                {
                    switch (existingItem->GetTemplate()->SubClass)
                    {
                    case ITEM_SUBCLASS_WEAPON_AXE:
                    case ITEM_SUBCLASS_WEAPON_DAGGER:
                    case ITEM_SUBCLASS_WEAPON_FIST:
                    case ITEM_SUBCLASS_WEAPON_MACE:
                    case ITEM_SUBCLASS_WEAPON_SWORD:
                        if (proto->SubClass == ITEM_SUBCLASS_WEAPON_AXE || proto->SubClass == ITEM_SUBCLASS_WEAPON_DAGGER ||
                            proto->SubClass == ITEM_SUBCLASS_WEAPON_FIST || proto->SubClass == ITEM_SUBCLASS_WEAPON_MACE ||
                            proto->SubClass == ITEM_SUBCLASS_WEAPON_SWORD)
                            continue;
                        break;
                    default:
                        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE && proto->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER &&
                            proto->SubClass != ITEM_SUBCLASS_WEAPON_FIST && proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                            proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD)
                            continue;
                        break;
                    }
                }
            }
            else if (proto->Class == ITEM_CLASS_ARMOR && proto->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
            {
                if (!CanEquipArmor(proto))
                    continue;

                Item* existingItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                if (existingItem && existingItem->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
                    continue;
            }
            else
                continue;

            items[proto->Class].push_back(itemId);
        }
    } while (items[ITEM_CLASS_ARMOR].empty() && items[ITEM_CLASS_WEAPON].empty() && desiredQuality-- > ITEM_QUALITY_NORMAL);

    for (map<uint32, vector<uint32> >::iterator i = items.begin(); i != items.end(); ++i)
    {
        vector<uint32>& ids = i->second;
        if (ids.empty())
        {
            sLog->outMessage("playerbot", LOG_LEVEL_DEBUG,  "%s: no items to make second equipment set for slot %d", bot->GetName().c_str(), i->first);
            continue;
        }

        for (int attempts = 0; attempts < 15; attempts++)
        {
            uint32 index = urand(0, ids.size() - 1);
            uint32 newItemId = ids[index];

            ItemPosCountVec sDest;
            Item* newItem = StoreItem(newItemId, 1);
            if (newItem)
            {
                EnchantItem(newItem);
                newItem->AddToWorld();
                newItem->AddToUpdateQueueOf(bot);
                break;
            }
        }
    }
}

void PlayerbotFactory::InitBags()
{
    // vector<uint32> ids;

    // ItemTemplateContainer const* itemTemplates = sObjectMgr->GetItemTemplateStore();
    // for (ItemTemplateContainer::const_iterator i = itemTemplates->begin(); i != itemTemplates->end(); ++i)
    // {
    //     uint32 itemId = i->first;
    //     ItemTemplate const* proto = &i->second;
    //     if (!proto || proto->Class != ITEM_CLASS_CONTAINER)
    //         continue;

    //     if (!CanEquipItem(proto, ITEM_QUALITY_NORMAL))
    //         continue;

    //     ids.push_back(itemId);
    // }

    // if (ids.empty())
    // {
    //     sLog->outMessage("playerbot", LOG_LEVEL_ERROR, "%s: no bags found", bot->GetName().c_str());
    //     return;
    // }

    for (uint8 slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; ++slot)
    {
        uint32 newItemId = 23162;

        uint16 dest;
        if (!CanEquipUnseenItem(slot, dest, newItemId))
            continue;

        Item* newItem = bot->EquipNewItem(dest, newItemId, true);
        if (newItem)
        {
            newItem->AddToWorld();
            newItem->AddToUpdateQueueOf(bot);
        }
    }
}

void PlayerbotFactory::EnchantItem(Item* item)
{
    if (urand(0, 100) < 100 * sPlayerbotAIConfig.randomGearLoweringChance)
        return;

    if (bot->getLevel() < urand(40, 50))
        return;

    ItemTemplate const* proto = item->GetTemplate();
    int32 itemLevel = proto->ItemLevel;

    vector<uint32> ids;
    for (int id = 0; id < sSpellStore.GetNumRows(); ++id)
    {
        SpellInfo const *entry = sSpellMgr->GetSpellInfo(id);
        if (!entry)
            continue;

        int32 requiredLevel = (int32)entry->BaseLevel;
        if (requiredLevel && (requiredLevel > itemLevel || requiredLevel < itemLevel - 35))
            continue;

        if (entry->MaxLevel && level > entry->MaxLevel)
            continue;

        uint32 spellLevel = entry->SpellLevel;
        if (spellLevel && (spellLevel > level || spellLevel < level - 10))
            continue;

        for (int j = 0; j < 3; ++j)
        {
            if (entry->Effects[j].Effect != SPELL_EFFECT_ENCHANT_ITEM)
                continue;

            uint32 enchant_id = entry->Effects[j].MiscValue;
            if (!enchant_id)
                continue;

            SpellItemEnchantmentEntry const* enchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
            if (!enchant || enchant->slot != PERM_ENCHANTMENT_SLOT)
                continue;

            if (enchant->requiredLevel && enchant->requiredLevel > level)
                continue;

            uint8 sp = 0, ap = 0, tank = 0;
            for (int i = 0; i < 3; ++i)
            {
                if (enchant->type[i] != ITEM_ENCHANTMENT_TYPE_STAT)
                    continue;

                AddItemStats(enchant->spellid[i], sp, ap, tank);
            }

            if (!CheckItemStats(sp, ap, tank))
                continue;

            if (enchant->EnchantmentCondition && !bot->EnchantmentFitsRequirements(enchant->EnchantmentCondition, -1))
                continue;

            if (!item->IsFitToSpellRequirements(entry))
                continue;

            ids.push_back(enchant_id);
        }
    }

    if (ids.empty())
    {
        sLog->outMessage("playerbot", LOG_LEVEL_DEBUG,  "%s: no enchantments found for item %d", bot->GetName().c_str(), item->GetTemplate()->ItemId);
        return;
    }

    int index = urand(0, ids.size() - 1);
    uint32 id = ids[index];

    SpellItemEnchantmentEntry const* enchant = sSpellItemEnchantmentStore.LookupEntry(id);
    if (!enchant)
        return;

    bot->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, false);
    item->SetEnchantment(PERM_ENCHANTMENT_SLOT, id, 0, 0);
    bot->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, true);
}

bool PlayerbotFactory::CanEquipUnseenItem(uint8 slot, uint16 &dest, uint32 item)
{
    dest = 0;
    Item *pItem = Item::CreateItem(item, 1, bot);
    if (pItem)
    {
        InventoryResult result = bot->CanEquipItem(slot, dest, pItem, true, false);
        pItem->RemoveFromUpdateQueueOf(bot);
        delete pItem;
        return result == EQUIP_ERR_OK;
    }

    return false;
}

void PlayerbotFactory::InitTradeSkills()
{
    for (int i = 0; i < sizeof(tradeSkills) / sizeof(uint32); ++i)
    {
        bot->SetSkill(tradeSkills[i], 0, 0, 0);
    }

    vector<uint32> firstSkills;
    vector<uint32> secondSkills;
    switch (bot->getClass())
    {
    case CLASS_WARRIOR:
	case CLASS_DEATH_KNIGHT:
    case CLASS_PALADIN:
        firstSkills.push_back(SKILL_MINING);
        secondSkills.push_back(SKILL_BLACKSMITHING);
        secondSkills.push_back(SKILL_ENGINEERING);
        break;
    case CLASS_SHAMAN:
    case CLASS_DRUID:
    case CLASS_HUNTER:
    case CLASS_ROGUE:
        firstSkills.push_back(SKILL_SKINNING);
        secondSkills.push_back(SKILL_LEATHERWORKING);
        break;
    default:
        firstSkills.push_back(SKILL_TAILORING);
        secondSkills.push_back(SKILL_ENCHANTING);
    }

    SetRandomSkill(SKILL_FIRST_AID);
    SetRandomSkill(SKILL_FISHING);
    SetRandomSkill(SKILL_COOKING);

    switch (urand(0, 3))
    {
    case 0:
        SetRandomSkill(SKILL_HERBALISM);
        SetRandomSkill(SKILL_ALCHEMY);
        break;
    case 1:
        SetRandomSkill(SKILL_HERBALISM);
        SetRandomSkill(SKILL_INSCRIPTION);
        break;
    case 2:
        SetRandomSkill(SKILL_MINING);
        SetRandomSkill(SKILL_JEWELCRAFTING);
        break;
    case 3:
        SetRandomSkill(firstSkills[urand(0, firstSkills.size() - 1)]);
        SetRandomSkill(secondSkills[urand(0, secondSkills.size() - 1)]);
        break;
    }
}

void PlayerbotFactory::UpdateTradeSkills()
{
    for (int i = 0; i < sizeof(tradeSkills) / sizeof(uint32); ++i)
    {
        if (bot->GetSkillValue(tradeSkills[i]) == 1)
            bot->SetSkill(tradeSkills[i], 0, 0, 0);
    }
}

void PlayerbotFactory::InitSkills()
{
    uint32 maxValue = level * 5;
    SetRandomSkill(SKILL_DEFENSE);
    SetRandomSkill(SKILL_SWORDS);
    SetRandomSkill(SKILL_AXES);
    SetRandomSkill(SKILL_BOWS);
    SetRandomSkill(SKILL_GUNS);
    SetRandomSkill(SKILL_MACES);
    SetRandomSkill(SKILL_2H_SWORDS);
    SetRandomSkill(SKILL_STAVES);
    SetRandomSkill(SKILL_2H_MACES);
    SetRandomSkill(SKILL_2H_AXES);
    SetRandomSkill(SKILL_DAGGERS);
    SetRandomSkill(SKILL_THROWN);
    SetRandomSkill(SKILL_CROSSBOWS);
    SetRandomSkill(SKILL_WANDS);
    SetRandomSkill(SKILL_POLEARMS);
    SetRandomSkill(SKILL_FIST_WEAPONS);

    if (bot->getLevel() >= 70)
        bot->SetSkill(SKILL_RIDING, 0, 300, 300);
    else if (bot->getLevel() >= 60)
        bot->SetSkill(SKILL_RIDING, 0, 225, 225);
    else if (bot->getLevel() >= 40)
        bot->SetSkill(SKILL_RIDING, 0, 150, 150);
    else if (bot->getLevel() >= 20)
        bot->SetSkill(SKILL_RIDING, 0, 75, 75);
    else
        bot->SetSkill(SKILL_RIDING, 0, 0, 0);

    uint32 skillLevel = bot->getLevel() < 40 ? 0 : 1;
    switch (bot->getClass())
    {
    case CLASS_DEATH_KNIGHT:
    case CLASS_WARRIOR:
    case CLASS_PALADIN:
        bot->SetSkill(SKILL_PLATE_MAIL, 0, skillLevel, skillLevel);
        break;
    case CLASS_SHAMAN:
    case CLASS_HUNTER:
        bot->SetSkill(SKILL_MAIL, 0, skillLevel, skillLevel);
    }
}

void PlayerbotFactory::SetRandomSkill(uint16 id)
{
    uint32 maxValue = level * 5;
    uint32 curValue = urand(maxValue - level, maxValue);
    bot->SetSkill(id, 0, curValue, maxValue);

}

void PlayerbotFactory::InitAvailableSpells()
{
    bot->LearnDefaultSkills();

    CreatureTemplateContainer const* creatureTemplateContainer = sObjectMgr->GetCreatureTemplates();
    for (CreatureTemplateContainer::const_iterator i = creatureTemplateContainer->begin(); i != creatureTemplateContainer->end(); ++i)
    {
        CreatureTemplate const& co = i->second;
        if (co.trainer_type != TRAINER_TYPE_TRADESKILLS && co.trainer_type != TRAINER_TYPE_CLASS)
            continue;

        if (co.trainer_type == TRAINER_TYPE_CLASS && co.trainer_class != bot->getClass())
            continue;

		uint32 trainerId = co.Entry;

		TrainerSpellData const* trainer_spells = sObjectMgr->GetNpcTrainerSpells(trainerId);
        if (!trainer_spells)
            trainer_spells = sObjectMgr->GetNpcTrainerSpells(trainerId);

        if (!trainer_spells)
            continue;

        for (TrainerSpellMap::const_iterator itr =  trainer_spells->spellList.begin(); itr !=  trainer_spells->spellList.end(); ++itr)
        {
            TrainerSpell const* tSpell = &itr->second;

            if (!tSpell)
                continue;

            if (!tSpell->learnedSpell[0] && !bot->IsSpellFitByClassAndRace(tSpell->learnedSpell[0]))
                continue;

            TrainerSpellState state = bot->GetTrainerSpellState(tSpell);
            if (state != TRAINER_SPELL_GREEN)
                continue;

            if (tSpell->learnedSpell)
                bot->LearnSpell(tSpell->learnedSpell[0], false);
            else
                ai->CastSpell(tSpell->spell, bot);
        }
    }
}

void PlayerbotFactory::InitClassSpells()
{
    int32_t level = bot->getLevel();
    switch (bot->getClass())
    {
        case CLASS_WARRIOR:
            bot->LearnSpell(78, false);
            bot->LearnSpell(2457, false);
            if (level >= 10) {
                bot->LearnSpell(71, false); // Defensive Stance
                bot->LearnSpell(355, false); // Taunt
                bot->LearnSpell(7386, false); // Sunder Armor
            }
            if (level >= 30) {
                bot->LearnSpell(2458, false); // Berserker Stance
            }
            break;
        case CLASS_PALADIN:
            bot->LearnSpell(21084, false);
            bot->LearnSpell(635, false);
            if (level >= 12) {
                bot->LearnSpell(7328, false); // Redemption
            }
            break;
        case CLASS_ROGUE:
            bot->LearnSpell(1752, false);
            bot->LearnSpell(2098, false);
            break;
        case CLASS_DEATH_KNIGHT:
            bot->LearnSpell(45477, false);
            bot->LearnSpell(47541, false);
            bot->LearnSpell(45462, false);
            bot->LearnSpell(45902, false);
            break;
        case CLASS_HUNTER:
            bot->LearnSpell(2973, false);
            bot->LearnSpell(75, false);
            if (level >= 10) {
                bot->LearnSpell(883, false); // call pet
                bot->LearnSpell(1515, false); // tame pet
                bot->LearnSpell(6991, false); // feed pet
                bot->LearnSpell(982, false); // revive pet
            }
            break;
        case CLASS_PRIEST:
            bot->LearnSpell(585, false);
            bot->LearnSpell(2050, false);
            break;
        case CLASS_MAGE:
            bot->LearnSpell(133, false);
            bot->LearnSpell(168, false);
            break;
        case CLASS_WARLOCK:
            bot->LearnSpell(687, false);
            bot->LearnSpell(686, false);
            if (level >= 10) {
                bot->LearnSpell(697, false); // summon voidwalker
            }
            if (level >= 20) {
                bot->LearnSpell(712, false); // summon succubus
            }
            if (level >= 30) {
                bot->LearnSpell(691, false); // summon felhunter
            }
            break;
        case CLASS_DRUID:
            bot->LearnSpell(5176, false);
            bot->LearnSpell(5185, false);
            if (level >= 10) {
                bot->LearnSpell(5487, false); // bear form
                bot->LearnSpell(6795, false); // Growl
                bot->LearnSpell(6807, false); // Maul
            }
            break;
        case CLASS_SHAMAN:
            bot->LearnSpell(403, false);
            bot->LearnSpell(331, false);
            break;
        default:
            break;
    }
}

void PlayerbotFactory::InitSpecialSpells()
{
    for (list<uint32>::iterator i = sPlayerbotAIConfig.randomBotSpellIds.begin(); i != sPlayerbotAIConfig.randomBotSpellIds.end(); ++i)
    {
        uint32 spellId = *i;
        bot->LearnSpell(spellId, false);
    }
	//to leave DK starting area 
	if (bot->getClass() == CLASS_DEATH_KNIGHT)
	{
		bot->LearnSpell(50977, false);
	}

	//Mounts
	if (bot->getLevel() > 20 && bot->GetTeamId()==TeamId::TEAM_ALLIANCE)
	{
		bot->LearnSpell(6899, false);
	}
	if (bot->getLevel() > 20 && bot->GetTeamId() == TeamId::TEAM_HORDE)
	{
		bot->LearnSpell(8395, false);

	}
	if (bot->getLevel() > 40 && bot->GetTeamId() == TeamId::TEAM_ALLIANCE)
	{
		bot->LearnSpell(23240, false);

	}
	if (bot->getLevel() > 40 && bot->GetTeamId() == TeamId::TEAM_HORDE)
	{
		bot->LearnSpell(23242, false);
	}
}

void PlayerbotFactory::InitTalents(uint32 specNo)
{
    uint32 classMask = bot->getClassMask();

    map<uint32, vector<TalentEntry const*> > spells;
    for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
    {
        TalentEntry const *talentInfo = sTalentStore.LookupEntry(i);
        if(!talentInfo)
            continue;

        TalentTabEntry const *talentTabInfo = sTalentTabStore.LookupEntry( talentInfo->TalentTab );
        if(!talentTabInfo || talentTabInfo->tabpage != specNo)
            continue;

        if( (classMask & talentTabInfo->ClassMask) == 0 )
            continue;

        spells[talentInfo->Row].push_back(talentInfo);
    }

    uint32 freePoints = bot->GetFreeTalentPoints();
    for (map<uint32, vector<TalentEntry const*> >::iterator i = spells.begin(); i != spells.end(); ++i)
    {
        vector<TalentEntry const*> &spells = i->second;
        if (spells.empty())
        {
            sLog->outMessage("playerbot", LOG_LEVEL_ERROR, "%s: No spells for talent row %d", bot->GetName().c_str(), i->first);
            continue;
        }

        int attemptCount = 0;
        while (!spells.empty() && (int)freePoints - (int)bot->GetFreeTalentPoints() < 5 && attemptCount++ < 3 && bot->GetFreeTalentPoints())
        {
            int index = urand(0, spells.size() - 1);
            TalentEntry const *talentInfo = spells[index];
            int maxRank = 0;
            for (int rank = 0; rank < min((uint32)MAX_TALENT_RANK, bot->GetFreeTalentPoints()); ++rank)
            {
                uint32 spellId = talentInfo->RankID[rank];
                if (!spellId)
                    continue;

                maxRank = rank;
            }

            bot->LearnTalent(talentInfo->TalentID, maxRank);
			spells.erase(spells.begin() + index);
        }

        freePoints = bot->GetFreeTalentPoints();
    }

    for (uint32 i = 0; i < MAX_TALENT_SPECS; ++i)
    {
        for (PlayerTalentMap::iterator itr = bot->GetTalentMap(i).begin(); itr != bot->GetTalentMap(i).end(); ++itr)
        {
            if (itr->second->state != PLAYERSPELL_REMOVED)
                itr->second->state = PLAYERSPELL_CHANGED;
        }
    }
}

ObjectGuid PlayerbotFactory::GetRandomBot()
{
    vector<ObjectGuid> guids;
    for (list<uint32>::iterator i = sPlayerbotAIConfig.randomBotAccounts.begin(); i != sPlayerbotAIConfig.randomBotAccounts.end(); i++)
    {
        uint32 accountId = *i;
        if (!sAccountMgr->GetCharactersCount(accountId))
            continue;

        QueryResult result = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE account = '%u'", accountId);
        if (!result)
            continue;

        do
        {
            Field* fields = result->Fetch();
            ObjectGuid guid = ObjectGuid(HighGuid::Player, fields[0].GetUInt32());
            if (!sObjectMgr->GetPlayerByLowGUID(guid))
                guids.push_back(guid);
        } while (result->NextRow());
    }

    if (guids.empty())
        return ObjectGuid();

    int index = urand(0, guids.size() - 1);
    return guids[index];
}

void AddPrevQuests(uint32 questId, list<uint32>& questIds)
{
    Quest const *quest = sObjectMgr->GetQuestTemplate(questId);
    for (Quest::PrevQuests::const_iterator iter = quest->prevQuests.begin(); iter != quest->prevQuests.end(); ++iter)
    {
        uint32 prevId = abs(*iter);
        AddPrevQuests(prevId, questIds);
		questIds.remove(prevId);
        questIds.push_back(prevId);
    }
}

void PlayerbotFactory::InitQuests()
{
    ObjectMgr::QuestMap const& questTemplates = sObjectMgr->GetQuestTemplates();
    list<uint32> questIds;
    for (ObjectMgr::QuestMap::const_iterator i = questTemplates.begin(); i != questTemplates.end(); ++i)
    {
        uint32 questId = i->first;
        Quest const *quest = i->second;

        if (!quest->GetRequiredClasses() ||
                quest->GetMinLevel() > bot->getLevel() ||
                quest->IsDailyOrWeekly() || quest->IsRepeatable() || quest->IsMonthly())
            continue;

        AddPrevQuests(questId, questIds);
		questIds.remove(questId);
        questIds.push_back(questId);
    }

    for (list<uint32>::iterator i = questIds.begin(); i != questIds.end(); ++i)
    {
        uint32 questId = *i;
        Quest const *quest = sObjectMgr->GetQuestTemplate(questId);

        if (!bot->SatisfyQuestClass(quest, false) ||
                !bot->SatisfyQuestRace(quest, false))
            continue;

        bot->RemoveActiveQuest(questId, false);
        bot->RemoveRewardedQuest(questId, false);

        bot->SetQuestStatus(questId, QUEST_STATUS_COMPLETE);
        bot->RewardQuest(quest, 0, bot, false);
        ClearInventory();
    }
}

void PlayerbotFactory::ClearInventory()
{
    DestroyItemsVisitor visitor(bot);
    IterateItems(&visitor);
}

void PlayerbotFactory::InitAmmo()
{
    if (bot->getClass() != CLASS_HUNTER && bot->getClass() != CLASS_ROGUE && bot->getClass() != CLASS_WARRIOR)
        return;

    Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
    if (!pItem)
        return;

    uint32 subClass = 0;
    switch (pItem->GetTemplate()->SubClass)
    {
    case ITEM_SUBCLASS_WEAPON_GUN:
        subClass = ITEM_SUBCLASS_BULLET;
        break;
    case ITEM_SUBCLASS_WEAPON_BOW:
    case ITEM_SUBCLASS_WEAPON_CROSSBOW:
        subClass = ITEM_SUBCLASS_ARROW;
        break;
    }

    if (!subClass)
        return;

    QueryResult results = WorldDatabase.PQuery("select max(entry), max(RequiredLevel) from item_template where class = '%u' and subclass = '%u' and RequiredLevel <= '%u'",
            ITEM_CLASS_PROJECTILE, subClass, bot->getLevel());

    Field* fields = results->Fetch();
    if (fields)
    {
        uint32 entry = fields[0].GetUInt32();
        for (int i = 0; i < 15; i++)
        {
            bot->StoreNewItemInBestSlots(entry, 1000);
        }
        bot->SetAmmo(entry);
    }
}

void PlayerbotFactory::InitMounts()
{
    map<uint32, map<int32, vector<uint32> > > allSpells;

    for (uint32 spellId = 0; spellId < sSpellStore.GetNumRows(); ++spellId)
    {
        SpellInfo const *spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (!spellInfo || spellInfo->Effects[0].ApplyAuraName != SPELL_AURA_MOUNTED)
            continue;

        if (spellInfo->GetDuration() != -1)
            continue;

        int32 effect = max(spellInfo->Effects[1].BasePoints, spellInfo->Effects[2].BasePoints);
        if (effect < 50)
            continue;

        uint32 index = (spellInfo->Effects[1].ApplyAuraName == SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS ||
                spellInfo->Effects[2].ApplyAuraName == SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS) ? 1 : 0;
        allSpells[index][effect].push_back(spellId);
    }

    for (uint32 type = 0; type < 2; ++type)
    {
        map<int32, vector<uint32> >& spells = allSpells[type];
        for (map<int32, vector<uint32> >::iterator i = spells.begin(); i != spells.end(); ++i)
        {
            int32 effect = i->first;
            vector<uint32>& ids = i->second;
            uint32 index = urand(0, ids.size() - 1);
            if (index >= ids.size())
                continue;

            bot->LearnSpell(ids[index], false);
        }
    }
}

void PlayerbotFactory::InitPotions()
{
    map<uint32, vector<uint32> > items;
    ItemTemplateContainer const* itemTemplateContainer = sObjectMgr->GetItemTemplateStore();
    for (ItemTemplateContainer::const_iterator i = itemTemplateContainer->begin(); i != itemTemplateContainer->end(); ++i)
    {
        ItemTemplate const& itemTemplate = i->second;
        uint32 itemId = i->first;
        ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
        if (!proto)
            continue;

        if (proto->Class != ITEM_CLASS_CONSUMABLE ||
            proto->SubClass != ITEM_SUBCLASS_POTION ||
            proto->Spells[0].SpellCategory != 4 ||
            proto->Bonding != NO_BIND)
            continue;

        if (proto->RequiredLevel > bot->getLevel() || proto->RequiredLevel < bot->getLevel() - 10)
            continue;

        if (proto->RequiredSkill && !bot->HasSkill(proto->RequiredSkill))
            continue;

        if (proto->Area || proto->Map || proto->RequiredCityRank || proto->RequiredHonorRank)
            continue;

        for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
        {
            const SpellInfo* const spellInfo = sSpellMgr->GetSpellInfo(proto->Spells[j].SpellId);
            if (!spellInfo)
                continue;

            for (int i = 0 ; i < 3; i++)
            {
                if (spellInfo->Effects[i].Effect == SPELL_EFFECT_HEAL || spellInfo->Effects[i].Effect == SPELL_EFFECT_ENERGIZE)
                {
                    items[spellInfo->Effects[i].Effect].push_back(itemId);
                    break;
                }
            }
        }
    }

    uint32 effects[] = { SPELL_EFFECT_HEAL, SPELL_EFFECT_ENERGIZE };
    for (int i = 0; i < sizeof(effects) / sizeof(uint32); ++i)
    {
        uint32 effect = effects[i];
        vector<uint32>& ids = items[effect];
        uint32 index = urand(0, ids.size() - 1);
        if (index >= ids.size())
            continue;

        uint32 itemId = ids[index];
        ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
        bot->StoreNewItemInBestSlots(itemId, urand(1, proto->GetMaxStackSize()));
   }
}

void PlayerbotFactory::InitFood()
{
    map<uint32, vector<uint32> > items;
    ItemTemplateContainer const* itemTemplateContainer = sObjectMgr->GetItemTemplateStore();
    for (ItemTemplateContainer::const_iterator i = itemTemplateContainer->begin(); i != itemTemplateContainer->end(); ++i)
    {
        ItemTemplate const& itemTemplate = i->second;
        uint32 itemId = i->first;
        ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
        if (!proto)
            continue;

        if (proto->Class != ITEM_CLASS_CONSUMABLE ||
            proto->SubClass != ITEM_SUBCLASS_FOOD ||
            (proto->Spells[0].SpellCategory != 11 && proto->Spells[0].SpellCategory != 59) ||
            proto->Bonding != NO_BIND)
            continue;

        if (proto->RequiredLevel > bot->getLevel() || proto->RequiredLevel < bot->getLevel() - 10)
            continue;

        if (proto->RequiredSkill && !bot->HasSkill(proto->RequiredSkill))
            continue;

        if (proto->Area || proto->Map || proto->RequiredCityRank || proto->RequiredHonorRank)
            continue;

        items[proto->Spells[0].SpellCategory].push_back(itemId);
    }

    uint32 categories[] = { 11, 59 };
    for (int i = 0; i < sizeof(categories) / sizeof(uint32); ++i)
    {
        uint32 category = categories[i];
        vector<uint32>& ids = items[category];
        for (int j = 0; j < 5; j++) {
            uint32 index = urand(0, ids.size() - 1);
            if (index >= ids.size())
                continue;

            uint32 itemId = ids[index];
            ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
            // bot->StoreNewItemInBestSlots(itemId, urand(1, proto->GetMaxStackSize()));
            bot->StoreNewItemInBestSlots(itemId, proto->GetMaxStackSize());
        }
   }
}

void PlayerbotFactory::InitClassItems()
{
    if (bot->getClass() == CLASS_ROGUE) {
        vector<int> instant_poison_ids = {43231, 43230, 21927, 8928, 8927, 8926, 6950, 6949, 6947};
        vector<int> deadly_poison_ids = {43233, 43232, 22054, 22053, 20844, 8985, 8984, 2893, 2892};
        for (int& itemId: deadly_poison_ids) {
            ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
            if (proto->RequiredLevel > bot->getLevel())
                continue;
            bot->StoreNewItemInBestSlots(itemId, proto->GetMaxStackSize());
            break;    
        }
        for (int& itemId: instant_poison_ids) {
            ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
            if (proto->RequiredLevel > bot->getLevel())
                continue;
            bot->StoreNewItemInBestSlots(itemId, proto->GetMaxStackSize());
            break;    
        }
    }
    
}

void PlayerbotFactory::CancelAuras()
{
    bot->RemoveAllAuras();
}

void PlayerbotFactory::InitInventory()
{
    InitInventoryTrade();
    InitInventoryEquip();
    InitInventorySkill();
}

void PlayerbotFactory::InitInventorySkill()
{
    if (bot->HasSkill(SKILL_MINING)) {
        StoreItem(2901, 1); // Mining Pick
    }
    if (bot->HasSkill(SKILL_JEWELCRAFTING)) {
        StoreItem(20815, 1); // Jeweler's Kit
        StoreItem(20824, 1); // Simple Grinder
    }
    if (bot->HasSkill(SKILL_BLACKSMITHING) || bot->HasSkill(SKILL_ENGINEERING)) {
        StoreItem(5956, 1); // Blacksmith Hammer
    }
    if (bot->HasSkill(SKILL_ENGINEERING)) {
        StoreItem(6219, 1); // Arclight Spanner
    }
    if (bot->HasSkill(SKILL_ENCHANTING)) {
        StoreItem(44452, 1); // Runed Titanium Rod
    }
    if (bot->HasSkill(SKILL_INSCRIPTION)) {
        StoreItem(39505, 1); // Virtuoso Inking Set
    }
    if (bot->HasSkill(SKILL_SKINNING)) {
        StoreItem(7005, 1); // Skinning Knife
    }
}

Item* PlayerbotFactory::StoreItem(uint32 itemId, uint32 count)
{
    ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
    ItemPosCountVec sDest;
    InventoryResult msg = bot->CanStoreNewItem(INVENTORY_SLOT_BAG_0, NULL_SLOT, sDest, itemId, count);
    if (msg != EQUIP_ERR_OK)
        return NULL;

    return bot->StoreNewItem(sDest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));
}

void PlayerbotFactory::InitInventoryTrade()
{
    vector<uint32> ids;
    ItemTemplateContainer const* itemTemplateContainer = sObjectMgr->GetItemTemplateStore();
    for (ItemTemplateContainer::const_iterator i = itemTemplateContainer->begin(); i != itemTemplateContainer->end(); ++i)
    {
        ItemTemplate const& itemTemplate = i->second;
        uint32 itemId = i->first;
        ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
        if (!proto)
            continue;

        if (proto->Class != ITEM_CLASS_TRADE_GOODS || proto->Bonding != NO_BIND)
            continue;

        if (proto->ItemLevel < bot->getLevel())
            continue;

        if (proto->RequiredLevel > bot->getLevel() || proto->RequiredLevel < bot->getLevel() - 10)
            continue;

        if (proto->RequiredSkill && !bot->HasSkill(proto->RequiredSkill))
            continue;

        ids.push_back(itemId);
    }

    if (ids.empty())
    {
        sLog->outMessage("playerbot", LOG_LEVEL_ERROR, "No trade items available for bot %s (%d level)", bot->GetName().c_str(), bot->getLevel());
        return;
    }

    uint32 index = urand(0, ids.size() - 1);
    if (index >= ids.size())
        return;

    uint32 itemId = ids[index];
    ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
    if (!proto)
        return;

    uint32 count = 1, stacks = 1;
    switch (proto->Quality)
    {
    case ITEM_QUALITY_NORMAL:
        count = proto->GetMaxStackSize();
        stacks = urand(1, 7) / auctionbot.GetRarityPriceMultiplier(proto);
        break;
    case ITEM_QUALITY_UNCOMMON:
        stacks = 1;
        count = urand(1, proto->GetMaxStackSize());
        break;
    case ITEM_QUALITY_RARE:
        stacks = 1;
        count = urand(1, min(uint32(3), proto->GetMaxStackSize()));
        break;
    }

    for (uint32 i = 0; i < stacks; i++)
        StoreItem(itemId, count);
}

void PlayerbotFactory::InitInventoryEquip()
{
    vector<uint32> ids;

    uint32 desiredQuality = itemQuality;
    if (urand(0, 100) < 100 * sPlayerbotAIConfig.randomGearLoweringChance && desiredQuality > ITEM_QUALITY_NORMAL) {
        desiredQuality--;
    }

    ItemTemplateContainer const* itemTemplateContainer = sObjectMgr->GetItemTemplateStore();
    for (ItemTemplateContainer::const_iterator i = itemTemplateContainer->begin(); i != itemTemplateContainer->end(); ++i)
    {
        ItemTemplate const& itemTemplate = i->second;
        uint32 itemId = i->first;
        ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
        if (!proto)
            continue;

        if (proto->Class != ITEM_CLASS_ARMOR && proto->Class != ITEM_CLASS_WEAPON || (proto->Bonding == BIND_WHEN_PICKED_UP ||
                proto->Bonding == BIND_WHEN_USE))
            continue;

        if (proto->Class == ITEM_CLASS_ARMOR && !CanEquipArmor(proto))
            continue;

        if (proto->Class == ITEM_CLASS_WEAPON && !CanEquipWeapon(proto))
            continue;

        if (!CanEquipItem(proto, desiredQuality))
            continue;

        ids.push_back(itemId);
    }

    int maxCount = urand(0, 3);
    int count = 0;
    for (int attempts = 0; attempts < 15; attempts++)
    {
        uint32 index = urand(0, ids.size() - 1);
        if (index >= ids.size())
            continue;

        uint32 itemId = ids[index];
        if (StoreItem(itemId, 1) && count++ >= maxCount)
            break;
   }
}

void PlayerbotFactory::InitGlyphs()
{
    bot->InitGlyphsForLevel();

    for (uint32 slotIndex = 0; slotIndex < MAX_GLYPH_SLOT_INDEX; ++slotIndex)
    {
        bot->SetGlyph(slotIndex, 0);
    }

    uint32 level = bot->getLevel();
    uint32 maxSlot = 0;
    if (level >= 15)
        maxSlot = 2;
    if (level >= 30)
        maxSlot = 3;
    if (level >= 50)
        maxSlot = 4;
    if (level >= 70)
        maxSlot = 5;
    if (level >= 80)
        maxSlot = 6;

    if (!maxSlot)
        return;

    list<uint32> glyphs;
    ItemTemplateContainer const* itemTemplates = sObjectMgr->GetItemTemplateStore();
    for (ItemTemplateContainer::const_iterator i = itemTemplates->begin(); i != itemTemplates->end(); ++i)
    {
        uint32 itemId = i->first;
        ItemTemplate const* proto = &i->second;
        if (!proto)
            continue;

        if (proto->Class != ITEM_CLASS_GLYPH)
            continue;

        if ((proto->AllowableClass & bot->getClassMask()) == 0 || (proto->AllowableRace & bot->getRaceMask()) == 0)
            continue;

        for (uint32 spell = 0; spell < MAX_ITEM_PROTO_SPELLS; spell++)
        {
            uint32 spellId = proto->Spells[spell].SpellId;
            SpellInfo const *entry = sSpellMgr->GetSpellInfo(spellId);
            if (!entry)
                continue;

            for (uint32 effect = 0; effect <= EFFECT_2; ++effect)
            {
                if (entry->Effects[effect].Effect != SPELL_EFFECT_APPLY_GLYPH)
                    continue;

                uint32 glyph = entry->Effects[effect].MiscValue;
                glyphs.push_back(glyph);
            }
        }
    }

    if (glyphs.empty())
    {
        sLog->outMessage("playerbot", LOG_LEVEL_ERROR, "No glyphs found for bot %s", bot->GetName().c_str());
        return;
    }

    set<uint32> chosen;
    for (uint32 slotIndex = 0; slotIndex < maxSlot; ++slotIndex)
    {
        uint32 slot = bot->GetGlyphSlot(slotIndex);
        GlyphSlotEntry const *gs = sGlyphSlotStore.LookupEntry(slot);
        if (!gs)
            continue;

        vector<uint32> ids;
        for (list<uint32>::iterator i = glyphs.begin(); i != glyphs.end(); ++i)
        {
            uint32 id = *i;
            GlyphPropertiesEntry const *gp = sGlyphPropertiesStore.LookupEntry(id);
            if (!gp || gp->TypeFlags != gs->TypeFlags)
                continue;

            ids.push_back(id);
        }

        int maxCount = urand(0, 3);
        int count = 0;
        bool found = false;
        for (int attempts = 0; attempts < 15; ++attempts)
        {
            uint32 index = urand(0, ids.size() - 1);
            if (index >= ids.size())
                continue;

            uint32 id = ids[index];
            if (chosen.find(id) != chosen.end())
                continue;

            chosen.insert(id);

            bot->SetGlyph(slotIndex, id);
            found = true;
            break;
        }
        if (!found)
            sLog->outMessage("playerbot", LOG_LEVEL_ERROR, "No glyphs found for bot %s index %d slot %d", bot->GetName().c_str(), slotIndex, slot);
    }
}

void PlayerbotFactory::InitGuild()
{
	bot->SaveToDB(); //thesawolf - save save save
    if (bot->GetGuildId())
        return;

    if (sPlayerbotAIConfig.randomBotGuilds.empty())
        RandomPlayerbotFactory::CreateRandomGuilds();

    vector<uint32> guilds;
    for(list<uint32>::iterator i = sPlayerbotAIConfig.randomBotGuilds.begin(); i != sPlayerbotAIConfig.randomBotGuilds.end(); ++i)
        guilds.push_back(*i);

    if (guilds.empty())
    {
        sLog->outMessage("playerbot", LOG_LEVEL_ERROR, "No random guilds available");
        return;
    }

    int index = urand(0, guilds.size() - 1);
    uint32 guildId = guilds[index];
    Guild* guild = sGuildMgr->GetGuildById(guildId);
    if (!guild)
    {
        sLog->outMessage("playerbot", LOG_LEVEL_ERROR, "Invalid guild %u", guildId);
        return;
    }

    if (guild->GetMemberCount() < 20)
        guild->AddMember(bot->GetGUID(), urand(GR_OFFICER, GR_INITIATE));
	bot->SaveToDB(); //thesawolf - save save save
}

float PlayerbotFactory::CalculateItemScore(uint32 item_id)
{
    float score = 0;
    int tab = AiFactory::GetPlayerSpecTab(bot);
    ItemTemplateContainer const* itemTemplates = sObjectMgr->GetItemTemplateStore();
    ItemTemplate const* proto = &itemTemplates->at(item_id);
    uint8 cls = bot->getClass();
    int agility = 0, strength = 0, intellect = 0, spirit = 0;
    int stamina = 0, defense = 0, dodge = 0, parry = 0, block = 0, resilience = 0;
    int hit = 0, crit = 0, haste = 0, expertise = 0, attack_power = 0;
    int mana_regeneration = 0, spell_power = 0, armor_penetration = 0, spell_penetration = 0;
    int armor = 0;
    int itemLevel = proto->ItemLevel;
    int quality = proto->Quality;
    int dps = (proto->Damage[0].DamageMin + proto->Damage[0].DamageMax) / 2 * proto->Delay / 1000;
    armor += proto->Armor;
    block += proto->Block;
    for (int i = 0; i < proto->StatsCount; i++) {
        const _ItemStat &stat = proto->ItemStat[i];
        const int32 &value = stat.ItemStatValue;
        switch (stat.ItemStatType) {
            case ITEM_MOD_AGILITY:
                agility += value;
                break;
            case ITEM_MOD_STRENGTH:
                strength += value;
                break;
            case ITEM_MOD_INTELLECT:
                intellect += value;
                break;
            case ITEM_MOD_SPIRIT:
                spirit += value;
                break;
            case ITEM_MOD_STAMINA:
                stamina += value;
                break;
            case ITEM_MOD_DEFENSE_SKILL_RATING:
                defense += value;
                break;
            case ITEM_MOD_PARRY_RATING:
                parry += value;
                break;
            case ITEM_MOD_BLOCK_RATING:
            case ITEM_MOD_BLOCK_VALUE:
                block += value;
                break;
            case ITEM_MOD_RESILIENCE_RATING:
                resilience += value;
                break;
            case ITEM_MOD_HIT_RATING:
                hit += value;
                break;
            case ITEM_MOD_CRIT_RATING:
                crit += value;
                break;
            case ITEM_MOD_HASTE_RATING:
                haste += value;
                break;
            case ITEM_MOD_EXPERTISE_RATING:
                expertise += value;
                break;
            case ITEM_MOD_ATTACK_POWER:
                attack_power += value;
                break;
            case ITEM_MOD_SPELL_POWER:
                spell_power += value;
                break;
            case ITEM_MOD_MANA_REGENERATION:
                mana_regeneration += value;
                break;
            default:
                break;
        }
    }
    if (cls == CLASS_HUNTER) {
        // AGILITY only
        score = agility * 2.5 + attack_power + armor_penetration * 2 + dps * 5 + hit * 3 + crit * 2 + haste * 2.5 + intellect;
    } else if (cls == CLASS_WARLOCK || 
               cls == CLASS_MAGE || 
               (cls == CLASS_PRIEST && tab == 2) || // shadow
               (cls == CLASS_SHAMAN && tab == 0) || // element
               (cls == CLASS_DRUID && tab == 0) // balance
              ) {
        // SPELL DPS
        score = intellect * 0.5 + spirit * 0.5 + spell_power + spell_penetration 
            + hit * 1.5 + crit * 0.7 + haste * 1;       
    } else if ((cls == CLASS_PALADIN && tab == 0) || // holy
               (cls == CLASS_PRIEST && tab != 2) || // discipline / holy
               (cls == CLASS_SHAMAN && tab == 2) || // heal
               (cls == CLASS_DRUID && tab == 2)
              ) {
        // HEALER
        score = intellect * 0.5 + spirit * 0.5 + spell_power + mana_regeneration * 0.5 + crit * 0.5 + haste * 1;       
    } else if (cls == CLASS_ROGUE) {
        // AGILITY mainly (STRENGTH also)
        score = agility * 2 + strength + attack_power + armor_penetration * 1 + dps * 5 + hit * 2 + crit * 1.5 + haste * 1.5 + expertise * 2.5;
    } else if  ((cls == CLASS_PALADIN && tab == 2) || // retribution
                (cls == CLASS_WARRIOR && tab != 2) || // arm / fury
                (cls == CLASS_DEATH_KNIGHT && tab != 0) // ice / unholy
               ) {
        // STRENGTH mainly (AGILITY also)
        score = strength * 2 + agility + attack_power + armor_penetration + dps * 5 + hit * 1.5 + crit * 1.5 + haste * 1.5 + expertise * 2;
    } else if ((cls == CLASS_SHAMAN && tab == 1)) { // enhancement
        // STRENGTH mainly (AGILITY, INTELLECT also)
        score = strength * 1 + agility * 1.5 + intellect * 1.5 + attack_power + spell_power * 1.5 + armor_penetration * 0.5 + dps * 5
            + hit * 2 + crit * 1.5 + haste * 1.5 + expertise * 2;
    } else if ((cls == CLASS_WARRIOR && tab == 2) || 
               (cls == CLASS_PALADIN && tab == 1)) {
        // TANK WITH SHIELD
        score = strength * 1 + agility * 2 + attack_power * 0.2
            + defense * 2.5 + parry * 2 + dodge * 2 + resilience * 2 + block * 2 + armor * 0.2 + stamina * 3
            + hit * 1 + crit * 0.2 + haste * 0.5 + expertise * 3;
    } else if (cls == CLASS_DEATH_KNIGHT && tab == 0){
        // BLOOD DK TANK
        score = strength * 1 + agility * 2 + attack_power * 0.2
            + defense * 3.5 + parry * 2 + dodge * 2 + resilience * 2 + armor * 0.2 + stamina * 2.5 
            + hit * 2 + crit * 0.5 + haste * 0.5 + expertise * 3.5;
    } else {
        // BEAR DRUID TANK (AND FERAL DRUID...?)
        score = agility * 1.5 + strength * 1 + attack_power * 0.5 + armor_penetration * 0.5 + dps * 2
            + defense * 0.25 + dodge * 0.25 + armor * 0.25 + stamina * 1.5
            + hit * 1 + crit * 1 + haste * 0.5 + expertise * 3;
    }
    if (NotSameArmorType(proto->SubClass))
    {
        score *= 0.8;
    }
    bool isDoubleHand = proto->Class == ITEM_CLASS_WEAPON && 
        !(ITEM_SUBCLASS_SINGLE_HAND & (1 << proto->SubClass)) && 
        !(ITEM_SUBCLASS_MASK_WEAPON_RANGED & (1 << proto->SubClass));
    // shield tank
    if (isDoubleHand && IsShieldTank()) {
        score *= 0.5;
    }
    // double hand penalty (except fury (talent), bear, retribution (cannot double-hand))
    if (isDoubleHand && 
        !(cls == CLASS_WARRIOR && tab == 1) && 
        !(cls == CLASS_DRUID && tab == 1) &&
        !(cls == CLASS_PALADIN && tab == 2)) {
        score *= 0.5;
    }
    // enhancement, rogue, ice/unholy dk
    if (isDoubleHand && 
        ((cls == CLASS_SHAMAN && tab == 1) ||
         (cls == CLASS_ROGUE) ||
         (cls == CLASS_DEATH_KNIGHT && tab != 0))
       ) {
        score *= 0.5;
    }
    return (0.01 + score) * itemLevel * (quality + 1);   
    // return score;
}

bool PlayerbotFactory::IsShieldTank() {
    int tab = AiFactory::GetPlayerSpecTab(bot);
    return (bot->getClass() == CLASS_WARRIOR && tab == 2) || (bot->getClass() == CLASS_PALADIN && tab == 1); 
}