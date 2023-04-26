#pragma once

#include "../triggers/GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(HunterNoStingsActiveTrigger, Trigger)
    END_TRIGGER()

    class HunterAspectOfTheHawkTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfTheHawkTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the hawk") {
			checkInterval = 1;
		}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive()
        {
            Unit* target = GetTarget();
            return SpellTrigger::IsActive() &&
                !ai->HasAura("aspect of the hawk", target) && !ai->HasAura("aspect of the dragonhawk", target) &&
                (!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") > 70);
        }
    };

	class HunterAspectOfTheWildTrigger : public BuffTrigger
	{
	public:
		HunterAspectOfTheWildTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the wild") {
			checkInterval = 1;
		}
	};

    class HunterAspectOfTheViperTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfTheViperTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the viper") {}
        virtual bool IsActive()
        {
            return SpellTrigger::IsActive() && !ai->HasAura(spell, GetTarget()) && 
                AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.lowMana;
        }
    };

    class HunterAspectOfThePackTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfThePackTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the pack") {}
        virtual bool IsActive() {
			return BuffTrigger::IsActive() && !ai->HasAura("aspect of the cheetah", GetTarget());
        };
    };

    BEGIN_TRIGGER(HuntersPetDeadTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetLowHealthTrigger, Trigger)
    END_TRIGGER()

    class BlackArrowTrigger : public DebuffFromBotTrigger
    {
    public:
        BlackArrowTrigger(PlayerbotAI* ai) : DebuffFromBotTrigger(ai, "black arrow") {}
    };

    class HuntersMarkTrigger : public DebuffTrigger
    {
    public:
        HuntersMarkTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "hunter's mark") {}
    };

    class FreezingTrapTrigger : public HasCcTargetTrigger
    {
    public:
        FreezingTrapTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "freezing trap") {}
    };

    class RapidFireTrigger : public BoostTrigger
    {
    public:
        RapidFireTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "rapid fire") {}
    };

    class TrueshotAuraTrigger : public BuffTrigger
    {
    public:
        TrueshotAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "trueshot aura") {}
    };

    class SerpentStingOnAttackerTrigger : public DebuffFromBotOnAttackerTrigger
    {
    public:
        SerpentStingOnAttackerTrigger(PlayerbotAI* ai) : DebuffFromBotOnAttackerTrigger(ai, "serpent sting") {}
    };
    
    class TargetRemoveEnrageTrigger : public TargetAuraDispelTrigger
    {
    public:
        TargetRemoveEnrageTrigger(PlayerbotAI* ai) : TargetAuraDispelTrigger(ai, "tranquilizing shot", DISPEL_ENRAGE) {}
    };

    class MisdirectionOnMainTankTrigger : public BuffOnMainTankTrigger
    {
    public:
        MisdirectionOnMainTankTrigger(PlayerbotAI* ai) : BuffOnMainTankTrigger(ai, "misdirection") {}
        virtual bool IsActive() {
            Unit* target = GetTarget();
            return SpellTrigger::IsActive() && !ai->HasAuraFromBot(spell, target);
        }
    };

}
