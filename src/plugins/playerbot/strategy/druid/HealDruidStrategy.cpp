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
        creators["nature's swiftness"] = &natures_swiftness;
        creators["nourish on party"] = &nourish_on_party;
    }
    static ActionNode* natures_swiftness(PlayerbotAI* ai)
    {
        return new ActionNode ("nature's swiftness",
            /*P*/ NULL,
            /*A*/ NULL,
            // /*C*/ NULL);
            /*C*/ NextAction::array(0, new NextAction("healing touch on party"), NULL));
    }
    static ActionNode* nourish_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("nourish on party",
            /*P*/ NULL,
            // /*A*/ NULL,
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
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL + 7), NULL)));

    // CRITICAL
    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, 
            new NextAction("swiftmend on party", ACTION_CRITICAL_HEAL + 3), 
            new NextAction("wild growth", ACTION_CRITICAL_HEAL + 2),
            new NextAction("nourish on party", ACTION_CRITICAL_HEAL + 1),
            // new NextAction("healing touch on party", ACTION_CRITICAL_HEAL + 0),
            NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("nature's swiftness", ACTION_CRITICAL_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("tranquility", ACTION_CRITICAL_HEAL + 5), NULL)));

    // LOW
    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("wild growth on party", ACTION_MEDIUM_HEAL + 9),
            new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 8),
            new NextAction("swiftmend on party", ACTION_MEDIUM_HEAL + 7),
            new NextAction("nourish on party", ACTION_MEDIUM_HEAL + 6),
            // new NextAction("healing touch on party", ACTION_MEDIUM_HEAL + 5), 
            NULL)));

    // MEDIUM
    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("wild growth on party", ACTION_MEDIUM_HEAL + 4), 
            new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 3),
            new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 2),
            new NextAction("nourish on party", ACTION_MEDIUM_HEAL + 1),
            NULL)));

    // almost full
    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("wild growth on party", ACTION_LIGHT_HEAL + 3),
            new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL + 2), 
            new NextAction("regrowth on party", ACTION_LIGHT_HEAL + 1),
            NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("innervate", ACTION_HIGH + 5), NULL)));
    
    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
		NextAction::array(0, new NextAction("flee", 49.0f), NULL)));
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
