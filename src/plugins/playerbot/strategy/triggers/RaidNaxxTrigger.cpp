#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RaidNaxxTrigger.h"
#include "ScriptedCreature.h"

using namespace ai;

bool MutatingInjectionRemovedTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "grobbulus");
    if (!boss) {
        return false;
    }
    return HasNotAuraTrigger::IsActive() && ai->GetCurrentState() == BOT_STATE_COMBAT && ai->IsRanged(bot);
}

bool BossEventTrigger::IsActive()
{
    Unit* boss = AI_VALUE(Unit*, "boss target");
    if (!boss || boss->GetEntry() != boss_entry) {
        return false;
    }
    BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    const uint32 event_time = eventMap->GetNextEventTime(event_id);
    if (event_time != last_event_time) {
        last_event_time = event_time;
        return true;
    }
    return false;
}

bool BossPhaseTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", boss_name);
    if (!boss) {
        return false;
    }
    if (this->phase_mask == 0) {
        return true;
    }
    BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    uint8 phase_mask = eventMap->GetPhaseMask();
    // bot->Yell("phase mask detected: " + to_string(phase_mask) + " compare with " + to_string(this->phase_mask), LANG_UNIVERSAL);
    return phase_mask == this->phase_mask;
}

bool GrobbulusCloudTrigger::IsActive()
{
    Unit* boss = AI_VALUE(Unit*, "boss target");
    if (!boss || boss->GetEntry() != boss_entry) {
        return false;
    }
    if (!ai->IsMainTank(bot)) {
        return false;
    }
    // bot->Yell("has aggro on " + boss->GetName() + " : " + to_string(AI_VALUE2(bool, "has aggro", "boss target")), LANG_UNIVERSAL);
    return AI_VALUE2(bool, "has aggro", "boss target");
}

bool HeiganMeleeTrigger::IsActive()
{
    Unit* heigan = AI_VALUE2(Unit*, "find target", "heigan the unclean");
    if (!heigan) {
        return false;
    }
    return !ai->IsRanged(bot);
}

bool HeiganRangedTrigger::IsActive()
{
    Unit* heigan = AI_VALUE2(Unit*, "find target", "heigan the unclean");
    if (!heigan) {
        return false;
    }
    return ai->IsRanged(bot);
}

bool RazuviousTankTrigger::IsActive()
{
    return BossPhaseTrigger::IsActive() && ai->IsTank(bot);
}