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
        creators["innervate"] = &innervate;
        creators["revive"] =  &revive;
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
    static ActionNode* innervate(PlayerbotAI* ai)
    {
        return new ActionNode ("innervate",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drink"), NULL),
            /*C*/ NULL);
    }
	static ActionNode* revive(PlayerbotAI* ai)
    {
        return new ActionNode ("revive",
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

    // sLog->outMessage("playerbot", LOG_LEVEL_INFO, "InitTriggers size: %d", triggers.size());
    // TEST
    // triggers.push_back(new TriggerNode(
    //     "bear form",
    //     NextAction::array(0, new NextAction("natures swiftness", 99.0f), NULL)));
    
    // triggers.push_back(new TriggerNode(
    //     "bear form",
    //     NextAction::array(0, new NextAction("rejuvenation on party", 98.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "bear form",
    //     NextAction::array(0, new NextAction("swiftmend on party", 97.0f), NULL)));
    // triggers.push_back(new TriggerNode(
    //     "bear form",
    //     NextAction::array(0, new NextAction("nourish on party", 97.0f), NULL)));
    // TEST END

    triggers.push_back(new TriggerNode(
        "mark of the wild",
        NextAction::array(0, new NextAction("mark of the wild", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mark of the wild on party",
        NextAction::array(0, new NextAction("mark of the wild on party", 11.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "tree of life",
    //     NextAction::array(0, new NextAction("tree of life", ACTION_NORMAL + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", ACTION_EMERGENCY + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_EMERGENCY + 8), NULL)));

	triggers.push_back(new TriggerNode(
		"party member to resurrect",
		NextAction::array(0, new NextAction("revive", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("innervate", ACTION_EMERGENCY + 5), NULL)));
    
    // triggers.push_back(new TriggerNode(
    //     "party member critical health",
    //     NextAction::array(0, new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 5), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member critical health",
    //     NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 6), NULL)));
        
    // triggers.push_back(new TriggerNode(
    //     "party member low health",
    //     NextAction::array(0, new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 3), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member low health",
    //     NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 4), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member medium health",
    //     NextAction::array(0, new NextAction("rejuvenation on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member medium health",
    //     NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 2), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "party member almost full health",
    //     NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL + 2), NULL)));
}
