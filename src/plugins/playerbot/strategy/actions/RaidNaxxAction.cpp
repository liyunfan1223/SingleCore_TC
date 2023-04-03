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

bool MoveInsideAction::Execute(Event event)
{
    return MoveInside(bot->GetMapId(), x, y, bot->GetPositionZ(), distance);
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

bool RazuviousUseObedienceCrystalAction::Execute(Event event)
{
    
    if (Unit* charm = bot->GetCharm()) {
        // bot->Yell("I am charming: " + charm->GetName(), LANG_UNIVERSAL);
        Unit* target = AI_VALUE2(Unit*, "find target", "instructor razuvious");
        if (!target) {
            return false;
        }
        // if (!charm->isMoving() && charm->GetDistance2d(target) > 0.1f) {
            // bot->Yell("Need chase.", LANG_UNIVERSAL);
            // MotionMaster &mm = *(charm->GetMotionMaster());
        //     mm.Clear();
        //     mm.MovePoint(target);
        // }
        // charm->GetMotionMaster()->MovePoint(target->GetMapId(), *target);
        charm->GetMotionMaster()->MoveChase(target);
        charm->Attack(target, true);
        charm->SetFacingToObject(target);
        Aura* forceObedience = ai->GetAura("force obedience", charm);
        if (!forceObedience) {
            return false;
        }
        // charm->Say("Force Obdience Duration: " + to_string(forceObedience->GetDuration()) + 
        //     " Distance: " + to_string(charm->GetDistance(target)), LANG_UNIVERSAL);
        if (charm->GetDistance(target) <= 0.51f) {
            // taunt
            bool tauntUseful = true;
            if (forceObedience->GetDuration() <= 85000) {
                if (target->GetVictim() && ai->HasAura(29061, target->GetVictim())) {
                    tauntUseful = false;
                }
                if (forceObedience->GetDuration() <= 3000) {
                    tauntUseful = false;
                }
            }
            if (forceObedience->GetDuration() >= 89500) {
                tauntUseful = false;
            }
            if ( tauntUseful && !charm->GetSpellHistory()->HasCooldown(29060) ) {
                // shield
                if (!charm->GetSpellHistory()->HasCooldown(29061)) {
                    charm->CastSpell(charm, 29061, true);
                    charm->GetSpellHistory()->AddCooldown(29061, 0, Seconds(30));
                }
                charm->CastSpell(target, 29060, true);
                charm->GetSpellHistory()->AddCooldown(29060, 0, Seconds(20));
            }
            // strike
            if (!charm->GetSpellHistory()->HasCooldown(61696)) {
                charm->CastSpell(target, 61696, true);
                charm->GetSpellHistory()->AddCooldown(61696, 0, Seconds(4));
            }
            // // shield
            // if (target->GetVictim() == charm && !charm->GetSpellHistory()->HasCooldown(29061)) {
            //     charm->CastSpell(charm, 29061, true);
            //     charm->GetSpellHistory()->AddCooldown(29061, 0, Seconds(30));
            // }
        }
    } else {
        // bot->Yell("Let\'s use obedience crystal.", LANG_UNIVERSAL);
        list<ObjectGuid> npcs = AI_VALUE(list<ObjectGuid>, "nearest npcs");
        for (list<ObjectGuid>::iterator i = npcs.begin(); i != npcs.end(); i++)
        {
            Creature* unit = ai->GetCreature(*i);
            if (!unit) {
                continue;
            }
            if (ai->IsMainTank(bot) && unit->GetSpawnId() != 128352) {
                continue;
            }
            if (!ai->IsMainTank(bot) && unit->GetSpawnId() != 128353) {
                continue;
            }
            if (MoveTo(unit)) {
                return true;
            }
            Creature *creature = bot->GetNPCIfCanInteractWith(*i, UNIT_NPC_FLAG_SPELLCLICK);
            if (!creature)
                continue;
            creature->HandleSpellClick(bot);
            return true;
        }
        return false;
    }
}

bool HorsemanAttractAlternativelyAction::Execute(Event event)
{
    Unit* sir = AI_VALUE2(Unit*, "find target", "sir zeliek");
    Unit* lady = AI_VALUE2(Unit*, "find target", "lady blaumeux");
    if (!sir) {
        return false;
    }
    std::vector<std::pair<float, float>> position = {
        // left (sir zeliek)
        {2502.03f, -2910.90f},
        // right (lady blaumeux)
        {2484.61f, -2947.07f},
    };
    float pos_z = 241.27f;
    BossAI* boss_ai = dynamic_cast<BossAI*>(sir->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    const uint32 timer = eventMap->GetTimer();
    if (lady) {
        BossAI* lady_ai = dynamic_cast<BossAI*>(lady->GetAI());
        EventMap* ladyEventMap = lady_ai->GetEvents();
        const uint32 voidZone = ladyEventMap->GetNextEventTime(5);
        if (!voidZone) {
            voidzone_counter = 0;
        }
        if (voidZone && last_voidzone != voidZone) {
            voidzone_counter = (voidzone_counter + 1) % 8;
        }
        last_voidzone = voidZone;
    }
    int pos_to_go;
    if (!lady) {
        pos_to_go = 0;
    } else {
        // 24 - 15 - 15 - ...
        if (timer <= 9000 || ((timer - 9000) / 67500) % 2 == 0) {
            pos_to_go = 0;
        } else {
            pos_to_go = 1;
        }
        if (ai->IsRangedDpsAssistantOfIndex(bot, 0)) {
            pos_to_go = 1 - pos_to_go;
        }
    }
    // bot->Yell("pos to go: " + to_string(pos_to_go), LANG_UNIVERSAL);
    float pos_x = position[pos_to_go].first, pos_y = position[pos_to_go].second;
    if (pos_to_go == 1) {
        float offset_x;
        float offset_y;
        if (voidzone_counter < 4) {
            offset_x = voidzone_counter * (-4.5f);
            offset_y = voidzone_counter * (4.5f);
        }
        if (voidzone_counter >= 4) {
            offset_x = (7 - voidzone_counter) * (-4.5f);
            offset_y = (7 - voidzone_counter) * (4.5f);
            offset_x += 4.5f;
            offset_y += 4.5f;
        }
        pos_x += offset_x;
        pos_y += offset_y;
    }
    if (MoveTo(bot->GetMapId(), pos_x, pos_y, pos_z)) {
        return true;
    }
    Unit* attackTarget;
    if (pos_to_go == 0) {
        attackTarget = sir;
    } else {
        attackTarget = lady;
    }
    if (context->GetValue<Unit*>("current target")->Get() != attackTarget) {
        return Attack(attackTarget);
    }
    return false;
}

bool HorsemanAttactInOrderAction::Execute(Event event)
{
    Unit* lady = AI_VALUE2(Unit*, "find target", "lady blaumeux");
    if (lady) {
        if (context->GetValue<Unit*>("current target")->Get() == lady && ai->GetCurrentState() == BOT_STATE_COMBAT) {
            return false;
        }
        if (!bot->IsWithinLOSInMap(lady)) {
            return MoveNear(lady, 10.0f);
        }
        return Attack(lady);
    }
    Unit* sir = AI_VALUE2(Unit*, "find target", "sir zeliek");
    if (sir) {
        if (context->GetValue<Unit*>("current target")->Get() == sir && ai->GetCurrentState() == BOT_STATE_COMBAT) {
            return false;
        }
        if (!bot->IsWithinLOSInMap(sir)) {
            return MoveNear(sir, 10.0f);
        }
        return Attack(sir);
    }
    return false;
}

bool SapphironGroundMainTankPositionAction::Execute(Event event)
{
    return MoveTo(533, 3512.07f, -5274.06f, 137.29f);
}

bool SapphironGroundPositionAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "sapphiron");
    if (!boss) {
        return false;
    }
    BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    const uint32 flight = eventMap->GetNextEventTime(6);
    const uint32 timer = eventMap->GetTimer();
    if (timer <= 3000 || (flight && flight != last_flight)) {
        reset = true;
        reset_timer = timer;
    }
    last_flight = flight;
    if (reset) {
        // bot->Yell("Let\'s go!", LANG_UNIVERSAL);
        std::pair<float, float> center = {3517.31f, -5253.74f};
        // std::pair<float, float> center = {boss->GetPositionX(), boss->GetPositionY()};
        uint32 index = ai->GetGroupSlotIndex(bot);
        float start_angle = 1.25 * M_PI;
        float offset_angle = ai->IsRanged(bot) ? -M_PI * 0.06 * index : -M_PI * 0.3;
        float angle = start_angle + offset_angle;
        float distance = 30.0f;
        if (ai->IsRangedDps(bot)) {
            distance = 30.0f;
        } else if (ai->IsHeal(bot)) {
            distance = 20.0f;
        } else {
            distance = 10.0f;
        }
        if (MoveTo(533, center.first + cos(angle) * distance, center.second + sin(angle) * distance, 137.29f)) {
            return true;
        }
        if (timer - reset_timer >= 3000) {
            reset = false;
        }
    }
    return false;
}

