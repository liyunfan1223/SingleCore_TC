#pragma once

#include "../Action.h"
#include "MovementActions.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class ReachTargetAction : public MovementAction
    {
    public:
        ReachTargetAction(PlayerbotAI* ai, string name, float distance, const char* target = "current target") 
        : MovementAction(ai, name), target(target)
		{
            this->distance = distance;
        }
        virtual bool Execute(Event event)
		{
			return MoveTo(AI_VALUE(Unit*, target), distance);
        }
        virtual bool isUseful()
		{
            return AI_VALUE2(float, "distance", target) > (distance + sPlayerbotAIConfig.contactDistance);
        }
        virtual string GetTargetName() { return target; }

    protected:
        float distance;
        const char* target;
    };


    class CastReachTargetSpellAction : public CastSpellAction
    {
    public:
        CastReachTargetSpellAction(PlayerbotAI* ai, string spell, float distance) : CastSpellAction(ai, spell)
		{
            this->distance = distance;
        }
		virtual bool isUseful()
		{
			return AI_VALUE2(float, "distance", "current target") > (distance + sPlayerbotAIConfig.contactDistance);
		}

    protected:
        float distance;
    };

    class ReachMeleeAction : public ReachTargetAction
	{
    public:
        ReachMeleeAction(PlayerbotAI* ai) : ReachTargetAction(ai, "reach melee", sPlayerbotAIConfig.meleeDistance) {}
    };

    class ReachSpellAction : public ReachTargetAction
	{
    public:
        ReachSpellAction(PlayerbotAI* ai, float distance = sPlayerbotAIConfig.spellDistance) : ReachTargetAction(ai, "reach spell", distance) {}
    };

    class ReachPartyMemberToHealAction : public ReachTargetAction
    {
    public:
        ReachPartyMemberToHealAction(PlayerbotAI* ai, float distance = sPlayerbotAIConfig.spellDistance) 
        : ReachTargetAction(ai, "reach party member to heal", distance, "party member to heal") {}
    };
}
