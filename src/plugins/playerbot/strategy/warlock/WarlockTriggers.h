#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{
	class DemonArmorTrigger : public BuffTrigger
	{
	public:
		DemonArmorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "demon armor") {}
		virtual bool IsActive();
	};

    class SpellstoneTrigger : public BuffTrigger
    {
    public:
        SpellstoneTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "spellstone") {}
        virtual bool IsActive();
    };

    DEBUFF_FROM_BOT_TRIGGER(CurseOfAgonyTrigger, "curse of agony", "curse of agony");
    DEBUFF_FROM_BOT_TRIGGER(CorruptionTrigger, "corruption", "corruption");

    class HauntTrigger : public DebuffFromBotTrigger
    {
    public:
        HauntTrigger(PlayerbotAI* ai) : DebuffFromBotTrigger(ai, "haunt", 1, 0) {}

    };

    class CorruptionOnAttackerTrigger : public DebuffFromBotOnAttackerTrigger
    {
    public:
        CorruptionOnAttackerTrigger(PlayerbotAI* ai) : DebuffFromBotOnAttackerTrigger(ai, "corruption") {}
    };

    // DEBUFF_TRIGGER(ImmolateTrigger, "immolate", "immolate");

    class ImmolateTrigger : public SpellTrigger
    {
    public:
        ImmolateTrigger(PlayerbotAI* ai) : SpellTrigger(ai, "immolate") {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive()
        {
            Unit* target = GetTarget();
            return SpellTrigger::IsActive() &&
                !ai->HasAuraFromBot("immolate", target) && !ai->HasAuraFromBot("unstable affliction", target) &&
                (!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana);
        }
    };

    class UnstableAfflictionTrigger : public DebuffFromBotTrigger // SpellTrigger
    {
    public:
        UnstableAfflictionTrigger(PlayerbotAI* ai) : DebuffFromBotTrigger(ai, "unstable affliction") {}
        // virtual string GetTargetName() { return "current target"; }
        // virtual bool IsActive()
        // {
        //     Unit* target = GetTarget();
        //     return SpellTrigger::IsActive() &&
        //         !ai->HasAura("unstable affliction", target) &&
        //         (!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana);
        // }
    };
    class ShadowTranceTrigger : public HasAuraTrigger
    {
    public:
        ShadowTranceTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "shadow trance") {}
    };

    class BacklashTrigger : public HasAuraTrigger
    {
    public:
        BacklashTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "backlash") {}
    };

    class BanishTrigger : public HasCcTargetTrigger
    {
    public:
        BanishTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "banish") {}
    };

    class WarlockConjuredItemTrigger : public ItemCountTrigger
    {
    public:
        WarlockConjuredItemTrigger(PlayerbotAI* ai, string item) : ItemCountTrigger(ai, item, 1) {}

        virtual bool IsActive() { return ItemCountTrigger::IsActive() && AI_VALUE2(uint8, "item count", "soul shard") > 0; }
    };

    class HasSpellstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasSpellstoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "spellstone") {}
    };

    class HasFirestoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasFirestoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "firestone") {}
    };

    class HasHealthstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasHealthstoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "healthstone") {}
    };

    class FearTrigger : public HasCcTargetTrigger
    {
    public:
        FearTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "fear") {}
    };

}