bool SapphironFlightPositionAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "sapphiron");
    if (!boss) {
        return false;
    }
    BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    const uint32 explosion = eventMap->GetNextEventTime(10);
    const uint32 land = eventMap->GetNextEventTime(11);
    const uint32 timer = eventMap->GetTimer();
    if (explosion && explosion != last_explosion) {
        move_ice_bolt = true;
    }
    last_explosion = explosion;
    if (land && land > timer) {
        move_ice_bolt = false;
    }
    // bool newexplosion = explosion && explosion != last_explosion;
    if (move_ice_bolt) {
        return MoveToNearestIcebolt();
    }
    
    // before explosion
    // std::pair<float, float> center = {boss->GetPositionX(), boss->GetPositionY()};
    const uint32 icebolt = eventMap->GetNextEventTime(8);

    uint32 runBeforeIcebolt = ai->IsRanged(bot) ? 3000 : 6000;
    if ((icebolt <= timer && timer - icebolt <= 7000) || (icebolt >= timer && icebolt - timer <= runBeforeIcebolt)) {
        std::pair<float, float> center = {3517.31f, -5253.74f};
        uint32 index = ai->GetGroupSlotIndex(bot);
        float start_angle = 1.25 * M_PI;
        float offset_angle = -M_PI * 0.04 * index;
        float angle = start_angle + offset_angle;
        float distance = 45.0f;
        if (MoveTo(533, center.first + cos(angle) * distance, center.second + sin(angle) * distance, 137.29f)) {
            return true;
        }
    }
    return false;
}

