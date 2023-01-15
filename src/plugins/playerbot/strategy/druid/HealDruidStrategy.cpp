#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "HealDruidStrategy.h"

using namespace ai;

class HealDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    HealDruidStrategyActionNodeFactory()
    {
        // creators["tree of life"] = &tree_of_life;
    }
    // static ActionNode* tree_of_life(PlayerbotAI* ai)
    // {
    //     return new ActionNode ("tree of life",
    //         /*P*/ NULL,
    //         /*A*/ NULL,
    //         /*C*/ NULL);
    // }
private:
};

HealDruidStrategy::HealDruidStrategy(PlayerbotAI* ai) : GenericDruidStrategy(ai)
{
    // actionNodeFactories.Add(new HealDruidStrategyActionNodeFactory());
}

void HealDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);
    // GENERAL 
    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "tree of life",
    //     NextAction::array(0, new NextAction("tree of life", ACTION_NORMAL + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", ACTION_EMERGENCY + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "entangling roots",
        NextAction::array(0, new NextAction("entangling roots on cc", ACTION_HIGH + 1), NULL)));

    // CRITICAL
    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("healing touch", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("healing touch on party", ACTION_CRITICAL_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("wild growth", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "low aoe heal",
        NextAction::array(0, new NextAction("tranquility", ACTION_CRITICAL_HEAL + 4), NULL)));

    // LOW
    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("healing touch", ACTION_MEDIUM_HEAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing touch on party", ACTION_MEDIUM_HEAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("wild growth", ACTION_MEDIUM_HEAL + 8), NULL)));

    // MEDIUM
    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("healing touch", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("healing touch on party", ACTION_CRITICAL_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("wild growth on party", ACTION_MEDIUM_HEAL + 5), NULL)));

    // almost full
    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("wild growth on party", ACTION_MEDIUM_HEAL + 3), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "almost full health",
    //     NextAction::array(0, new NextAction("healing touch", ACTION_EMERGENCY + 3), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member almost full health",
    //     NextAction::array(0, new NextAction("healing touch on party", ACTION_EMERGENCY + 4), NULL)));

    

    // triggers.push_back(new TriggerNode(
    //     "medium aoe heal",
    //     NextAction::array(0, new NextAction("tranquility", ACTION_CRITICAL_HEAL + 3), NULL)));
}
