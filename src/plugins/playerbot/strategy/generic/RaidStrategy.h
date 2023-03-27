#pragma once

namespace ai
{   
    class HeiganDanceMultiplier : public Multiplier
    {
    public:
        HeiganDanceMultiplier(PlayerbotAI* ai) : Multiplier(ai, "helgan dance") {}

    public:
        virtual float GetValue(Action* action);
    };

    class RaidNaxxGenericStrategy : public Strategy
    {
    public:
        RaidNaxxGenericStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual string getName() { return "naxx"; }
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
    };

    
}