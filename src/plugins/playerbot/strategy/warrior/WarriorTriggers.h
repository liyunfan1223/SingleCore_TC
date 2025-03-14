#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{
    class BattleShoutTrigger : public BuffTrigger
    {
    public:
        BattleShoutTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "battle shout") {}
        virtual bool IsActive() {
            return BuffTrigger::IsActive() && !ai->HasAura("blessing of might", bot);
        }
    };

    BUFF_TRIGGER(CommandingShoutTrigger, "commanding shout", "commanding shout")
    // class CommandingShoutTrigger : public BuffTrigger
    // {
    // public:
    //     CommandingShoutTrigger(PlayerbotAI*)

    // };

    DEBUFF_FROM_BOT_TRIGGER(RendDebuffTrigger, "rend", "rend")
    DEBUFF_FROM_BOT_TRIGGER(DisarmDebuffTrigger, "disarm", "disarm")
    DEBUFF_TRIGGER(SunderArmorDebuffTrigger, "sunder armor", "sunder armor")

    class RendDebuffOnAttackerTrigger : public DebuffFromBotOnAttackerTrigger
    {
    public:
        RendDebuffOnAttackerTrigger(PlayerbotAI* ai) : DebuffFromBotOnAttackerTrigger(ai, "rend") {}
    };

	class RevengeAvailableTrigger : public SpellCanBeCastTrigger
	{
	public:
		RevengeAvailableTrigger(PlayerbotAI* ai) : SpellCanBeCastTrigger(ai, "revenge") {}
	};

    class BloodrageDebuffTrigger : public DebuffTrigger
    {
    public:
        BloodrageDebuffTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "bloodrage") {}
        virtual bool IsActive()
        {
            return DebuffTrigger::IsActive() &&
                AI_VALUE2(uint8, "health", "self target") >= 75 &&
                AI_VALUE2(uint8, "rage", "self target") < 20;
        }
    };

    class ShieldBashInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        ShieldBashInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "shield bash") {}
    };
	
	class PummelInterruptSpellTrigger : public InterruptSpellTrigger
	{
	public:
		PummelInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "pummel") {}
	};
	
    class VictoryRushTrigger : public HasAuraTrigger
    {
    public:
        VictoryRushTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "victory rush") {}
    };

    class SwordAndBoardTrigger : public HasAuraTrigger
    {
    public:
        SwordAndBoardTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "sword and board") {}
    };

    class ConcussionBlowTrigger : public SnareTargetTrigger
    {
    public:
        ConcussionBlowTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "concussion blow") {}
    };

    class HamstringTrigger : public SnareTargetTrigger
    {
    public:
        HamstringTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "hamstring") {}
    };

    class DeathWishTrigger : public BoostTrigger
    {
    public:
        DeathWishTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "death wish") {}
    };

	class SweepingStrikesTrigger : public BoostTrigger
    {
    public:
		SweepingStrikesTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "sweeping strikes") {}
    };

    class ShieldBashInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        ShieldBashInterruptEnemyHealerSpellTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "shield bash") {}
    };

    class SlamTrigger : public HasAuraTrigger
    {
    public:
        SlamTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "slam!") {}
    };
}
