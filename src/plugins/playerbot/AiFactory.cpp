#include "../pchdef.h"
#include "playerbot.h"
#include "AiFactory.h"
#include "strategy/Engine.h"

#include "strategy/priest/PriestAiObjectContext.h"
#include "strategy/mage/MageAiObjectContext.h"
#include "strategy/warlock/WarlockAiObjectContext.h"
#include "strategy/warrior/WarriorAiObjectContext.h"
#include "strategy/shaman/ShamanAiObjectContext.h"
#include "strategy/paladin/PaladinAiObjectContext.h"
#include "strategy/druid/DruidAiObjectContext.h"
#include "strategy/hunter/HunterAiObjectContext.h"
#include "strategy/rogue/RogueAiObjectContext.h"
#include "strategy/DK/DKAiObjectContext.h"
#include "../Entities/Player/Player.h"
#include "PlayerbotAIConfig.h"
#include "RandomPlayerbotMgr.h"


AiObjectContext* AiFactory::createAiObjectContext(Player* player, PlayerbotAI* ai)
{
    switch (player->getClass())
    {
    case CLASS_PRIEST:
        return new PriestAiObjectContext(ai);
        break;
    case CLASS_MAGE:
        return new MageAiObjectContext(ai);
        break;
    case CLASS_WARLOCK:
        return new WarlockAiObjectContext(ai);
        break;
    case CLASS_WARRIOR:
        return new WarriorAiObjectContext(ai);
        break;
    case CLASS_SHAMAN:
        return new ShamanAiObjectContext(ai);
        break;
    case CLASS_PALADIN:
        return new PaladinAiObjectContext(ai);
        break;
	case CLASS_DEATH_KNIGHT:
		return new DKAiObjectContext(ai);
		break;
    case CLASS_DRUID:
        return new DruidAiObjectContext(ai);
        break;
    case CLASS_HUNTER:
        return new HunterAiObjectContext(ai);
        break;
    case CLASS_ROGUE:
        return new RogueAiObjectContext(ai);
        break;
    }
    return new AiObjectContext(ai);
}

int AiFactory::GetPlayerSpecTab(Player* player)
{
    int c0 = 0, c1 = 0, c2 = 0;
    PlayerTalentMap& talentMap = player->GetTalentMap(player->GetActiveSpec());
    for (PlayerTalentMap::iterator i = talentMap.begin(); i != talentMap.end(); ++i)
    {
        uint32 spellId = i->first;
        TalentSpellPos const* talentPos = GetTalentSpellPos(spellId);
        if(!talentPos)
            continue;

        TalentEntry const* talentInfo = sTalentStore.LookupEntry(talentPos->talent_id);
        if (!talentInfo)
            continue;

        uint32 const* talentTabIds = GetTalentTabPages(player->getClass());
        if (talentInfo->TalentTab == talentTabIds[0]) c0++;
        if (talentInfo->TalentTab == talentTabIds[1]) c1++;
        if (talentInfo->TalentTab == talentTabIds[2]) c2++;
    }

    if (c0 >= c1 && c0 >= c2)
        return 0;

    if (c1 >= c0 && c1 >= c2)
        return 1;

    return 2;
}

