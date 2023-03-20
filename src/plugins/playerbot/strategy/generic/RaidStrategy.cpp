#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RaidStrategy.h"

using namespace ai;

void RaidNaxxStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
		"often", 
		NextAction::array(0, new NextAction("try to get boss ai", 70.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"mutating injection", 
		NextAction::array(0, new NextAction("go behind the boss", 71.0f), NULL)));
	
}