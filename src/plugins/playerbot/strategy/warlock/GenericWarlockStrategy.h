#pragma once

#include "../Strategy.h"
#include "../generic/RangedCombatStrategy.h"

namespace ai
{
    class GenericWarlockStrategy : public RangedCombatStrategy
    {
    public:
        GenericWarlockStrategy(PlayerbotAI* ai);
        virtual string getName() { return "warlock"; }
        virtual int GetType() { return RangedCombatStrategy::GetType() | STRATEGY_TYPE_DPS; }
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** getDefaultActions();
    };
}
