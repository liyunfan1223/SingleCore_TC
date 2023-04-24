#pragma once

#include "GenericWarriorStrategy.h"

namespace ai
{
    class BerserkerWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        BerserkerWarriorStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "melee"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
    };

}
