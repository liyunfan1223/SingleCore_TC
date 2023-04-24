#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarriorMultipliers.h"
#include "BerserkerWarriorStrategy.h"

using namespace ai;

class BerserkerWarriorStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    BerserkerWarriorStrategyActionNodeFactory()
    {
		creators["overpower"] = &overpower;
		creators["bloodthirst"] = &bloodthirst;
		creators["whirlwind"] = &whirlwind;
		creators["death wish"] = &death_wish;
    }
private:
    static ActionNode* overpower(PlayerbotAI* ai)
    {
        return new ActionNode ("overpower",
            /*P*/ NextAction::array(0, new NextAction("berserker stance"), NULL),
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* bloodthirst(PlayerbotAI* ai)
    {
        return new ActionNode ("bloodthirst",
            /*P*/ NextAction::array(0, new NextAction("berserker stance"), NULL),
            // /*A*/ NextAction::array(0, new NextAction("heroic strike"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
	static ActionNode* whirlwind(PlayerbotAI* ai)
	{
		return new ActionNode("whirlwind",
			/*P*/ NextAction::array(0, new NextAction("berserker stance"), NULL),
			/*A*/ NULL,
			/*C*/ NULL);
    }
    static ActionNode* death_wish(PlayerbotAI* ai)
    {
        return new ActionNode ("death wish",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("berserker rage"), NULL),
            /*C*/ NULL);
    }
};

BerserkerWarriorStrategy::BerserkerWarriorStrategy(PlayerbotAI* ai) : GenericWarriorStrategy(ai)
{
    actionNodeFactories.Add(new BerserkerWarriorStrategyActionNodeFactory());
}

NextAction** BerserkerWarriorStrategy::getDefaultActions()
{
	return NextAction::array(0, 
        new NextAction("bloodthirst", ACTION_NORMAL + 5), 
        new NextAction("whirlwind", ACTION_NORMAL + 4), 
        new NextAction("execute", ACTION_NORMAL + 3), 
        new NextAction("overpower", ACTION_NORMAL + 2), 
        new NextAction("melee", ACTION_NORMAL), 
    NULL);
}

void BerserkerWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("intercept", ACTION_NORMAL + 9), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "target critical health",
    //     NextAction::array(0, new NextAction("execute", ACTION_HIGH + 9), NULL)));

	triggers.push_back(new TriggerNode(
		"hamstring",
		NextAction::array(0, new NextAction("hamstring", ACTION_INTERRUPT), NULL)));

	triggers.push_back(new TriggerNode(
		"victory rush",
		NextAction::array(0, new NextAction("victory rush", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "death wish",
        NextAction::array(0, new NextAction("death wish", ACTION_HIGH + 2), NULL)));
    
    triggers.push_back(new TriggerNode(
        "slam",
        NextAction::array(0, new NextAction("slam", ACTION_HIGH + 2), NULL)));
    
    triggers.push_back(new TriggerNode(
        "light aoe",
		NextAction::array(0, new NextAction("cleave", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium rage available",
        NextAction::array(0, new NextAction("heroic strike", ACTION_HIGH + 2), NULL)));
}