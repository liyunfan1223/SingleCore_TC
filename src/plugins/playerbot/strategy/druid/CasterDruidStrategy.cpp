#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "CasterDruidStrategy.h"
#include "FeralDruidStrategy.h"

using namespace ai;

class CasterDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    CasterDruidStrategyActionNodeFactory()
    {
        creators["faerie fire"] = &faerie_fire;
        creators["hibernate"] = &hibernate;
        creators["entangling roots"] = &entangling_roots;
        creators["entangling roots on cc"] = &entangling_roots_on_cc;
        creators["wrath"] = &wrath;
        creators["starfall"] = &starfall;
        creators["insect swarm"] = &insect_swarm;
        creators["moonfire"] = &moonfire;
        creators["starfire"] = &starfire;
        creators["nature's grasp"] = &natures_grasp;
    }
private:
    static ActionNode* faerie_fire(PlayerbotAI* ai)
    {
        return new ActionNode ("faerie fire",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* hibernate(PlayerbotAI* ai)
    {
        return new ActionNode ("hibernate",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("entangling roots"), NULL),
            /*C*/ NextAction::array(0, new NextAction("flee", 49.0f), NULL));
    }
    static ActionNode* entangling_roots(PlayerbotAI* ai)
    {
        return new ActionNode ("entangling roots",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("flee", 49.0f), NULL));
    }
    static ActionNode* entangling_roots_on_cc(PlayerbotAI* ai)
    {
        return new ActionNode ("entangling roots on cc",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* wrath(PlayerbotAI* ai)
    {
        return new ActionNode ("wrath",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* starfall(PlayerbotAI* ai)
    {
        return new ActionNode ("starfall",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            // /*A*/ NextAction::array(0, new NextAction("hurricane"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* insect_swarm(PlayerbotAI* ai)
    {
        return new ActionNode ("insect swarm",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* moonfire(PlayerbotAI* ai)
    {
        return new ActionNode ("moonfire",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* starfire(PlayerbotAI* ai)
    {
        return new ActionNode ("starfire",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* natures_grasp(PlayerbotAI* ai)
    {
        return new ActionNode ("nature's grasp",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

CasterDruidStrategy::CasterDruidStrategy(PlayerbotAI* ai) : GenericDruidStrategy(ai)
{
    actionNodeFactories.Add(new CasterDruidStrategyActionNodeFactory());
    actionNodeFactories.Add(new ShapeshiftDruidStrategyActionNodeFactory());
}

NextAction** CasterDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, 
        new NextAction("starfall", ACTION_NORMAL + 2),
        new NextAction("wrath", ACTION_NORMAL + 1), 
        new NextAction("starfire", ACTION_NORMAL), 
        NULL);
}

void CasterDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL + 7), NULL)));
    
    triggers.push_back(new TriggerNode(
        "party member remove curse",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL + 7), NULL)));
        
    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE), NULL)));

	triggers.push_back(new TriggerNode(
		"moonfire",
		NextAction::array(0, new NextAction("moonfire", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
		"insect swarm",
		NextAction::array(0, new NextAction("insect swarm", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "eclipse (solar)",
        NextAction::array(0, new NextAction("wrath", ACTION_NORMAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "eclipse (lunar)",
        NextAction::array(0, new NextAction("starfire", ACTION_NORMAL + 6), NULL)));

	// triggers.push_back(new TriggerNode(
	// 	"nature's grasp",
	// 	NextAction::array(0, new NextAction("nature's grasp", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
        NextAction::array(0, new NextAction("innervate", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
		NextAction::array(0, new NextAction("flee", 49.0f), NULL)));
}

void CasterDruidAoeStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	// triggers.push_back(new TriggerNode(
	// 	"medium aoe",
	// 	NextAction::array(0, new NextAction("starfall", ACTION_HIGH + 1), NULL)));
	
	triggers.push_back(new TriggerNode(
		"high aoe",
		NextAction::array(0, new NextAction("hurricane", ACTION_HIGH + 1), NULL)));
	
    triggers.push_back(new TriggerNode(
		"light aoe",
        NextAction::array(0,
            new NextAction("starfall", ACTION_NORMAL + 4),
		    new NextAction("insect swarm on attacker", ACTION_NORMAL + 3), 
            new NextAction("moonfire on attacker", ACTION_NORMAL + 2),
            NULL)));
	

	triggers.push_back(new TriggerNode(
		"low health",
		NextAction::array(0, new NextAction("barkskin", ACTION_HIGH + 1), NULL)));

}

void CasterDruidDebuffStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "faerie fire",
        NextAction::array(0, new NextAction("faerie fire", ACTION_NORMAL + 1), NULL)));
}