void AiFactory::AddDefaultCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* engine)
{
    int tab = GetPlayerSpecTab(player);
    int level = player->getLevel();
	if (player->InBattleground() && player->GetBattlegroundTypeId()==BattlegroundTypeId::BATTLEGROUND_WS)
	{
		engine->addStrategies("warsong", "attack weak", "racials", "chat", "default", "dps", "potions", "cast time", "conserve mana", "duel", "pvp", NULL);
	}
	else {
		// engine->addStrategies("attack weak", , "chat", "default", "aoe", "potions", "cast time", "conserve mana", "duel", "pvp", NULL);
        engine->addStrategies("attack weak", "racials", "chat", "default", "aoe", "cast time", "duel", "pvp", NULL);
	}

    switch (player->getClass())
    {
        case CLASS_PRIEST:
            if (tab == 2)
            {
                engine->addStrategies("dps", "threat", "dps debuff", NULL);
                // if (player->getLevel() > 19)
                //     engine->addStrategy();
            }
            else {
                engine->ChangeStrategy("-shadow aoe");
                engine->addStrategy("heal");
            }

            // engine->addStrategy("flee");
            break;
        case CLASS_MAGE:
            if (tab == 0)
                engine->addStrategies("arcane", "arcane aoe", "threat", NULL);
            else if (tab == 1)
                engine->addStrategies("fire", "fire aoe", "threat", NULL);
            else
                engine->addStrategies("frost", "frost aoe", "threat", NULL);

            // engine->addStrategy("flee");
            break;
        case CLASS_WARRIOR:
            if (level < 80) {
                engine->addStrategy("bdps");
            } else {
                engine->addStrategy("bhealth");
            }
            if (tab == 2) {
                engine->addStrategies("tank", "tank aoe", NULL);
                engine->ChangeStrategy("-aoe");
            }
            else if (tab == 0) {
                engine->addStrategies("dps", "threat", NULL);
            } else if (tab == 1) {
                engine->addStrategies("melee", "threat", NULL);
                engine->ChangeStrategy("-aoe");
            }
            break;
		case CLASS_DEATH_KNIGHT:
			if (tab == 0)
				engine->addStrategies("blood", "tank aoe", NULL);
			else if (tab == 1)
				engine->addStrategies("frost", "frost aoe", "threat", NULL);
			else
				engine->addStrategies("unholy", "unholy aoe", "threat", NULL);
			break;
        case CLASS_SHAMAN:
            if (tab == 0)
                engine->addStrategies("caster", "caster aoe", "bmana", "threat", NULL);
            else if (tab == 2)
                engine->addStrategies("heal", "bmana", NULL);
            else
                engine->addStrategies("dps", "melee aoe", "bdps", "threat", NULL);
            engine->addStrategies("totems", NULL);
            break;
        case CLASS_PALADIN:
            if (tab == 0)
                engine->addStrategies("heal", "cure", NULL);
            else if (tab == 1)
                engine->addStrategies("tank", "tank aoe", "cure", NULL);
            else
                engine->addStrategies("dps", "threat", "cure", NULL);
            break;
        case CLASS_DRUID:
            if (tab == 0)
            {
                engine->addStrategies("caster", "caster aoe", "threat", NULL);
                if (player->getLevel() > 19)
                    engine->addStrategy("caster debuff");
            }
            else if (tab == 2)
                engine->addStrategies("heal", NULL);
            else
                engine->addStrategies("bear", "tank aoe", NULL);
            break;
        case CLASS_HUNTER:
            engine->addStrategies("dps", "bdps", "threat", "dps debuff", NULL);
            // if (player->getLevel() > 19)
            //     engine->addStrategy();
			// engine->addStrategy("flee");
			break;
        case CLASS_ROGUE:
            if (tab == 0) {
                engine->addStrategies("melee", "threat", NULL);
            } else {
                engine->addStrategies("dps", "threat", NULL);
            }
            break;
        case CLASS_WARLOCK:
            // if (tab == 1)
            //     engine->addStrategies("tank", "threat", NULL);
            // else
            engine->addStrategies("dps", "threat", NULL);

            // if (player->getLevel() > 19)
            engine->addStrategy("dps debuff");

            // engine->addStrategy("flee");
            break;
    }

	if (sRandomPlayerbotMgr.IsRandomBot(player))
	{
		if (!player->GetGroup())
		{
			engine->ChangeStrategy(sPlayerbotAIConfig.randomBotCombatStrategies);
			if (player->getClass() == CLASS_DRUID && player->getLevel() < 20)
			{
				engine->addStrategies("bear", NULL);
			}
		}
	}
	else
	{
		engine->ChangeStrategy(sPlayerbotAIConfig.combatStrategies);
	}
}

