#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RaidNaxxTrigger.h"
#include "ScriptedCreature.h"

using namespace ai;

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