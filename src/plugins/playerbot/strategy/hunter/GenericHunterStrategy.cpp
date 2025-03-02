#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GenericHunterStrategy.h"
#include "HunterAiObjectContext.h"

using namespace ai;

class GenericHunterStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericHunterStrategyActionNodeFactory()
    {
        creators["rapid fire"] = &rapid_fire;
        creators["boost"] = &rapid_fire;
        creators["aspect of the pack"] = &aspect_of_the_pack;
        creators["feign death"] = &feign_death;
    }
private:
    static ActionNode* rapid_fire(PlayerbotAI* ai)
    {
        return new ActionNode ("rapid fire",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("readiness"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* aspect_of_the_pack(PlayerbotAI* ai)
    {
        return new ActionNode ("aspect of the pack",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("aspect of the cheetah"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* feign_death(PlayerbotAI* ai)
    {
        return new ActionNode ("feign death",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flee"), NULL),
            /*C*/ NULL);
    }
};

GenericHunterStrategy::GenericHunterStrategy(PlayerbotAI* ai) : RangedCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericHunterStrategyActionNodeFactory());
}

void GenericHunterStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    RangedCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "tranquilizing shot",
        NextAction::array(0, new NextAction("tranquilizing shot", 61.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for shoot",
        NextAction::array(0, new NextAction("flee", 49.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy is close",
        NextAction::array(0, new NextAction("wing clip", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("feign death", 52.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hunters pet low health",
        NextAction::array(0, new NextAction("mend pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "rapid fire",
        NextAction::array(0, new NextAction("rapid fire", 55.0f), NULL)));

    // 	triggers.push_back(new TriggerNode(
	// 	"aspect of the hawk", 
	// 	NextAction::array(0, new NextAction("aspect of the dragonhawk", 91.0f), NULL)));

    // triggers.push_back(new TriggerNode(
	// 	"aspect of the hawk", 
	// 	NextAction::array(0, new NextAction("aspect of the hawk", 90.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "aspect of the viper",
        NextAction::array(0, new NextAction("aspect of the viper", 20.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        "misdirection on main tank",
        NextAction::array(0, new NextAction("misdirection on main tank", ACTION_HIGH + 7), NULL)));

}
