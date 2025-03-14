#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{

    class KickInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        KickInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "kick") {}
    };

    class SliceAndDiceTrigger : public BuffTrigger
    {
    public:
        SliceAndDiceTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "slice and dice") {}
    };

    class RuptureTrigger : public DebuffFromBotTrigger
    {
    public:
        RuptureTrigger(PlayerbotAI* ai) : DebuffFromBotTrigger(ai, "rupture") {}
    };

    class ExposeArmorTrigger : public DebuffTrigger
    {
    public:
        ExposeArmorTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "expose armor") {}
        virtual bool IsActive();
    };

    class KickInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        KickInterruptEnemyHealerSpellTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "kick") {}
    };

	/*class StealthTrigger : public BuffTrigger
	{
	public:
		StealthTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "stealth") {}
		virtual bool IsActive() { return !ai->HasAura("stealth", bot); }
	};*/

    class MainHandWeaponNoEnchantTrigger : public BuffTrigger
    {
    public:
        MainHandWeaponNoEnchantTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "main hand", 1) {}
        virtual bool IsActive();
    };

    class OffHandWeaponNoEnchantTrigger : public BuffTrigger
    {
    public:
        OffHandWeaponNoEnchantTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "off hand", 1) {}
        virtual bool IsActive();
    };

    class TricksOfTheTradeOnMainTankTrigger : public BuffOnMainTankTrigger
    {
    public:
        TricksOfTheTradeOnMainTankTrigger(PlayerbotAI* ai) : BuffOnMainTankTrigger(ai, "tricks of the trade") {}
        virtual bool IsActive() {
            Unit* target = GetTarget();
            return SpellTrigger::IsActive() && !ai->HasAuraFromBot(spell, target);
        }
    };
}
