#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "TankPaladinStrategy.h"

using namespace ai;

TankPaladinStrategy::TankPaladinStrategy(PlayerbotAI* ai) : GenericPaladinStrategy(ai)
{
}

NextAction** TankPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0,
        new NextAction("shield of righteousness", ACTION_NORMAL + 6),
        new NextAction("hammer of the righteous", ACTION_NORMAL + 5),
        new NextAction("judgement of wisdom", ACTION_NORMAL + 4),
        // new NextAction("avenger's shield", ACTION_NORMAL + 3), 
        // new NextAction("consecration", ACTION_NORMAL + 2),
        new NextAction("melee", ACTION_NORMAL), 
        NULL);
}

void TankPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    // triggers.push_back(new TriggerNode(
    //     "judgement of light",
    //     NextAction::array(0, new NextAction("judgement of light", ACTION_NORMAL + 2), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "medium mana",
    //     NextAction::array(0, new NextAction("judgement of wisdom", ACTION_NORMAL + 3), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "judgement",
    //     NextAction::array(0, new NextAction("judgement", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "righteous fury",
        NextAction::array(0, new NextAction("righteous fury", ACTION_HIGH + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 1), new NextAction("avenger's shield", ACTION_HIGH + 3), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "light aoe",
    //     NextAction::array(0, new NextAction("hammer of the righteous", ACTION_HIGH + 6), new NextAction("avenger's shield", ACTION_HIGH + 6), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "medium aoe",
    //     NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("hand of reckoning", ACTION_HIGH + 7), NULL)));

	triggers.push_back(new TriggerNode(
		"holy shield",
		NextAction::array(0, new NextAction("holy shield", ACTION_HIGH + 7), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "blessing",
    //     NextAction::array(0, new NextAction("blessing of sanctuary", ACTION_HIGH + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_NORMAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("reach melee", ACTION_NORMAL + 8), NULL)));
    
}
