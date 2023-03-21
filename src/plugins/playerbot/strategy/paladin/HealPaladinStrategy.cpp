#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "HealPaladinStrategy.h"

using namespace ai;

HealPaladinStrategy::HealPaladinStrategy(PlayerbotAI* ai) : GenericPaladinStrategy(ai)
{
}

NextAction** HealPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, 
        new NextAction("judgement of light", ACTION_NORMAL + 1),
        NULL);
}

void HealPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
		NextAction::array(0,
            new NextAction("holy shock on party", ACTION_CRITICAL_HEAL + 5), 
            new NextAction("holy light on party", ACTION_CRITICAL_HEAL + 4),
            // new NextAction("power word: shield", ACTION_CRITICAL_HEAL + 4),
            // new NextAction("flash heal on party", ACTION_CRITICAL_HEAL + 3),
            // new NextAction("prayer of mending on party", ACTION_CRITICAL_HEAL + 2),
            NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
		NextAction::array(0,
            new NextAction("holy light on party", ACTION_MEDIUM_HEAL + 5), 
            // new NextAction("power word: shield", ACTION_MEDIUM_HEAL + 4),
            // new NextAction("prayer of mending on party", ACTION_MEDIUM_HEAL + 3),
            // new NextAction("flash heal on party", ACTION_MEDIUM_HEAL + 2),
            NULL)));

	triggers.push_back(new TriggerNode(
        "party member medium health",
		NextAction::array(0,
            new NextAction("holy light on party", ACTION_LIGHT_HEAL + 9),
            new NextAction("flash of light on party", ACTION_LIGHT_HEAL + 8),
            // new NextAction("penance on party", ACTION_LIGHT_HEAL + 8), 
            // new NextAction("power word: shield", ACTION_LIGHT_HEAL + 7),
            // new NextAction("prayer of mending on party", ACTION_LIGHT_HEAL + 6),
            // new NextAction("flash heal on party", ACTION_LIGHT_HEAL + 5),
            NULL)));
    
    triggers.push_back(new TriggerNode(
        "party member almost full health",
		NextAction::array(0, 
            new NextAction("flash of light on party", ACTION_LIGHT_HEAL + 3),
            // new NextAction("penance on party", ACTION_LIGHT_HEAL + 2), 
            NULL)));

    triggers.push_back(new TriggerNode(
        "beacon of light on main tank",
		NextAction::array(0, new NextAction("beacon of light on main tank", ACTION_CRITICAL_HEAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "sacred shield on main tank",
		NextAction::array(0, new NextAction("sacred shield on main tank", ACTION_CRITICAL_HEAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
		NextAction::array(0, new NextAction("flee", 49.0f), NULL)));
        
    // triggers.push_back(new TriggerNode(
    //     "medium health",
    //     NextAction::array(0, new NextAction("flash of light", ACTION_MEDIUM_HEAL + 3), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member medium health",
    //     NextAction::array(0, new NextAction("flash of light on party", ACTION_MEDIUM_HEAL + 2), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member almost full health",
    //     NextAction::array(0, new NextAction("flash of light on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "blessing",
    //     NextAction::array(0, new NextAction("blessing of sanctuary", ACTION_HIGH + 9), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "low health",
    //     NextAction::array(0, new NextAction("divine protection", ACTION_CRITICAL_HEAL + 2), new NextAction("holy light", ACTION_CRITICAL_HEAL + 2), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member low health",
    //     NextAction::array(0, new NextAction("holy light on party", ACTION_CRITICAL_HEAL + 1), NULL)));
}