bool SapphironFlightPositionAction::MoveToNearestIcebolt()
{
    Group* group = bot->GetGroup();
    if (!group) {
        return 0;
    }
    Group::MemberSlotList const& slots = group->GetMemberSlots();
    int counter = 0;
    Player* playerWithIcebolt = NULL;
    float minDistance;
    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next()) {
        Player* member = ref->GetSource();
        if (ai->HasAuraWithDuration("icebolt", member)) {
            if (!playerWithIcebolt || minDistance > bot->GetDistance(member)) {
                playerWithIcebolt = member;
                minDistance = bot->GetDistance(member);
            }
        }
    }
    if (playerWithIcebolt) {
        Unit* boss = AI_VALUE2(Unit*, "find target", "sapphiron");
        float angle = boss->GetAngle(playerWithIcebolt);
        // bot->Yell("Find icebolt and let\'s move!", LANG_UNIVERSAL);
        return MoveTo(533, playerWithIcebolt->GetPositionX() + cos(angle) * 4.0f, playerWithIcebolt->GetPositionY() + sin(angle) * 4.0f, 137.29f);
    }
    // bot->Yell("No icebolt!", LANG_UNIVERSAL);
    return false;
}

bool SapphironAvoidChillAction::Execute(Event event)
{
    Aura* aura = ai->GetAura("chill", bot);
    if (!aura) return false;
    DynamicObject* dyn_obj = aura->GetDynobjOwner();
    if (!dyn_obj) return false;
    Unit* currentTarget = AI_VALUE(Unit*, "current target");
    float angle = 0;
    
    if (currentTarget) {
        if (ai->IsRanged(bot) && bot->GetExactDist2d(currentTarget) <= 35.0f) {
            angle = bot->GetAngle(currentTarget) + M_PI;
        } else {
            angle = bot->GetAngle(currentTarget) + M_PI / 2;
        }
    } else {
        angle = bot->GetAngle(dyn_obj) - M_PI;
    }
    return MoveTo(bot->GetMapId(), bot->GetPositionX() + cos(angle) * 5.0f, bot->GetPositionY() + sin(angle) * 5.0f, bot->GetPositionZ());
}