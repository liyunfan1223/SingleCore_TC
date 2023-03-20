#pragma once
#include "../Value.h"

namespace ai
{
    class FindTargetStrategy
    {
    public:
        FindTargetStrategy(PlayerbotAI* ai)
        {
            result = NULL;
            this->ai = ai;
        }

    public:
        Unit* GetResult() { return result; }

    public:
        virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager) = 0;
        void GetPlayerCount(Unit* creature, int* tankCount, int* dpsCount);

    protected:
        Unit* result;
        PlayerbotAI* ai;

    protected:
        map<Unit*, int> tankCountCache;
        map<Unit*, int> dpsCountCache;
    };

    class TargetValue : public UnitCalculatedValue
	{
	public:
        TargetValue(PlayerbotAI* ai) : UnitCalculatedValue(ai) {}

    protected:
        Unit* FindTarget(FindTargetStrategy* strategy);
    };

    class FindBossTargetStrategy : public FindTargetStrategy
    {
    public:
        FindBossTargetStrategy(PlayerbotAI* ai) : FindTargetStrategy(ai) {}
        virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager);
    };

    class BossTargetValue : public TargetValue, public Qualified
    {
    public:
        BossTargetValue(PlayerbotAI* ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };
}
