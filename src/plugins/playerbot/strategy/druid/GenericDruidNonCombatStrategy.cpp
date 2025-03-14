#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "GenericDruidNonCombatStrategy.h"

using namespace ai;

class GenericDruidNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericDruidNonCombatStrategyActionNodeFactory()
    {
        creators["mark of the wild"] = &mark_of_the_wild;
        creators["mark of the wild on party"] = &mark_of_the_wild_on_party;
        creators["gift of the wild on party"] = &gift_of_the_wild_on_party;
        creators["innervate"] = &innervate;
        creators["revive"] =  &revive;
        creators["regrowth_on_party"] = &regrowth_on_party;
        creators["rejuvenation on party"] = &rejuvenation_on_party;
    }
private:
    static ActionNode* mark_of_the_wild(PlayerbotAI* ai)
    {
        return new ActionNode ("mark of the wild",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
	static ActionNode* mark_of_the_wild_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("mark of the wild on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* gift_of_the_wild_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("gift of the wild on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("mark of the wild on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* innervate(PlayerbotAI* ai)
    {
        return new ActionNode ("innervate",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	static ActionNode* revive(PlayerbotAI* ai)
    {
        return new ActionNode ("revive",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* regrowth_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* rejuvenation_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

GenericDruidNonCombatStrategy::GenericDruidNonCombatStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericDruidNonCombatStrategyActionNodeFactory());
}

void GenericDruidNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    // triggers.push_back(new TriggerNode(
    //     "mark of the wild",
    //     NextAction::array(0, new NextAction("mark of the wild", 12.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "avoid aoe",
    //     NextAction::array(0, new NextAction("nothing", 111.0f), NULL)));
        
    triggers.push_back(new TriggerNode(
        "mark of the wild on party",
        NextAction::array(0, new NextAction("gift of the wild on party", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL + 7), NULL)));

	triggers.push_back(new TriggerNode(
		"party member to resurrect",
		NextAction::array(0, new NextAction("revive", ACTION_HIGH + 9), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "low mana",
    //     NextAction::array(0, new NextAction("innervate", ACTION_DISPEL + 5), NULL)));
    
    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 5),
            new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 3), 
        new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 1),
        new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL + 2), NULL)));
}

BuffHealthStrategy::BuffHealthStrategy(PlayerbotAI* ai) : Strategy(ai)
{
}

void BuffHealthStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "bear form",
        NextAction::array(0, new NextAction("dire bear form", ACTION_NORMAL), NULL)));
    
    triggers.push_back(new TriggerNode(
        "thorns",
        NextAction::array(0, new NextAction("thorns", ACTION_HIGH + 9), NULL)));
        
}