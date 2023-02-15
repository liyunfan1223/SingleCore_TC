#pragma once

namespace ai
{
    class RaidNaxxStrategy : public Strategy
    {
    public:
        RaidNaxxStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual string getName() { return "naxx"; }
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}