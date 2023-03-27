#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RaidStrategy.h"
#include "MovementActions.h"
#include "ScriptedCreature.h"
#include "RaidNaxxAction.h"
#include "GenericSpellActions.h"

using namespace ai;

float HeiganDanceMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "heigan the unclean");
    if (!boss) {
        return 1.0f;
    }
    BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    uint32 curr_phase = eventMap->GetPhaseMask();
	uint32 curr_dance = eventMap->GetNextEventTime(4);
	uint32 curr_timer = eventMap->GetTimer();
	if (curr_phase != 2 && (int32)curr_dance - curr_timer >= 3000) {
		return 1.0f;
	}
	if (dynamic_cast<HeiganDanceAction*>(action) || dynamic_cast<CurePartyMemberAction*>(action)) {
		return 1.0f;
	}
	return 0.0f;
}

void RaidNaxxGenericStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	// triggers.push_back(new TriggerNode(
	// 	"often", 
	// 	NextAction::array(0, new NextAction("try to get boss ai", ACTION_RAID), NULL)));
	
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

	// Heigan the Unclean
	triggers.push_back(new TriggerNode(
		"heigan melee", 
		NextAction::array(0, new NextAction("heigan dance melee", ACTION_RAID + 1), NULL)));

	triggers.push_back(new TriggerNode(
		"heigan ranged", 
		NextAction::array(0, new NextAction("heigan dance ranged", ACTION_RAID + 1), NULL)));
}

void RaidNaxxGenericStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
	multipliers.push_back(new HeiganDanceMultiplier(ai));
}