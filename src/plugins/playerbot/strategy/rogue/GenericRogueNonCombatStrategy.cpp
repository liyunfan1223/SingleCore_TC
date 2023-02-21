#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueTriggers.h"
#include "RogueMultipliers.h"
#include "GenericRogueNonCombatStrategy.h"
#include "RogueActions.h"

using namespace ai;

class GenericRogueNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
	GenericRogueNonCombatStrategyActionNodeFactory()
	{
	
	}
	
};


GenericRogueNonCombatStrategy::GenericRogueNonCombatStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
	actionNodeFactories.Add(new GenericRogueNonCombatStrategyActionNodeFactory());
}

void GenericRogueNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);
	
	triggers.push_back(new TriggerNode(
		"in battleground without flag",
		NextAction::array(0, new NextAction("stealth", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"main hand weapon no enchant",
		NextAction::array(0, new NextAction("use instant poison", 20.0f), NULL)));
	
	triggers.push_back(new TriggerNode(
		"off hand weapon no enchant",
		NextAction::array(0, new NextAction("use deadly poison", 19.0f), NULL)));
}