#pragma once

#include "../Strategy.h"
#include "../generic/MeleeCombatStrategy.h"

namespace ai
{
    class AiObjectContext;

    class GenericWarriorStrategy : public MeleeCombatStrategy
    {
    public:
        GenericWarriorStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "warrior"; }
    };

    class WarriorBuffHealthStrategy : public Strategy
    {
    public:
        WarriorBuffHealthStrategy(PlayerbotAI* ai);
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "bhealth"; }
    };

    class WarriorBuffDpsStrategy : public Strategy
    {
    public:
        WarriorBuffDpsStrategy(PlayerbotAI* ai);
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "bdps"; }
    };
}
