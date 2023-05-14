#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "PriestNonCombatStrategy.h"
#include "PriestNonCombatStrategyActionNodeFactory.h"

using namespace ai;

PriestNonCombatStrategy::PriestNonCombatStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new PriestNonCombatStrategyActionNodeFactory());
}

void PriestNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    // triggers.push_back(new TriggerNode(
    //     "power word: fortitude",
    //     NextAction::array(0, new NextAction("power word: fortitude", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "power word: fortitude on party",
        NextAction::array(0, new NextAction("prayer of fortitude on party", 11.0f), NULL)));


    // triggers.push_back(new TriggerNode(
    //     "divine spirit",
    //     NextAction::array(0, new NextAction("divine spirit", 14.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit on party",
        NextAction::array(0, new NextAction("prayer of spirit on party", 13.0f), NULL)));


    triggers.push_back(new TriggerNode(
        "inner fire",
        NextAction::array(0, new NextAction("inner fire", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
		NextAction::array(0,
            new NextAction("renew on party", ACTION_CRITICAL_HEAL + 3),
            new NextAction("penance on party", ACTION_CRITICAL_HEAL + 2), 
            new NextAction("greater heal on party", ACTION_CRITICAL_HEAL + 1),
            NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
		NextAction::array(0,
            new NextAction("renew on party", ACTION_MEDIUM_HEAL + 3),
            new NextAction("penance on party", ACTION_MEDIUM_HEAL + 2), 
            new NextAction("greater heal on party", ACTION_MEDIUM_HEAL + 1),
            NULL)));

	triggers.push_back(new TriggerNode(
        "party member medium health",
		NextAction::array(0,
            new NextAction("renew on party", ACTION_LIGHT_HEAL + 9),
            new NextAction("penance on party", ACTION_LIGHT_HEAL + 8),
            NULL)));
    
    triggers.push_back(new TriggerNode(
        "party member almost full health",
		NextAction::array(0, 
            new NextAction("renew on party", ACTION_LIGHT_HEAL + 3),
            new NextAction("penance on party", ACTION_LIGHT_HEAL + 2), 
            NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("circle of healing", 27.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member to resurrect",
		NextAction::array(0, new NextAction("resurrection", ACTION_HIGH + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic",
        NextAction::array(0, new NextAction("dispel magic", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic on party",
        NextAction::array(0, new NextAction("dispel magic on party", 40.0f), NULL)));


    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("abolish disease", 31.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("abolish disease on party", 30.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"in battleground without flag",
		NextAction::array(0, new NextAction("mount", 1.0f), NULL)));

}
