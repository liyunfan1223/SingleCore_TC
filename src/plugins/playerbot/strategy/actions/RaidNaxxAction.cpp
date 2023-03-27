#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RaidNaxxAction.h"
#include "ScriptedCreature.h"

using namespace ai;

bool TryToGetBossAIAction::Execute(Event event) {
    Unit* boss = AI_VALUE(Unit*, "boss target");
    if (!boss) {
        return false;
    }
    Creature* creature = boss->ToCreature();
    BossAI* b_ai = dynamic_cast<BossAI*>(boss->GetAI());
    if (!b_ai) {
        return false;
    }
    bool enabled = boss->IsAIEnabled;
    EventMap *eventMap = b_ai->GetEvents();
    uint8 phase_mask = eventMap->GetPhaseMask();
    uint32 bossID = b_ai->GetBossID();
    bool isDungeonBoss = creature->IsDungeonBoss();
    // bot->Yell("boss ai detected.", LANG_UNIVERSAL);
    uint32 next_event_time_1 = eventMap->GetNextEventTime(1);
    uint32 next_event_time_2 = eventMap->GetNextEventTime(2);
    uint32 next_event_time_3 = eventMap->GetNextEventTime(3);
    uint32 next_event_time_4 = eventMap->GetNextEventTime(4);
    uint32 next_event_time_5 = eventMap->GetNextEventTime(5);
    uint32 curr_timer = eventMap->GetTimer();
    bot->Yell("boss ai detected. phase mask: " + to_string(phase_mask) + " ai enabled: " + to_string(enabled) +
                " boss id: " + to_string(bossID) + " name: " + boss->GetName() + " entry: " + to_string(boss->GetEntry()) +
                " guid: " + to_string(boss->GetGUID().GetRawValue()) + " isDungeonBoss: " + to_string(isDungeonBoss) +
                " event1: " + to_string(next_event_time_1) + " event2: " + to_string(next_event_time_2) +
                " event3: " + to_string(next_event_time_3) + " event4: " + to_string(next_event_time_4) +
                " event5: " + to_string(next_event_time_5) + " timer: " + to_string(curr_timer), LANG_UNIVERSAL); 
    return true;
    
}

bool GoBehindTheBossAction::Execute(Event event)
{
    Unit* boss = AI_VALUE(Unit*, "boss target");
    if (!boss) {
        return false;
    }
    // Position* pos = boss->GetPosition();
    float orientation = boss->GetOrientation() + M_PI + delta_angle;
    float x = boss->GetPositionX();
    float y = boss->GetPositionY();
    float z = boss->GetPositionZ();
    float rx = x + cos(orientation) * distance;
    float ry = y + sin(orientation) * distance;
    return MoveTo(bot->GetMapId(), rx, ry, z);
}

bool MoveToPointForceAction::Execute(Event event)
{
    return MoveTo(bot->GetMapId(), x, y, bot->GetPositionZ(), true);
}

bool RotateAroundTheCenterPointAction::Execute(Event event)
{
    // uint32 nearest = FindNearestWaypoint();
    // uint32 next_point = (nearest + 1) % intervals;
    uint32 next_point = GetCurrWaypoint();
    // bot->Yell("Now Execute Rotate, call_counters: " + to_string(call_counters) + " next point: " + to_string(next_point), LANG_UNIVERSAL);
    if (MoveTo(bot->GetMapId(), waypoints[next_point].first, waypoints[next_point].second, bot->GetPositionZ())) {
        call_counters += 1;
        return true;
    }
    return false;
}

uint32 RotateAroundTheCenterPointAction::FindNearestWaypoint()
{
    float minDistance = 0;
    int ret = -1;
    for (int i = 0; i < intervals; i++) {
        float w_x = waypoints[i].first, w_y = waypoints[i].second;
        float dis = bot->GetDistance2d(w_x, w_y);
        if (ret == -1 || dis < minDistance) {
            ret = i;
            minDistance = dis;
        }
    }
    return ret;
}

uint32 RotateGrobbulusAction::GetCurrWaypoint()
{
    Unit* boss = AI_VALUE(Unit*, "boss target");
    if (!boss) {
        return false;
    }
    BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    const uint32 event_time = eventMap->GetNextEventTime(2);
    return (event_time / 15000) % intervals;
}

bool HeiganDanceAction::CalculateSafe() {
    Unit* boss = AI_VALUE2(Unit*, "find target", "heigan the unclean");
    if (!boss) {
        return false;
    }
    BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    uint32 curr_phase = eventMap->GetPhaseMask();
    uint32 curr_erupt = eventMap->GetNextEventTime(3);
    uint32 curr_dance = eventMap->GetNextEventTime(4);
    uint32 curr_dance_end = eventMap->GetNextEventTime(5);
    uint32 curr_timer = eventMap->GetTimer();
    if ((curr_phase != 2 && curr_dance - curr_timer >= 80000) || (curr_phase == 2 && curr_dance_end - curr_timer >= 36000)) {
        ResetSafe();
    } else if (curr_erupt != prev_erupt) {
        NextSafe();
    }
    prev_phase = curr_phase;
    prev_erupt = curr_erupt;
}

// bool HeiganDanceAction::MoveToCurrSafeSection() {
//     bot->Yell("Let\'s go " + to_string(curr_safe), LANG_UNIVERSAL);
//     return MoveTo(waypoints[curr_safe].first, waypoints[curr_safe].second);
// }

bool HeiganDanceMeleeAction::Execute(Event event) {
    CalculateSafe();
    if (ai->IsMainTank(bot) && !AI_VALUE2(bool, "has aggro", "boss target")) {
        return false;
    }
    // bot->Yell("Let\'s go " + to_string(curr_safe), LANG_UNIVERSAL);
    return MoveTo(bot->GetMapId(), waypoints[curr_safe].first, waypoints[curr_safe].second, bot->GetPositionZ());
}

bool HeiganDanceRangedAction::Execute(Event event) {
    CalculateSafe();
    if (prev_phase != 2) {
        // bot->Yell("Let\'s go platform", LANG_UNIVERSAL);
        return MoveTo(bot->GetMapId(), platform.first, platform.second, bot->GetPositionZ());
    }
    ai->InterruptSpell();
    // bot->Yell("Let\'s go " + to_string(curr_safe) + " " + to_string(prev_phase), LANG_UNIVERSAL);
    return MoveTo(bot->GetMapId(), waypoints[curr_safe].first, waypoints[curr_safe].second, bot->GetPositionZ());
}