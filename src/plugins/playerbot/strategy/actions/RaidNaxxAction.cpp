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
        return MoveTo(bot->GetMapId(), platform.first, platform.second, bot->GetPositionZ());
    }
    ai->InterruptSpell();
    return MoveTo(bot->GetMapId(), waypoints[curr_safe].first, waypoints[curr_safe].second, bot->GetPositionZ());
}

bool ThaddiusAttackNearestPetAction::isUseful()
{
    Unit* feugen = AI_VALUE2(Unit*, "find target", "feugen");
    Unit* stalagg = AI_VALUE2(Unit*, "find target", "stalagg");
    if (!feugen || !stalagg) {
        return false;
    }
    Unit* result = feugen;
    if (stalagg && (!result || (bot->GetDistance2d(result) > bot->GetDistance2d(stalagg)))) {
        result = stalagg;
    }
    if (AI_VALUE(Unit*, "current target") == result) {
        return false;
    }
    return true;
}

bool ThaddiusAttackNearestPetAction::Execute(Event event) {
    Unit* feugen = AI_VALUE2(Unit*, "find target", "feugen");
    Unit* stalagg = AI_VALUE2(Unit*, "find target", "stalagg");
    Unit* result = feugen;
    if (stalagg && (!result || (bot->GetDistance2d(result) > bot->GetDistance2d(stalagg)))) {
        result = stalagg;
    }
    if (result) {
        // bot->Yell("Goona attack " + result->GetName(), LANG_UNIVERSAL);
    }
    return Attack(result);
}

bool ThaddiusMeleeToPlaceAction::isUseful()
{
    if (ai->IsTank(bot)) {
        Unit* target = AI_VALUE(Unit*, "current target");
        return target && target->GetVictim() == bot;
    } else {
        return !ai->IsRanged(bot);
    }
}

bool ThaddiusMeleeToPlaceAction::Execute(Event event)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    Unit* feugen = AI_VALUE2(Unit*, "find target", "feugen");
    Unit* stalagg = AI_VALUE2(Unit*, "find target", "stalagg");
    // float high_lx = 3455.14f, high_ly = -2927.48f;
    // float high_rx = 3515.00f, high_ry = -2983.09f;
    float high_lx = 3436.14f, high_ly = -2919.98f;
    float high_rx = 3522.94f, high_ry = -3002.60f;
    float high_z = 312.61f;
    if (target == feugen) {
        return MoveTo(bot->GetMapId(), high_rx, high_ry, high_z);
    } else if (target == stalagg) {
        return MoveTo(bot->GetMapId(), high_lx, high_ly, high_z);
    }
    return false;
}

bool ThaddiusRangedToPlaceAction::isUseful()
{
    return ai->IsRanged(bot);
}

bool ThaddiusRangedToPlaceAction::Execute(Event event)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    Unit* feugen = AI_VALUE2(Unit*, "find target", "feugen");
    Unit* stalagg = AI_VALUE2(Unit*, "find target", "stalagg");
    float high_lx = 3441.01f, high_ly = -2942.04f;
    float high_rx = 3500.45f, high_ry = -2997.92f;
    float high_z = 312.61f;
    if (target == feugen) {
        return MoveTo(bot->GetMapId(), high_rx, high_ry, high_z);
    } else if (target == stalagg) {
        return MoveTo(bot->GetMapId(), high_lx, high_ly, high_z);
    }
    return false;
}

bool ThaddiusMoveToPlatformAction::isUseful()
{
    // float high_z = 312.0f;
    // if (bot->GetPositionZ() < (high_z - 3.0f)) {
    //     return false;
    // }
    return true;
}

bool ThaddiusMoveToPlatformAction::Execute(Event event) {
    std::vector<std::pair<float, float>> position = {
        // high left
        {3462.99f, -2918.90f},
        // high right
        {3520.65f, -2976.51f},
        // low left
        {3471.36f, -2910.65f},
        // low right
        {3528.80f, -2967.04f},
        // center
        {3512.19f, -2928.58f},
    };
    // float high_lx = 3462.99f, high_ly = -2918.90f;
    // float high_rx = 3520.65f, high_ly = -2976.51f;
    // float low_lx = 3471.36f, low_ly = -2910.65f;
    // float low_rx = 3528.80f, low_ry = -2967.04f;
    float high_z = 312.00f, low_z = 304.02f;
    bool is_left = bot->GetDistance2d(position[0].first, position[0].second) < bot->GetDistance2d(position[1].first, position[1].second);
    if (bot->GetPositionZ() >= (high_z - 3.0f)) {
        if (is_left) {
            if (!MoveTo(bot->GetMapId(), position[0].first, position[0].second, high_z)) {
                bot->TeleportTo(bot->GetMapId(), position[2].first, position[2].second, low_z, bot->GetOrientation());
            }
        } else {
            if (!MoveTo(bot->GetMapId(), position[1].first, position[1].second, high_z)) {
                bot->TeleportTo(bot->GetMapId(), position[3].first, position[3].second, low_z, bot->GetOrientation());
            }
        }
    } else {
        return MoveTo(bot->GetMapId(), position[4].first, position[4].second, low_z);
    }
    return true;
}

bool ThaddiusMovePolarityAction::isUseful() {
    return !ai->IsMainTank(bot) || AI_VALUE2(bool, "has aggro", "current target");
}

bool ThaddiusMovePolarityAction::Execute(Event event) {
    std::vector<std::pair<float, float>> position = {
        // left melee
        {3508.29f, -2920.12f},
        // left ranged
        {3501.72f, -2913.36f},
        // right melee
        {3519.74f, -2931.69f},
        // right ranged
        {3524.32f, -2936.26f},
        // center melee
        {3512.19f, -2928.58f},
        // center ranged
        {3504.68f, -2936.68f},
    };
    uint32 idx;
    if (ai->HasAuraWithDuration("negative charge", bot)) {
        idx = 0;
    } else if (ai->HasAuraWithDuration("positive charge", bot)) {
        idx = 1;
    } else {
        idx = 2;
    }
    idx = idx * 2 + ai->IsRanged(bot);
    return MoveTo(bot->GetMapId(), position[idx].first, position[idx].second, bot->GetPositionZ());
}