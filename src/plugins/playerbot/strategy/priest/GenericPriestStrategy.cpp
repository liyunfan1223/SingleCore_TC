#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"
#include "GenericPriestStrategyActionNodeFactory.h"
#include "Strategy.h"

using namespace ai;

GenericPriestStrategy::GenericPriestStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericPriestStrategyActionNodeFactory());
}

void GenericPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("power word: shield", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("power word: shield", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic on party",
        NextAction::array(0, new NextAction("dispel magic on party", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("abolish disease on party", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
        NextAction::array(0, new NextAction("shadowfiend", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
		NextAction::array(0, new NextAction("flee", 49.0f), NULL)));
        
    // triggers.push_back(new TriggerNode(
    //     "medium threat",
    //     NextAction::array(0, new NextAction("psychic scream", 50.0f), NULL)));

}
