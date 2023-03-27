#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RaidStrategy.h"

using namespace ai;

void RaidNaxxGenericStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	// grobbulus
	triggers.push_back(new TriggerNode(
		"mutating injection", 
		NextAction::array(0, new NextAction("go behind the boss", ACTION_RAID + 2), NULL)));
	
	triggers.push_back(new TriggerNode(
		"mutating injection removed", 
		NextAction::array(0, new NextAction("grobbulus move center", ACTION_RAID + 1), NULL)));

	triggers.push_back(new TriggerNode(
		"grobbulus cloud", 
		NextAction::array(0, new NextAction("rotate grobbulus", ACTION_RAID + 1), NULL)));

	// 
	
}