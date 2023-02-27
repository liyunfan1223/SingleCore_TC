#pragma once
#include "../Value.h"

namespace ai
{
    class AttackerWithoutAuraTargetValue : public UnitCalculatedValue, public Qualified
	{
	public:
        AttackerWithoutAuraTargetValue(PlayerbotAI* ai) :
            UnitCalculatedValue(ai, "attacker without aura") {}

    protected:
        virtual Unit* Calculate();
	};

    class AttackerWithoutAuraFromBotTargetValue : public UnitCalculatedValue, public Qualified
	{
	public:
        AttackerWithoutAuraFromBotTargetValue(PlayerbotAI* ai) :
            UnitCalculatedValue(ai, "attacker without aura from bot") {}

    protected:
        virtual Unit* Calculate();
	};
}
