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

    class LoathebGenericMultiplier : public Multiplier
    {
    public:
        LoathebGenericMultiplier(PlayerbotAI* ai) : Multiplier(ai, "loatheb generic") {}

    public:
        virtual float GetValue(Action* action);
    };

    class ThaddiusGenericMultiplier : public Multiplier
    {
    public:
        ThaddiusGenericMultiplier(PlayerbotAI* ai) : Multiplier(ai, "thaddius generic") {}

    public:
        virtual float GetValue(Action* action);
    };

    class SapphironGenericMultiplier : public Multiplier
    {
    public:
        SapphironGenericMultiplier(PlayerbotAI* ai) : Multiplier(ai, "sapphiron generic") {}

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