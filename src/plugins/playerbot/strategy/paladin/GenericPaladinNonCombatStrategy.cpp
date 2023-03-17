#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "GenericPaladinNonCombatStrategy.h"
#include "GenericPaladinStrategyActionNodeFactory.h"

using namespace ai;

GenericPaladinNonCombatStrategy::GenericPaladinNonCombatStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericPaladinStrategyActionNodeFactory());
}

void GenericPaladinNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
		"party member to resurrect",
		NextAction::array(0, new NextAction("redemption", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("flash of light on party", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("holy light on party", 26.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", 27.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("holy light on party", 28.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "cleanse cure disease",
    //     NextAction::array(0, new NextAction("cleanse disease", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", 40.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "cleanse cure poison",
    //     NextAction::array(0, new NextAction("cleanse poison", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", 40.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "cleanse cure magic",
    //     NextAction::array(0, new NextAction("cleanse magic", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure magic",
        NextAction::array(0, new NextAction("cleanse magic on party", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"in battleground without flag",
		NextAction::array(0, new NextAction("mount", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
		NextAction::array(0, new NextAction("divine plea", ACTION_HIGH), NULL)));

}
