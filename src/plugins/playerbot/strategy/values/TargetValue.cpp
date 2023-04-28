#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TargetValue.h"
#include "ScriptedCreature.h"

using namespace ai;

Unit* TargetValue::FindTarget(FindTargetStrategy* strategy)
{
    list<ObjectGuid> attackers = ai->GetAiObjectContext()->GetValue<list<ObjectGuid> >("attackers")->Get();
    for (list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
    {
        Unit* unit = ai->GetUnit(*i);
        if (!unit)
            continue;

        ThreatManager &threatManager = unit->getThreatManager();
        strategy->CheckAttacker(unit, &threatManager);
    }

    return strategy->GetResult();
}

void FindTargetStrategy::GetPlayerCount(Unit* creature, int* tankCount, int* dpsCount)
{
    Player* bot = ai->GetBot();
    if (tankCountCache.find(creature) != tankCountCache.end())
    {
        *tankCount = tankCountCache[creature];
        *dpsCount = dpsCountCache[creature];
        return;
    }

    *tankCount = 0;
    *dpsCount = 0;

    for (HostileReference *ref = creature->getHostileRefManager().getFirst(); ref; ref = ref->next())
    {
        ThreatManager *threatManager = ref->GetSource();
        Unit *attacker = threatManager->GetOwner();
        Unit *victim = attacker->GetVictim();
        Player *player = dynamic_cast<Player*>(victim);

        if (!player)
            continue;

        if (ai->IsTank(player))
            (*tankCount)++;
        else
            (*dpsCount)++;
    }

    tankCountCache[creature] = *tankCount;
    dpsCountCache[creature] = *dpsCount;
}


void FindBossTargetStrategy::CheckAttacker(Unit* attacker, ThreatManager* threatManager)
{
    UnitAI* unitAI = attacker->GetAI();
    BossAI* bossAI = dynamic_cast<BossAI*>(unitAI);
    if (bossAI) {
        result = attacker;
    }
}

Unit* BossTargetValue::Calculate()
{
    FindBossTargetStrategy strategy(ai);
    return FindTarget(&strategy);
}

Unit* FindTargetValue::Calculate()
{
    if (qualifier == "") {
        return nullptr;
    }
    if (!bot->GetGroup()) {
        return nullptr;
    }
    for (GroupReference *gref = bot->GetGroup()->GetFirstMember(); gref; gref = gref->next()) {
        Player* member = gref->GetSource();
        if (!member) {
            continue;
        }
        HostileReference *ref = member->getHostileRefManager().getFirst();
        while (ref)
        {
            ThreatManager *threatManager = ref->GetSource();
            Unit *unit = threatManager->GetOwner();
            assert(unit);
            wstring wnamepart;
            Utf8toWStr(unit->GetName(), wnamepart);
            wstrToLower(wnamepart);
            if (!qualifier.empty() && qualifier.length() == wnamepart.length() && Utf8FitTo(qualifier, wnamepart)) {
                return unit;
            }
            ref = ref->next();
        }
    }
    return nullptr;
}