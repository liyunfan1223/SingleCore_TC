#pragma once
#include "../Trigger.h"
#include "../../PlayerbotAIConfig.h"
#include "../../../Battlegrounds/Battleground.h"
#include "../../../Battlegrounds/BattlegroundMgr.h"
#include "../../../Battlegrounds/BattlegroundQueue.h"
#include "../../../Battlegrounds/Zones/BattlegroundWS.h"

#define BUFF_TRIGGER(clazz, spell, action) \
    class clazz : public BuffTrigger \
    { \
    public: \
        clazz(PlayerbotAI* ai) : BuffTrigger(ai, spell) {} \
    };

#define BUFF_TRIGGER_FREQ(clazz, spell, action) \
    class clazz : public BuffTrigger \
    { \
    public: \
        clazz(PlayerbotAI* ai) : BuffTrigger(ai, spell, 1) {} \
    };

#define BUFF_ON_PARTY_TRIGGER(clazz, spell, action) \
    class clazz : public BuffOnPartyTrigger \
    { \
    public: \
        clazz(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, spell) {}  \
    };

#define DEBUFF_TRIGGER(clazz, spell, action) \
    class clazz : public DebuffTrigger \
    { \
    public: \
        clazz(PlayerbotAI* ai) : DebuffTrigger(ai, spell) {} \
    };

#define DEBUFF_FROM_BOT_TRIGGER(clazz, spell, action) \
    class clazz : public DebuffFromBotTrigger \
    { \
    public: \
        clazz(PlayerbotAI* ai) : DebuffFromBotTrigger(ai, spell) {} \
    };


namespace ai
{
	class StatAvailable : public Trigger
	{
	public:
		StatAvailable(PlayerbotAI* ai, int amount, string name = "stat available") : Trigger(ai, name)
		{
			this->amount = amount;
		}

	protected:
		int amount;
	};

	class RageAvailable : public StatAvailable
    {
    public:
        RageAvailable(PlayerbotAI* ai, int amount) : StatAvailable(ai, amount, "rage available") {}
        virtual bool IsActive();
    };

    class LightRageAvailableTrigger : public RageAvailable
    {
    public:
        LightRageAvailableTrigger(PlayerbotAI* ai) : RageAvailable(ai, 20) {}
    };

    class MediumRageAvailableTrigger : public RageAvailable
    {
    public:
        MediumRageAvailableTrigger(PlayerbotAI* ai) : RageAvailable(ai, 40) {}
    };

    class HighRageAvailableTrigger : public RageAvailable
    {
    public:
        HighRageAvailableTrigger(PlayerbotAI* ai) : RageAvailable(ai, 60) {}
    };

	class EnergyAvailable : public StatAvailable
	{
	public:
		EnergyAvailable(PlayerbotAI* ai, int amount) : StatAvailable(ai, amount, "energy available") {}
		virtual bool IsActive();
	};

