#pragma once

#include "GenericShamanStrategy.h"

namespace ai
{
    class TotemsShamanStrategy : public CombatStrategy
    {
    public:
        TotemsShamanStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "totems"; }
    };
}
