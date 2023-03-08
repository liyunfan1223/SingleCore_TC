#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"

using namespace ai;

NextAction** HealPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

void HealPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), NULL)));

	triggers.push_back(new TriggerNode(
		"medium aoe heal",
		NextAction::array(0, new NextAction("circle of healing", 27.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
		NextAction::array(0,
            new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 4),
            new NextAction("penance on party", ACTION_CRITICAL_HEAL + 5), 
            new NextAction("flash heal on party", ACTION_CRITICAL_HEAL + 3),
            new NextAction("prayer of mending on party", ACTION_CRITICAL_HEAL + 2),
            NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
		NextAction::array(0,
            new NextAction("power word: shield on party", ACTION_MEDIUM_HEAL + 5),
            new NextAction("penance on party", ACTION_MEDIUM_HEAL + 4), 
            new NextAction("prayer of mending on party", ACTION_MEDIUM_HEAL + 3),
            new NextAction("flash heal on party", ACTION_MEDIUM_HEAL + 2),
            NULL)));

	triggers.push_back(new TriggerNode(
        "party member medium health",
		NextAction::array(0,
            new NextAction("power word: shield on party", ACTION_LIGHT_HEAL + 9),
            new NextAction("penance on party", ACTION_LIGHT_HEAL + 8), 
            new NextAction("prayer of mending on party", ACTION_LIGHT_HEAL + 7),
            new NextAction("flash heal on party", ACTION_LIGHT_HEAL + 6),
            // new NextAction("renew on party", ACTION_LIGHT_HEAL + 8),
            NULL)));
    
    triggers.push_back(new TriggerNode(
        "party member almost full health",
		NextAction::array(0, 
            // new NextAction("penance on party", ACTION_LIGHT_HEAL + 3), 
            new NextAction("renew on party", ACTION_LIGHT_HEAL + 2),
            NULL)));

    // triggers.push_back(new TriggerNode(
    //     "almost full health",
    //     NextAction::array(0, new NextAction("renew", 15.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member almost full health",
    //     NextAction::array(0, new NextAction("renew on party", 10.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "enemy too close for spell",
    //     NextAction::array(0, new NextAction("flee", 49.0f), NULL)));
}
