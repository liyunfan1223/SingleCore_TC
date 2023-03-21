#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RaidStrategy.h"

using namespace ai;

void RaidNaxxGenericStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    // triggers.push_back(new TriggerNode(
	// 	"often", 
	// 	NextAction::array(0, new NextAction("try to get boss ai", 70.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"mutating injection", 
		NextAction::array(0, new NextAction("go behind the boss", 52.0f), NULL)));
	
	triggers.push_back(new TriggerNode(
		"mutating injection removed", 
		NextAction::array(0, new NextAction("grobbulus move center", 51.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"grobbulus cloud", 
		NextAction::array(0, new NextAction("rotate grobbulus", 51.0f), NULL)));
}