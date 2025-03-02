#pragma once

#include "../triggers/GenericTriggers.h"

namespace ai
{
    BUFF_ON_PARTY_TRIGGER(PowerWordFortitudeOnPartyTrigger, "power word: fortitude::prayer of fortitude", "power word: fortitude on party")
    BUFF_TRIGGER(PowerWordFortitudeTrigger, "power word: fortitude", "power word: fortitude")

    BUFF_ON_PARTY_TRIGGER(DivineSpiritOnPartyTrigger, "divine spirit::prayer of spirit", "divine spirit on party")
    BUFF_TRIGGER(DivineSpiritTrigger, "divine spirit", "divine spirit")
    BUFF_TRIGGER(InnerFireTrigger, "inner fire", "inner fire")
    BUFF_TRIGGER(VampiricEmbraceTrigger, "vampiric embrace", "vampiric embrace")

    class PowerWordPainOnAttackerTrigger : public DebuffFromBotOnAttackerTrigger
    {
    public:
        PowerWordPainOnAttackerTrigger(PlayerbotAI* ai) : DebuffFromBotOnAttackerTrigger(ai, "shadow word: pain") {}
    };

    DEBUFF_FROM_BOT_TRIGGER(PowerWordPainTrigger, "shadow word: pain", "shadow word: pain")
    DEBUFF_FROM_BOT_TRIGGER(DevouringPlagueTrigger, "devouring plague", "devouring plague")
    DEBUFF_FROM_BOT_TRIGGER(VampiricTouchTrigger, "vampiric touch", "vampiric touch")

    class DispelMagicTrigger : public NeedCureTrigger
    {
    public:
        DispelMagicTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC) {}
    };

    class DispelMagicPartyMemberTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        DispelMagicPartyMemberTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC) {}
    };

    class CureDiseaseTrigger : public NeedCureTrigger
    {
    public:
        CureDiseaseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
    };

    class PartyMemberCureDiseaseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberCureDiseaseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
    };

    class ShadowformTrigger : public BuffTrigger {
    public:
        ShadowformTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "shadowform") {}
        virtual bool IsActive() { return !ai->HasAura("shadowform", bot); }
    };
}
