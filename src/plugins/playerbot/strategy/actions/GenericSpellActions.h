#pragma once

#include "../Action.h"
#include "../../PlayerbotAIConfig.h"

#define BEGIN_SPELL_ACTION(clazz, name) \
class clazz : public CastSpellAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : CastSpellAction(ai, name) {} \


#define END_SPELL_ACTION() \
    };

#define BEGIN_DEBUFF_ACTION(clazz, name) \
class clazz : public CastDebuffSpellAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : CastDebuffSpellAction(ai, name) {} \

#define BEGIN_RANGED_SPELL_ACTION(clazz, name) \
class clazz : public CastSpellAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : CastSpellAction(ai, name) {} \

#define BEGIN_MELEE_SPELL_ACTION(clazz, name) \
class clazz : public CastMeleeSpellAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : CastMeleeSpellAction(ai, name) {} \


#define END_RANGED_SPELL_ACTION() \
    };


#define BEGIN_BUFF_ON_PARTY_ACTION(clazz, name) \
class clazz : public BuffOnPartyAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : BuffOnPartyAction(ai, name) {}

namespace ai
{
    class CastSpellAction : public Action
    {
    public:
        CastSpellAction(PlayerbotAI* ai, string spell) : Action(ai, spell),
			range(sPlayerbotAIConfig.spellDistance)
        {
            this->spell = spell;
        }

		virtual string GetTargetName() { return "current target"; };
        virtual bool Execute(Event event);
        virtual bool isPossible();
		virtual bool isUseful();
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_SINGLE; }

		virtual NextAction** getPrerequisites()
		{
			if (spell == "mount")
				return NULL;
			// if (range > sPlayerbotAIConfig.spellDistance + 7.5f)
			// 	return NULL;
            else if (range > sPlayerbotAIConfig.spellDistance)
                return NULL;
                // return NextAction::merge( NextAction::array(0, new NextAction("reach heal"), NULL), Action::getPrerequisites());
			else if (range > ATTACK_DISTANCE)
				return NextAction::merge( NextAction::array(0, new NextAction("reach spell"), NULL), Action::getPrerequisites());
			else
				return NextAction::merge( NextAction::array(0, new NextAction("reach melee"), NULL), Action::getPrerequisites());
		}

