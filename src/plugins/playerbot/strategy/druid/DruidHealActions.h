#pragma once

#include "../actions/GenericActions.h"
#include "../Spells/Auras/SpellAuraEffects.h"

namespace ai {
	class CastNourishAction : public CastHealingSpellAction
	{
	public:
		CastNourishAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "nourish") {}
	};

	class CastPartyNourishAction : public HealPartyMemberAction
	{
	public:
		CastPartyNourishAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "nourish") {}
	};

    class CastPartySwiftmendAction : public HealPartyMemberAction
	{
	public:
		CastPartySwiftmendAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "swiftmend") {}
	};

    class CastNaturesSwiftnessAction : public CastBuffSpellAction
	{
	public:
		CastNaturesSwiftnessAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "nature's swift") {}
	};

	class CastLifeBloomAction : public CastHealingSpellAction
	{
	public:
		CastLifeBloomAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "lifebloom") {}
		virtual bool isUseful() {
			if (!CastSpellAction::isUseful()) {
				return false;
			}
			Aura *aura = ai->GetAura(spell, GetTarget());
			if (aura == nullptr) {
				return true;
			}
			// if (aura->GetStackAmount() >= 3)  {
			// 	return false;
			// }
			if (aura->GetDuration() >= 2000)  {
				return false;
			}
			return true;
		}
	};

	class CastPartyLifeBloomAction : public HealPartyMemberAction
	{
	public:
		CastPartyLifeBloomAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "lifebloom") {}
		virtual bool isUseful() {
			if (!CastSpellAction::isUseful()) {
				return false;
			}
			Aura *aura = ai->GetAura(spell, GetTarget());
			if (aura == nullptr) {
				return true;
            }
			// if (aura->GetStackAmount() >= 3)  {
			// 	return false;
			// }
			if (aura->GetDuration() >= 2000)  {
				return false;
			}
			return true;
		}
	};
}
