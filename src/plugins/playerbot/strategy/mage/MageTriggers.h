#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{
    BUFF_ON_PARTY_TRIGGER(ArcaneIntellectOnPartyTrigger, "arcane intellect::arcane brilliance", "arcane intellect on party")
    BUFF_TRIGGER(ArcaneIntellectTrigger, "arcane intellect", "arcane intellect")

    class MageArmorTrigger : public BuffTrigger {
    public:
        MageArmorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "mage armor") {}
        virtual bool IsActive();
    };

    class LivingBombTrigger : public DebuffFromBotTrigger {
    public:
        LivingBombTrigger(PlayerbotAI* ai) : DebuffFromBotTrigger(ai, "living bomb") {}
	};

    class FireballTrigger : public DebuffFromBotTrigger {
    public:
        FireballTrigger(PlayerbotAI* ai) : DebuffFromBotTrigger(ai, "fireball") {}
	};

    class PyroblastTrigger : public DebuffFromBotTrigger {
    public:
        PyroblastTrigger(PlayerbotAI* ai) : DebuffFromBotTrigger(ai, "pyroblast") {}
    };

    class HotStreakTrigger : public HasAuraTrigger {
    public:
        HotStreakTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "hot streak") {}
    };

    class MissileBarrageTrigger : public HasAuraTrigger {
    public:
        MissileBarrageTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "missile barrage") {}
    };

    class ArcaneBlastTrigger : public BuffTrigger {
    public:
        ArcaneBlastTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "arcane blast") {}
    };
    
    class ArcaneBlastStackTrigger : public HasAuraStackTrigger {
    public:
        ArcaneBlastStackTrigger(PlayerbotAI* ai) : HasAuraStackTrigger(ai, "arcane blast", 3, 1) {}
    };

    class CounterspellInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        CounterspellInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "counterspell") {}
    };

    class CombustionTrigger : public BoostTrigger
    {
    public:
        CombustionTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "combustion") {}
    };

    class IcyVeinsTrigger : public BoostTrigger
    {
    public:
        IcyVeinsTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "icy veins") {}
    };

    class PolymorphTrigger : public HasCcTargetTrigger
    {
    public:
        PolymorphTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "polymorph") {}
    };

    class RemoveCurseTrigger : public NeedCureTrigger
    {
    public:
        RemoveCurseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "remove curse", DISPEL_CURSE) {}
    };

    class PartyMemberRemoveCurseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberRemoveCurseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "remove curse", DISPEL_CURSE) {}
    };

    class SpellstealTrigger : public TargetAuraDispelTrigger
    {
    public:
        SpellstealTrigger(PlayerbotAI* ai) : TargetAuraDispelTrigger(ai, "spellsteal", DISPEL_MAGIC) {}
    };

    class CounterspellEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        CounterspellEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "counterspell") {}
    };
}