    class LightEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        LightEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 20) {}
    };

    class MediumEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        MediumEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 40) {}
    };

    class HighEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        HighEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 60) {}
    };

	class ComboPointsAvailableTrigger : public StatAvailable
	{
	public:
	    ComboPointsAvailableTrigger(PlayerbotAI* ai, int amount = 5) : StatAvailable(ai, amount, "combo points available") {}
		virtual bool IsActive();
	};

	class LoseAggroTrigger : public Trigger {
	public:
		LoseAggroTrigger(PlayerbotAI* ai) : Trigger(ai, "lose aggro") {}
		virtual bool IsActive();
	};

	class HasAggroTrigger : public Trigger {
	public:
	    HasAggroTrigger(PlayerbotAI* ai) : Trigger(ai, "have aggro") {}
		virtual bool IsActive();
	};

	class SpellTrigger : public Trigger
	{
	public:
		SpellTrigger(PlayerbotAI* ai, string spell, int checkInterval = 1) : Trigger(ai, spell, checkInterval)
		{
			this->spell = spell;
		}

		virtual string GetTargetName() { return "current target"; }
		virtual string getName() { return spell; }
		virtual bool IsActive();

	protected:
		string spell;
	};

	class SpellCanBeCastTrigger : public SpellTrigger
	{
	public:
		SpellCanBeCastTrigger(PlayerbotAI* ai, string spell) : SpellTrigger(ai, spell) {}
		virtual bool IsActive();
	};

	// TODO: check other targets
    class InterruptSpellTrigger : public SpellTrigger
	{
    public:
        InterruptSpellTrigger(PlayerbotAI* ai, string spell) : SpellTrigger(ai, spell) {}
        virtual bool IsActive();
    };


    class AttackerCountTrigger : public Trigger
    {
    public:
        AttackerCountTrigger(PlayerbotAI* ai, int amount, float distance = sPlayerbotAIConfig.sightDistance) : Trigger(ai)
        {
            this->amount = amount;
            this->distance = distance;
        }
    public:
        virtual bool IsActive()
		{
            return AI_VALUE(uint8, "attacker count") >= amount;
        }
        virtual string getName() { return "attacker count"; }

    protected:
        int amount;
        float distance;
    };

    class HasAttackersTrigger : public AttackerCountTrigger
    {
    public:
        HasAttackersTrigger(PlayerbotAI* ai) : AttackerCountTrigger(ai, 1) {}
    };

    class MyAttackerCountTrigger : public AttackerCountTrigger
    {
    public:
        MyAttackerCountTrigger(PlayerbotAI* ai, int amount) : AttackerCountTrigger(ai, amount) {}
    public:
        virtual bool IsActive();
        virtual string getName() { return "my attacker count"; }
    };

    class MediumThreatTrigger : public MyAttackerCountTrigger
    {
    public:
        MediumThreatTrigger(PlayerbotAI* ai) : MyAttackerCountTrigger(ai, 2) {}
    };

    class AoeTrigger : public AttackerCountTrigger
    {
    public:
        AoeTrigger(PlayerbotAI* ai, int amount = 3, float range = 15.0f) : AttackerCountTrigger(ai, amount)
        {
            this->range = range;
        }
    public:
        virtual bool IsActive();
        virtual string getName() { return "aoe"; }

    private:
        float range;
    };

    class NoFoodTrigger : public Trigger {
    public:
        NoFoodTrigger(PlayerbotAI* ai) : Trigger(ai, "no food trigger") {}
        virtual bool IsActive() { return AI_VALUE2(list<Item*>, "inventory items", "food").empty(); }
    };

    class NoDrinkTrigger : public Trigger {
    public:
        NoDrinkTrigger(PlayerbotAI* ai) : Trigger(ai, "no drink trigger") {}
        virtual bool IsActive() { return AI_VALUE2(list<Item*>, "inventory items", "drink").empty(); }
    };

    class LightAoeTrigger : public AoeTrigger
    {
    public:
        LightAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 2, 8.0f) {}
    };

    class MediumAoeTrigger : public AoeTrigger
    {
    public:
        MediumAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 3, 8.0f) {}
    };

    class HighAoeTrigger : public AoeTrigger
    {
    public:
        HighAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 4, 8.0f) {}
    };

    class BuffTrigger : public SpellTrigger
    {
    public:
        BuffTrigger(PlayerbotAI* ai, string spell, int checkInterval = 5) : SpellTrigger(ai, spell, checkInterval) {}
    public:
		virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class BuffOnPartyTrigger : public BuffTrigger
    {
    public:
        BuffOnPartyTrigger(PlayerbotAI* ai, string spell) : BuffTrigger(ai, spell, 1) {}
    public:
		virtual Value<Unit*>* GetTargetValue();
    };

    class BuffOnMainTankTrigger : public BuffTrigger
    {
    public:
        BuffOnMainTankTrigger(PlayerbotAI* ai, string spell) : BuffTrigger(ai, spell, 1) {}
    public:
		virtual Value<Unit*>* GetTargetValue();
    };

    BEGIN_TRIGGER(NoAttackersTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(NoTargetTrigger, Trigger)
    END_TRIGGER()

    // BEGIN_TRIGGER(InvalidTargetTrigger, Trigger)
    // END_TRIGGER()

    class InvalidTargetTrigger : public Trigger {
    public:
        InvalidTargetTrigger(PlayerbotAI* ai) : Trigger(ai, "invalid target") {}
        virtual bool IsActive();
    };

    // BEGIN_TRIGGER(NoValidTargetTrigger, Trigger)
    // END_TRIGGER()
    
    class NoValidTargetTrigger : public Trigger {
    public:
        NoValidTargetTrigger(PlayerbotAI* ai) : Trigger(ai, "no valid target") {}
        virtual bool IsActive();
    };

    class TargetInSightTrigger : public Trigger {
    public:
        TargetInSightTrigger(PlayerbotAI* ai) : Trigger(ai, "target in sight") {}
        virtual bool IsActive() { return AI_VALUE(Unit*, "grind target"); }
    };

    class DebuffTrigger : public BuffTrigger
    {
    public:
        DebuffTrigger(PlayerbotAI* ai, string spell, int checkInterval = 1, int life_bound = 25) : 
        BuffTrigger(ai, spell, checkInterval), life_bound(life_bound) {}
    public:
		virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    protected:
        int life_bound;
    };

    class HasAuraFromBotTrigger : public Trigger {
	public:
		HasAuraFromBotTrigger(PlayerbotAI* ai, string spell, int checkInterval = 5) : Trigger(ai, spell, checkInterval) {}

		virtual string GetTargetName() { return "self target"; }
		virtual bool IsActive();

	};
    
    class DebuffFromBotTrigger : public Trigger
    {
    public:
        DebuffFromBotTrigger(PlayerbotAI* ai, string spell, int checkInterval = 1, int life_bound = 25) : 
        Trigger(ai, spell, checkInterval), life_bound(life_bound) {}
    public:
		virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    protected:
        int life_bound;
    };

    class DebuffOnAttackerTrigger : public DebuffTrigger
    {
    public:
        DebuffOnAttackerTrigger(PlayerbotAI* ai, string spell) : DebuffTrigger(ai, spell) {
            this->spell = spell;
        }
    public:
        virtual Value<Unit*>* GetTargetValue();
        virtual string getName() { return spell + " on attacker"; }
    };

    class DebuffFromBotOnAttackerTrigger : public DebuffFromBotTrigger
    {
    public:
        DebuffFromBotOnAttackerTrigger(PlayerbotAI* ai, string spell) : DebuffFromBotTrigger(ai, spell) {
            this->spell = spell;
        }
    public:
        virtual Value<Unit*>* GetTargetValue();
        virtual string getName() { return spell + " on attacker"; }
    protected:
        string spell;
    };

	class BoostTrigger : public BuffTrigger
	{
	public:
		BoostTrigger(PlayerbotAI* ai, string spell, float balance = 50) : BuffTrigger(ai, spell, 1)
		{
			this->balance = balance;
		}
	public:
		virtual bool IsActive();

	protected:
		float balance;
	};

    class RandomTrigger : public Trigger
    {
    public:
		RandomTrigger(PlayerbotAI* ai, string name, int probability = 7) : Trigger(ai, name)
        {
            this->probability = probability;
			lastCheck = time(0);
        }
    public:
        virtual bool IsActive();

    protected:
        int probability;
		time_t lastCheck;
    };

    class AndTrigger : public Trigger
    {
    public:
        AndTrigger(PlayerbotAI* ai, Trigger* ls, Trigger* rs) : Trigger(ai)
        {
            this->ls = ls;
            this->rs = rs;
        }
        virtual ~AndTrigger()
        {
            delete ls;
            delete rs;
        }
    public:
        virtual bool IsActive();
        virtual string getName();

    protected:
        Trigger* ls;
        Trigger* rs;
    };

    class SnareTargetTrigger : public DebuffTrigger
    {
    public:
        SnareTargetTrigger(PlayerbotAI* ai, string aura) : DebuffTrigger(ai, aura) {}
    public:
        virtual bool IsActive();
        virtual string getName() { return "target is moving"; }
    };

	class LowManaTrigger : public Trigger
	{
	public:
		LowManaTrigger(PlayerbotAI* ai) : Trigger(ai, "low mana") {}

		virtual bool IsActive();
	};

	class MediumManaTrigger : public Trigger
	{
	public:
		MediumManaTrigger(PlayerbotAI* ai) : Trigger(ai, "medium mana") {}

		virtual bool IsActive();
	};

    BEGIN_TRIGGER(PanicTrigger, Trigger)
        virtual string getName() { return "panic"; }
    END_TRIGGER()


	class NoPetTrigger : public Trigger
	{
	public:
		NoPetTrigger(PlayerbotAI* ai) : Trigger(ai, "no pet", 5) {}

		virtual bool IsActive() {
			return !AI_VALUE(Unit*, "pet target") && !AI_VALUE2(bool, "mounted", "self target");
		}
	};

    class HasPetTrigger : public Trigger
	{
	public:
		HasPetTrigger(PlayerbotAI* ai) : Trigger(ai, "no pet", 15) {}

		virtual bool IsActive() {
			return AI_VALUE(Unit*, "pet target");
		}
	};

	class ItemCountTrigger : public Trigger {
	public:
		ItemCountTrigger(PlayerbotAI* ai, string item, int count) : Trigger(ai, item, 5) {
			this->item = item;
			this->count = count;
		}
	public:
		virtual bool IsActive();
		virtual string getName() { return "item count"; }

	protected:
		string item;
		int count;
	};

	class HasAuraTrigger : public Trigger {
	public:
		HasAuraTrigger(PlayerbotAI* ai, string spell, int checkInterval = 5) : Trigger(ai, spell, checkInterval) {}

		virtual string GetTargetName() { return "self target"; }
		virtual bool IsActive();

	};

    class HasNotAuraTrigger : public Trigger {
	public:
		HasNotAuraTrigger(PlayerbotAI* ai, string spell, int checkInterval = 5) : Trigger(ai, spell, checkInterval) {}

		virtual string GetTargetName() { return "self target"; }
		virtual bool IsActive();

	};

    class HasAuraStackTrigger : public Trigger {
	public:
		HasAuraStackTrigger(PlayerbotAI* ai, string spell, int stack = 4, int checkInterval = 5) : Trigger(ai, spell, checkInterval),
            stack(stack) {}

		virtual string GetTargetName() { return "self target"; }
		virtual bool IsActive();
    private:
        int stack;
	};

    class TimerTrigger : public Trigger
    {
    public:
        TimerTrigger(PlayerbotAI* ai, int checkInterval = 5) : Trigger(ai, "timer", checkInterval) {}

    public:
        virtual bool IsActive() { return true; }
    };

	class TankAoeTrigger : public Trigger
	{
	public:
		TankAoeTrigger(PlayerbotAI* ai) : Trigger(ai, "tank aoe") {}

	public:
		virtual bool IsActive();
	};

    class IsBehindTargetTrigger : public Trigger
    {
    public:
        IsBehindTargetTrigger(PlayerbotAI* ai) : Trigger(ai) {}

    public:
        virtual bool IsActive();
    };

    class IsNotFacingTargetTrigger : public Trigger
    {
    public:
        IsNotFacingTargetTrigger(PlayerbotAI* ai) : Trigger(ai) {}

    public:
        virtual bool IsActive();
    };

    class HasCcTargetTrigger : public Trigger
    {
    public:
        HasCcTargetTrigger(PlayerbotAI* ai, string name) : Trigger(ai, name) {}

    public:
        virtual bool IsActive();
    };

	class NoMovementTrigger : public Trigger
	{
	public:
		NoMovementTrigger(PlayerbotAI* ai, string name) : Trigger(ai, name) {}

	public:
		virtual bool IsActive();
	};


    class NoPossibleTargetsTrigger : public Trigger
    {
    public:
        NoPossibleTargetsTrigger(PlayerbotAI* ai) : Trigger(ai, "no possible targets") {}

    public:
        virtual bool IsActive();
    };

    class NotLeastHpTargetActiveTrigger : public Trigger
    {
    public:
        NotLeastHpTargetActiveTrigger(PlayerbotAI* ai) : Trigger(ai, "not least hp target active") {}

    public:
        virtual bool IsActive();
    };

    class EnemyPlayerIsAttacking : public Trigger
    {
    public:
        EnemyPlayerIsAttacking(PlayerbotAI* ai) : Trigger(ai, "enemy player is attacking") {}

    public:
        virtual bool IsActive();
    };

	class PlayerHasNoFlag : public Trigger
	{
	public:
		PlayerHasNoFlag(PlayerbotAI* ai) : Trigger(ai, "player has no flag") {}

	public:
		virtual bool IsActive();
	};

	class PlayerIsInBattleground : public Trigger
	{
	public:
		PlayerIsInBattleground(PlayerbotAI* ai) : Trigger(ai, "in battleground") {}

	public:
		virtual bool IsActive();
	};

	class PlayerIsInBattlegroundWithoutFlag : public Trigger
	{
	public:
		PlayerIsInBattlegroundWithoutFlag(PlayerbotAI* ai) : Trigger(ai, "in battleground without flag") {}

	public:
		virtual bool IsActive();
	};


    class IsSwimmingTrigger : public Trigger
    {
    public:
        IsSwimmingTrigger(PlayerbotAI* ai) : Trigger(ai, "swimming") {}

    public:
        virtual bool IsActive();
    };

    class HasNearestAddsTrigger : public Trigger
    {
    public:
        HasNearestAddsTrigger(PlayerbotAI* ai) : Trigger(ai, "has nearest adds") {}

    public:
        virtual bool IsActive();
    };

    class HasItemForSpellTrigger : public Trigger
    {
    public:
        HasItemForSpellTrigger(PlayerbotAI* ai, string spell) : Trigger(ai, spell) {}

    public:
        virtual bool IsActive();
    };

    class TargetChangedTrigger : public Trigger
    {
    public:
        TargetChangedTrigger(PlayerbotAI* ai) : Trigger(ai, "target changed") {}

    public:
        virtual bool IsActive();
    };

    class InterruptEnemyHealerTrigger : public SpellTrigger
    {
    public:
        InterruptEnemyHealerTrigger(PlayerbotAI* ai, string spell) : SpellTrigger(ai, spell) {}
    public:
        virtual Value<Unit*>* GetTargetValue();
        virtual string getName() { return spell + " on enemy healer"; }
    };

	class RandomBotUpdateTrigger : public RandomTrigger
	{
	public:
		RandomBotUpdateTrigger(PlayerbotAI* ai) : RandomTrigger(ai, "random bot update", 15) {}
		
	public:
		virtual bool IsActive()
		{
			return RandomTrigger::IsActive() && AI_VALUE(bool, "random bot update");
		}
	};

	class NoNonBotPlayersAroundTrigger : public Trigger
	{
	public:
		NoNonBotPlayersAroundTrigger(PlayerbotAI* ai) : Trigger(ai, "no non bot players around", 5) {}

	public:
		virtual bool IsActive()
		{
			return AI_VALUE(list<ObjectGuid>, "nearest non bot players").empty();
		}
	};

    class AvoidAOESpellTrigger : public Trigger
    {
    public:
        AvoidAOESpellTrigger(PlayerbotAI* ai) : Trigger(ai, "avoid aoe", 1) {}
    public:
        virtual bool IsActive();
    };
}

#include "RangeTriggers.h"
#include "HealthTriggers.h"
#include "CureTriggers.h"
