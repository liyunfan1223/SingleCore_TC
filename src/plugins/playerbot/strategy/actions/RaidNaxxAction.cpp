#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RaidNaxxAction.h"
#include "ScriptedCreature.h"

using namespace ai;

bool TryToGetBossAIAction::Execute(Event event) {
    list<ObjectGuid> attackers = context->GetValue<list<ObjectGuid> >("attackers")->Get();
    for (list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
    {
        Unit* unit = ai->GetUnit(*i);
        if (!unit) {
            continue;
        }
        Creature *creature = unit->ToCreature();
        if (!creature) {
            continue;
        }
        UnitAI* u_ai = unit->GetAI();
        bool enabled = unit->IsAIEnabled;
        CreatureAI* c_ai = creature->AI();
        if (!c_ai) {
            continue;
        }
        BossAI* b_ai = dynamic_cast<BossAI*>(c_ai);
        if (!b_ai) {
            continue;
        }
        EventMap *e_m = b_ai->GetEvents();
        if (!e_m) {
            continue;
        }
        uint8 phase_mask = e_m->GetPhaseMask();
        uint32 bossID = b_ai->GetBossID();
        bool isDungeonBoss = creature->IsDungeonBoss();
        // bot->Yell("boss ai detected.", LANG_UNIVERSAL);
        bot->Yell("boss ai detected. phase mask: " + to_string(phase_mask) + " ai enabled: " + to_string(enabled) +
                  " boss id: " + to_string(bossID) + " name: " + unit->GetName() + " entry: " + to_string(unit->GetEntry()) +
                  " guid: " + to_string(unit->GetGUID().GetRawValue()) + " isDungeonBoss: " + to_string(isDungeonBoss), LANG_UNIVERSAL); 
        return true;
    }
    return false;
}

bool GoBehindTheBossAction::Execute(Event event)
{
    Unit* boss = AI_VALUE(Unit*, "boss target");
    if (!boss) {
        return false;
    }
    // Position* pos = boss->GetPosition();
    float orientation = boss->GetOrientation();
    float x = boss->GetPositionX();
    float y = boss->GetPositionY();
    float z = boss->GetPositionZ();
    float rx = x - cos(orientation) * distance;
    float ry = y - sin(orientation) * distance;
    bot->Yell("Boss Name: " + boss->GetName() + " Move to " + to_string(rx) + ", " + to_string(ry) + ", " + to_string(z), LANG_UNIVERSAL);
    return MoveTo(bot->GetMapId(), rx, ry, z);
}