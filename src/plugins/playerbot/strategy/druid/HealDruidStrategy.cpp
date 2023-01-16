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
        creators["natures swiftness"] = &natures_swiftness;
        creators["nourish on party"] = &nourish_on_party;
    }
    static ActionNode* natures_swiftness(PlayerbotAI* ai)
    {
        return new ActionNode ("natures swiftness",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("healing touch on party"), NULL));
    }
    static ActionNode* nourish_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("nourish_on_party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing touch on party"), NULL),
            /*C*/ NULL);
    }
private:
};

HealDruidStrategy::HealDruidStrategy(PlayerbotAI* ai) : GenericDruidStrategy(ai)
{
    actionNodeFactories.Add(new HealDruidStrategyActionNodeFactory());
}

void HealDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);
    // GENERAL 
    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "tree of life",
        NextAction::array(0, new NextAction("tree of life", ACTION_NORMAL + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_EMERGENCY + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "entangling roots",
        NextAction::array(0, new NextAction("entangling roots on cc", ACTION_HIGH + 1), NULL)));

    // CRITICAL
    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("nourish on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("wild growth", ACTION_CRITICAL_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("swiftmend on party", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("natures swiftness", ACTION_CRITICAL_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "median aoe heal",
        NextAction::array(0, new NextAction("tranquility", ACTION_CRITICAL_HEAL + 5), NULL)));

    // LOW
    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("nourish on party", ACTION_MEDIUM_HEAL + 6), NULL)));\

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("swiftmend on party", ACTION_MEDIUM_HEAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 8), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member low health",
    //     NextAction::array(0, new NextAction("lifebloom on party", ACTION_MEDIUM_HEAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("wild growth", ACTION_MEDIUM_HEAL + 9), NULL)));

    // MEDIUM
    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("nourish on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 3), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member medium health",
    //     NextAction::array(0, new NextAction("lifebloom on party", ACTION_MEDIUM_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("wild growth on party", ACTION_MEDIUM_HEAL + 5), NULL)));

    // almost full
    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("wild growth on party", ACTION_LIGHT_HEAL + 3), NULL)));

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
