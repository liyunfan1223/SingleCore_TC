#pragma once

namespace ai
{
    class RaidNaxxGenericStrategy : public Strategy
    {
    public:
        RaidNaxxGenericStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual string getName() { return "naxx"; }
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    
}