Engine* AiFactory::createCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
	Engine* engine = new Engine(facade, AiObjectContext);
    AddDefaultCombatStrategies(player, facade, engine);
    return engine;
}

void AiFactory::AddDefaultNonCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* nonCombatEngine)
{
    int tab = GetPlayerSpecTab(player);

    switch (player->getClass()){
        case CLASS_PALADIN:
            if (tab == 1)
                nonCombatEngine->addStrategy("bhealth");
            else if (tab == 0)
                nonCombatEngine->addStrategy("bmana");
            else
                nonCombatEngine->addStrategy("bdps");
            break;
        case CLASS_HUNTER:
            nonCombatEngine->addStrategy("bdps");
            break;
        case CLASS_SHAMAN:
            if (tab == 0 || tab == 2)
                nonCombatEngine->addStrategy("bmana");
            else
                nonCombatEngine->addStrategy("bdps");
            break;
        case CLASS_MAGE:
            if (tab == 0 || tab == 1)
                nonCombatEngine->addStrategy("bdps");
            else
                nonCombatEngine->addStrategy("bmana");
            break;
        case CLASS_DRUID:
            if (tab == 1)
                nonCombatEngine->addStrategies("tank aoe", "bhealth", NULL);
            else
                nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_WARRIOR:
            if (tab == 2)
                nonCombatEngine->addStrategy("tank aoe");
            else
                nonCombatEngine->addStrategy("dps assist");
            break;
            nonCombatEngine->addStrategy("dps assist");
            break;
		case CLASS_DEATH_KNIGHT:
			if (tab == 0)
				nonCombatEngine->addStrategy("tank");
			else
				nonCombatEngine->addStrategy("dps assist");
			break;
        case CLASS_WARLOCK:
            if (tab == 0) {
                nonCombatEngine->addStrategy("bmana");
            } else if (tab == 1) {
                nonCombatEngine->addStrategy("bdps");
            } else if (tab == 2) {
                nonCombatEngine->addStrategy("bhealth");
            }
            nonCombatEngine->addStrategy("dps assist");
            break;
		default:
			nonCombatEngine->addStrategy("dps assist");
			break;
		
    }
	if (player->InBattleground())
	{
		nonCombatEngine->addStrategies("grind", "warsong", "nc", "attack weak", "food", "chat",
+			"default", "quest", "loot", "gather", "duel", "emote", "lfg", "bg", "conserve mana", NULL);
	}
	else {
// 		nonCombatEngine->addStrategies("nc", "attack weak", "food", "stay", "chat",
// +			"default", "quest", "loot", "gather", "duel", "emote", "follow", "lfg", "bg", "conserve mana", NULL);
        nonCombatEngine->addStrategies("nc", "attack weak", "food", "stay", "chat",
+			"default", "quest", "loot", "gather", "duel", "follow", "lfg", "bg", NULL);
	}

	if (sRandomPlayerbotMgr.IsRandomBot(player))
	{
		if (!player->GetGroup())
		{
			nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.randomBotNonCombatStrategies);
		}
	}
	else
	{
		nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.nonCombatStrategies);
	}
}

Engine* AiFactory::createNonCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
	Engine* nonCombatEngine = new Engine(facade, AiObjectContext);

    AddDefaultNonCombatStrategies(player, facade, nonCombatEngine);
	return nonCombatEngine;
}

void AiFactory::AddDefaultDeadStrategies(Player* player, PlayerbotAI* const facade, Engine* deadEngine)
{
    deadEngine->addStrategies("dead", "stay", "chat", "default", "follow", NULL);
    if (sRandomPlayerbotMgr.IsRandomBot(player) && !player->GetGroup())
    {
        deadEngine->removeStrategy("follow");
    }
}

Engine* AiFactory::createDeadEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
    Engine* deadEngine = new Engine(facade, AiObjectContext);
    AddDefaultDeadStrategies(player, facade, deadEngine);
    return deadEngine;
}
