#pragma once

namespace ai
{
    class AvoidAOEStrategy : public Strategy
    {
    public:
        AvoidAOEStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "avoid aoe"; };
    };

}