    protected:
        string spell;
		float range;
    };

	//---------------------------------------------------------------------------------------------------------------------
	class CastAuraSpellAction : public CastSpellAction
	{
	public:
		CastAuraSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}

		virtual bool isUseful();
	};

    //---------------------------------------------------------------------------------------------------------------------
	class CastAuraFromBotSpellAction : public CastSpellAction
	{
	public:
		CastAuraFromBotSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}

		virtual bool isUseful();
	};

    //---------------------------------------------------------------------------------------------------------------------
    class CastMeleeSpellAction : public CastSpellAction
    {
    public:
        CastMeleeSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {
			range = ATTACK_DISTANCE;
		}
    };

    //---------------------------------------------------------------------------------------------------------------------
    class CastDebuffSpellAction : public CastAuraFromBotSpellAction
    {
    public:
        CastDebuffSpellAction(PlayerbotAI* ai, string spell) : CastAuraFromBotSpellAction(ai, spell) {}
    };

    class CastDebuffSpellOnAttackerAction : public CastAuraSpellAction
    {
    public:
        CastDebuffSpellOnAttackerAction(PlayerbotAI* ai, string spell) : CastAuraSpellAction(ai, spell) {}
        Value<Unit*>* GetTargetValue()
        {
            return context->GetValue<Unit*>("attacker without aura from bot", spell);
        }
        virtual string getName() { return spell + " on attacker"; }
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_NONE; }
    };

	class CastBuffSpellAction : public CastAuraSpellAction
	{
	public:
		CastBuffSpellAction(PlayerbotAI* ai, string spell) : CastAuraSpellAction(ai, spell)
		{
			range = sPlayerbotAIConfig.spellDistance;
		}

        virtual string GetTargetName() { return "self target"; }
	};

	class CastEnchantItemAction : public CastSpellAction
	{
	public:
	    CastEnchantItemAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell)
		{
			range = sPlayerbotAIConfig.spellDistance;
		}

        virtual bool isPossible();
        virtual string GetTargetName() { return "self target"; }
	};

    //---------------------------------------------------------------------------------------------------------------------

    class CastHealingSpellAction : public CastAuraFromBotSpellAction
    {
    public:
        CastHealingSpellAction(PlayerbotAI* ai, string spell, uint8 estAmount = 5.0f) : CastAuraFromBotSpellAction(ai, spell)
		{
            this->estAmount = estAmount;
			range = sPlayerbotAIConfig.spellDistance;
        }
		virtual string GetTargetName() { return "self target"; }
        virtual bool isUseful();
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_AOE; }

    protected:
        uint8 estAmount;
    };

    class CastAoeHealSpellAction : public CastHealingSpellAction
    {
    public:
    	CastAoeHealSpellAction(PlayerbotAI* ai, string spell, uint8 estAmount = 15.0f) : CastHealingSpellAction(ai, spell, estAmount) {}
		virtual string GetTargetName() { return "party member to heal"; }
        virtual bool isUseful();
    };

	class CastCureSpellAction : public CastSpellAction
	{
	public:
		CastCureSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell)
		{
			range = sPlayerbotAIConfig.spellDistance;
		}

		virtual string GetTargetName() { return "self target"; }
	};

	class PartyMemberActionNameSupport {
	public:
		PartyMemberActionNameSupport(string spell)
		{
			name = string(spell) + " on party";
		}

		virtual string getName() { return name; }

	private:
		string name;
	};

    class MainTankActionNameSupport {
	public:
		MainTankActionNameSupport(string spell)
		{
			name = string(spell) + " on main tank";
		}

		virtual string getName() { return name; }

	private:
		string name;
	};

    class HealPartyMemberAction : public CastHealingSpellAction, public PartyMemberActionNameSupport
    {
    public:
        HealPartyMemberAction(PlayerbotAI* ai, string spell, uint8 estAmount = 15.0f) :
			CastHealingSpellAction(ai, spell, estAmount), PartyMemberActionNameSupport(spell) {}

		virtual string GetTargetName() { return "party member to heal"; }
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
        virtual NextAction** getPrerequisites()
		{
			if (spell == "mount")
				return NULL;
			if (range > sPlayerbotAIConfig.spellDistance + 10.0f)
				return NULL;
			else
				return NextAction::merge( NextAction::array(0, new NextAction("reach party member to heal"), NULL), Action::getPrerequisites());
		}
    };

	class ResurrectPartyMemberAction : public CastSpellAction
	{
	public:
		ResurrectPartyMemberAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}

		virtual string GetTargetName() { return "party member to resurrect"; }
        virtual bool isUseful() {
            return CastSpellAction::isUseful() && 
            (!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana);
        }
        virtual NextAction** getPrerequisites()
		{
			if (spell == "mount")
				return NULL;
			if (range > sPlayerbotAIConfig.spellDistance)
				return NULL;
			else
				return NextAction::merge( NextAction::array(0, new NextAction("reach party member to resurrect"), NULL), Action::getPrerequisites());
		}
	};
    //---------------------------------------------------------------------------------------------------------------------

    class CurePartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        CurePartyMemberAction(PlayerbotAI* ai, string spell, uint32 dispelType) :
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        {
            this->dispelType = dispelType;
        }

		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }

    protected:
        uint32 dispelType;
    };

    //---------------------------------------------------------------------------------------------------------------------

    class BuffOnPartyAction : public CastBuffSpellAction, public PartyMemberActionNameSupport
    {
    public:
        BuffOnPartyAction(PlayerbotAI* ai, string spell) :
			CastBuffSpellAction(ai, spell), PartyMemberActionNameSupport(spell) {}
    public:
		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };

    //---------------------------------------------------------------------------------------------------------------------

    class BuffOnMainTankAction : public CastBuffSpellAction, public MainTankActionNameSupport
    {
    public:
        BuffOnMainTankAction(PlayerbotAI* ai, string spell) :
			CastBuffSpellAction(ai, spell), MainTankActionNameSupport(spell) {}
    public:
		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return MainTankActionNameSupport::getName(); }
    };

    class CastShootAction : public CastSpellAction
    {
    public:
        CastShootAction(PlayerbotAI* ai) : CastSpellAction(ai, "shoot") {}
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_NONE; }
    };

	class CastLifeBloodAction : public CastHealingSpellAction
	{
	public:
		CastLifeBloodAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "lifeblood") {}
	};

	class CastGiftOfTheNaaruAction : public CastHealingSpellAction
	{
	public:
		CastGiftOfTheNaaruAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "gift of the naaru") {}
	};

    class CastArcaneTorrentAction : public CastBuffSpellAction
    {
    public:
        CastArcaneTorrentAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "arcane torrent") {}
    };

    class CastSpellOnEnemyHealerAction : public CastSpellAction
    {
    public:
        CastSpellOnEnemyHealerAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}
        Value<Unit*>* GetTargetValue()
        {
            return context->GetValue<Unit*>("enemy healer target", spell);
        }
        virtual string getName() { return spell + " on enemy healer"; }
    };
}
