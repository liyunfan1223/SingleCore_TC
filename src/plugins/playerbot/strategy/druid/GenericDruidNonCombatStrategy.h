#pragma once

#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericDruidNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericDruidNonCombatStrategy(PlayerbotAI* ai);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class BuffHealthStrategy : public Strategy
    {
    public:
        BuffHealthStrategy(PlayerbotAI* ai);
        virtual string getName() { return "bhealth"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
