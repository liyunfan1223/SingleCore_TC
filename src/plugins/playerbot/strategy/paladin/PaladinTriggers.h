#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{
	BUFF_TRIGGER(HolyShieldTrigger, "holy shield", "holy shield")
    BUFF_TRIGGER(RighteousFuryTrigger, "righteous fury", "righteous fury")

    BUFF_TRIGGER(RetributionAuraTrigger, "retribution aura", "retribution aura")

	class CrusaderAuraTrigger : public BuffTrigger
	{
	public:
		CrusaderAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "crusader aura") {}
		virtual bool IsActive();
	};

	class SealTrigger : public BuffTrigger
	{
	public:
		SealTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "seal of justice") {}
		virtual bool IsActive();
	};

    DEBUFF_TRIGGER(JudgementOfLightTrigger, "judgement of light", "judgement of light")
    DEBUFF_TRIGGER(JudgementOfWisdomTrigger, "judgement of wisdom", "judgement of wisdom")
    DEBUFF_TRIGGER(JudgementTrigger, "judgement", "judgement")

    BUFF_ON_PARTY_TRIGGER(BlessingOnPartyTrigger, "blessing of", "blessing of kings on party")
    BUFF_TRIGGER(BlessingTrigger, "blessing of sanctuary", "blessing of sanctuary")

    class HammerOfJusticeInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        HammerOfJusticeInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "hammer of justice") {}
    };

    class HammerOfJusticeSnareTrigger : public SnareTargetTrigger
    {
    public:
        HammerOfJusticeSnareTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "hammer of justice") {}
    };

    class ArtOfWarTrigger : public HasAuraTrigger
    {
    public:
        ArtOfWarTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "the art of war") {}
    };

    class ShadowResistanceAuraTrigger : public BuffTrigger
    {
    public:
        ShadowResistanceAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "shadow resistance aura") {}
    };

    class FrostResistanceAuraTrigger : public BuffTrigger
    {
    public:
        FrostResistanceAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "frost resistance aura") {}
    };

    class FireResistanceAuraTrigger : public BuffTrigger
    {
    public:
        FireResistanceAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "fire resistance aura") {}
    };

    class DevotionAuraTrigger : public BuffTrigger
    {
    public:
        DevotionAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "devotion aura") {}
    };

    class ConcentrationAuraTrigger : public BuffTrigger
    {
    public:
        ConcentrationAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "concentration aura") {}
    };

    class CleanseCureDiseaseTrigger : public NeedCureTrigger
    {
    public:
        CleanseCureDiseaseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cleanse", DISPEL_DISEASE) {}
    };

    class CleanseCurePartyMemberDiseaseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        CleanseCurePartyMemberDiseaseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse", DISPEL_DISEASE) {}
    };

    class CleanseCurePoisonTrigger : public NeedCureTrigger
    {
    public:
        CleanseCurePoisonTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cleanse", DISPEL_POISON) {}
    };

    class CleanseCurePartyMemberPoisonTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        CleanseCurePartyMemberPoisonTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse", DISPEL_POISON) {}
    };

    class CleanseCureMagicTrigger : public NeedCureTrigger
    {
    public:
        CleanseCureMagicTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cleanse", DISPEL_MAGIC) {}
    };

    class CleanseCurePartyMemberMagicTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        CleanseCurePartyMemberMagicTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse", DISPEL_MAGIC) {}
    };

    class HammerOfJusticeEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        HammerOfJusticeEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "hammer of justice") {}
    };

    class BeaconOfLightOnMainTankTrigger : public BuffOnMainTankTrigger
    {
    public:
        BeaconOfLightOnMainTankTrigger(PlayerbotAI* ai) : BuffOnMainTankTrigger(ai, "beacon of light") {}
        virtual bool IsActive() {
            Unit* target = GetTarget();
            return SpellTrigger::IsActive() && !ai->HasAuraFromBot(spell, target);
        }
    };

    class SacredShieldOnMainTankTrigger : public BuffOnMainTankTrigger
    {
    public:
        SacredShieldOnMainTankTrigger(PlayerbotAI* ai) : BuffOnMainTankTrigger(ai, "sacred shield") {}
    };
}
