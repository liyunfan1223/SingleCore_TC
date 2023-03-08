#pragma once

#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericWarlockNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericWarlockNonCombatStrategy(PlayerbotAI* ai);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class SummonImpStrategy : public NonCombatStrategy
    {
    public:
        SummonImpStrategy(PlayerbotAI* ai);
        virtual string getName() { return "bhealth"; }
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class SummonFelguardStrategy : public NonCombatStrategy
    {
    public:
        SummonFelguardStrategy(PlayerbotAI* ai);
        virtual string getName() { return "bdps"; }
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class SummonFelhunterStrategy : public NonCombatStrategy
    {
    public:
        SummonFelhunterStrategy(PlayerbotAI* ai);
        virtual string getName() { return "bmana"; }
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
