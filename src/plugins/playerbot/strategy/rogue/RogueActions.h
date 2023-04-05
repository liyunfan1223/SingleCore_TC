#pragma once

#include "../actions/GenericActions.h"
#include "RogueComboActions.h"
#include "RogueOpeningActions.h"
#include "RogueFinishingActions.h"
#include "UseItemAction.h"

namespace ai
{
	class CastEvasionAction : public CastBuffSpellAction
	{
	public:
		CastEvasionAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "evasion") {}
	};

	class CastSprintAction : public CastBuffSpellAction
	{
	public:
		CastSprintAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "sprint") {}
	};

	class CastKickAction : public CastSpellAction
	{
	public:
		CastKickAction(PlayerbotAI* ai) : CastSpellAction(ai, "kick") {}
	};
	class CastStealthAction : public CastSpellAction
	{
	public:
		CastStealthAction(PlayerbotAI* ai) : CastSpellAction(ai, "stealth") {}
		virtual string GetTargetName() { return "self target"; }
	};
	class CastCancelStealthAction : public Action
	{
	public:
		CastCancelStealthAction(PlayerbotAI* ai) : Action(ai, "cancel stealth") {}
		virtual bool isUseful();
		virtual bool Execute(Event event);
	};

	class CastFeintAction : public CastBuffSpellAction
	{
	public:
		CastFeintAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "feint") {}
	};

	class CastDismantleAction : public CastSpellAction
	{
	public:
		CastDismantleAction(PlayerbotAI* ai) : CastSpellAction(ai, "dismantle") {}
	};

	class CastDistractAction : public CastSpellAction
	{
	public:
		CastDistractAction(PlayerbotAI* ai) : CastSpellAction(ai, "distract") {}
	};

	class CastVanishAction : public CastBuffSpellAction
	{
	public:
		CastVanishAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "vanish") {}
	};

	class CastBlindAction : public CastDebuffSpellAction
	{
	public:
		CastBlindAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "blind") {}
	};


	class CastBladeFlurryAction : public CastBuffSpellAction
	{
	public:
		CastBladeFlurryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blade flurry") {}
	};

	class CastAdrenalineRushAction : public CastBuffSpellAction
	{
	public:
		CastAdrenalineRushAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "adrenaline rush") {}
	};

	class CastKillingSpreeAction : public CastBuffSpellAction
	{
	public:
		CastKillingSpreeAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "killing spree") {}
	};

    class CastKickOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastKickOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "kick") {}
    };

	class UseDeadlyPoisonAction : public UseItemAction
	{
	public:
		UseDeadlyPoisonAction(PlayerbotAI* ai) : UseItemAction(ai, "Deadly Poison") {}
		virtual bool Execute(Event event);
	};

	class UseInstantPoisonAction : public UseItemAction
	{
	public:
		UseInstantPoisonAction(PlayerbotAI* ai) : UseItemAction(ai, "Instant Poison") {}
		virtual bool Execute(Event event);
	};

	class EnvenomAction : public CastMeleeSpellAction
	{
	public:
		EnvenomAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "envenom") {}
	};

	class FanOfKnivesAction : public CastMeleeSpellAction
	{
	public:
		FanOfKnivesAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "fan of knives") {}
	};

	class CastTricksOfTheTradeOnMainTankAction : public BuffOnMainTankAction
	{
	public:
		CastTricksOfTheTradeOnMainTankAction(PlayerbotAI* ai) : BuffOnMainTankAction(ai, "tricks of the trade") {}
		virtual bool isUseful() {
            return BuffOnMainTankAction::isUseful() && AI_VALUE2(float, "distance", GetTargetName()) < 20.0f;
        }
	};
}
