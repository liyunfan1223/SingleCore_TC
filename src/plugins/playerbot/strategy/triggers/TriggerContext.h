#pragma once

#include "HealthTriggers.h"
#include "GenericTriggers.h"
#include "LootTriggers.h"
#include "../triggers/GenericTriggers.h"
#include "LfgTriggers.h"
#include "RaidNaxxTrigger.h"

namespace ai
{

    class TriggerContext : public NamedObjectContext<Trigger>
    {
    public:
        TriggerContext()
        {
            creators["timer"] = &TriggerContext::Timer;
            creators["random"] = &TriggerContext::Random;
            creators["seldom"] = &TriggerContext::seldom;
            creators["often"] = &TriggerContext::often;

            creators["target critical health"] = &TriggerContext::TargetCriticalHealth;

            creators["critical health"] = &TriggerContext::CriticalHealth;
            creators["low health"] = &TriggerContext::LowHealth;
            creators["medium health"] = &TriggerContext::MediumHealth;
            creators["almost full health"] = &TriggerContext::AlmostFullHealth;

            creators["low mana"] = &TriggerContext::LowMana;
            creators["medium mana"] = &TriggerContext::MediumMana;

            creators["party member critical health"] = &TriggerContext::PartyMemberCriticalHealth;
            creators["party member low health"] = &TriggerContext::PartyMemberLowHealth;
            creators["party member medium health"] = &TriggerContext::PartyMemberMediumHealth;
            creators["party member almost full health"] = &TriggerContext::PartyMemberAlmostFullHealth;

            creators["light rage available"] = &TriggerContext::LightRageAvailable;
            creators["medium rage available"] = &TriggerContext::MediumRageAvailable;
            creators["high rage available"] = &TriggerContext::HighRageAvailable;

            creators["light energy available"] = &TriggerContext::LightEnergyAvailable;
            creators["medium energy available"] = &TriggerContext::MediumEnergyAvailable;
            creators["high energy available"] = &TriggerContext::HighEnergyAvailable;

            creators["loot available"] = &TriggerContext::LootAvailable;
            creators["no attackers"] = &TriggerContext::NoAttackers;
            creators["no target"] = &TriggerContext::NoTarget;
            creators["target in sight"] = &TriggerContext::TargetInSight;
            creators["not least hp target active"] = &TriggerContext::not_least_hp_target_active;
            creators["has nearest adds"] = &TriggerContext::has_nearest_adds;
            creators["enemy player is attacking"] = &TriggerContext::enemy_player_is_attacking;
			creators["has no flag"] = &TriggerContext::player_has_no_flag;
			creators["in battleground"] = &TriggerContext::player_is_in_battleground;
			creators["in battleground without flag"] = &TriggerContext::player_is_in_battleground_no_flag;

            creators["tank aoe"] = &TriggerContext::TankAoe;
            creators["lose aggro"] = &TriggerContext::LoseAggro;
            creators["has aggro"] = &TriggerContext::HasAggro;

            creators["light aoe"] = &TriggerContext::LightAoe;
            creators["medium aoe"] = &TriggerContext::MediumAoe;
            creators["high aoe"] = &TriggerContext::HighAoe;

            creators["enemy out of melee"] = &TriggerContext::EnemyOutOfMelee;
            creators["enemy out of spell"] = &TriggerContext::EnemyOutOfSpell;
            creators["enemy too close for spell"] = &TriggerContext::enemy_too_close_for_spell;
			creators["enemy too close for shoot"] = &TriggerContext::enemy_too_close_for_shoot;
            creators["enemy too close for melee"] = &TriggerContext::enemy_too_close_for_melee;
			creators["enemy is close"] = &TriggerContext::enemy_is_close;

            creators["combo points available"] = &TriggerContext::ComboPointsAvailable;
            creators["combo points available 3"] = &TriggerContext::ComboPointsAvailable3;

            creators["medium threat"] = &TriggerContext::MediumThreat;

            creators["dead"] = &TriggerContext::Dead;
            creators["party member to resurrect"] = &TriggerContext::PartyMemberDead;
            creators["combat party member to resurrect"] = &TriggerContext::CombatPartyMemberDead;
            creators["no pet"] = &TriggerContext::no_pet;
            creators["has pet"] = &TriggerContext::has_pet;
            creators["has attackers"] = &TriggerContext::has_attackers;
            creators["no possible targets"] = &TriggerContext::no_possible_targets;

            creators["no drink"] = &TriggerContext::no_drink;
            creators["no food"] = &TriggerContext::no_food;

            creators["panic"] = &TriggerContext::panic;
            creators["behind target"] = &TriggerContext::behind_target;
            creators["not facing target"] = &TriggerContext::not_facing_target;
            creators["far from master"] = &TriggerContext::far_from_master;
            creators["far from loot target"] = &TriggerContext::far_from_loot_target;
            creators["can loot"] = &TriggerContext::can_loot;
            creators["swimming"] = &TriggerContext::swimming;
            creators["target changed"] = &TriggerContext::target_changed;

            creators["critical aoe heal"] = &TriggerContext::critical_aoe_heal;
            creators["low aoe heal"] = &TriggerContext::low_aoe_heal;
            creators["medium aoe heal"] = &TriggerContext::medium_aoe_heal;
            creators["group heal occasion"] = &TriggerContext::group_heal_occasion;
            creators["invalid target"] = &TriggerContext::invalid_target;
            creators["no valid target"] = &TriggerContext::no_valid_target;
            creators["lfg proposal active"] = &TriggerContext::lfg_proposal_active;
			creators["random bot update"] = &TriggerContext::random_bot_update_trigger;
			creators["no non bot players around"] = &TriggerContext::no_non_bot_players_around;
            creators["avoid aoe"] = &TriggerContext::avoid_aoe;
            creators["mutating injection"] = &TriggerContext::mutating_injection;
            creators["mutating injection removed"] = &TriggerContext::mutating_injection_removed;
            creators["grobbulus cloud"] = &TriggerContext::grobbulus_cloud;
            creators["heigan melee"] = &TriggerContext::heigan_melee;
            creators["heigan ranged"] = &TriggerContext::heigan_ranged;

            creators["thaddius phase pet"] = &TriggerContext::thaddius_phase_pet;
            creators["thaddius phase pet lose aggro"] = &TriggerContext::thaddius_phase_pet_lose_aggro;
            creators["thaddius phase transition"] = &TriggerContext::thaddius_phase_transition;
            creators["thaddius phase thaddius"] = &TriggerContext::thaddius_phase_thaddius;

            creators["razuvious tank"] = &TriggerContext::razuvious_tank;

            creators["horseman attractors"] = &TriggerContext::horseman_attractors;
            creators["horseman except attractors"] = &TriggerContext::horseman_except_attractors;

            creators["sapphiron ground main tank"] = &TriggerContext::sapphiron_ground_main_tank;
            creators["sapphiron ground except main tank"] = &TriggerContext::sapphiron_ground_except_main_tank;
            creators["sapphiron flight"] = &TriggerContext::sapphiron_flight;
            creators["sapphiron chill"] = &TriggerContext::sapphiron_ground_chill;

            creators["kel'thuzad"] = &TriggerContext::kelthuzad;
        }

    private:
        static Trigger* lfg_proposal_active(PlayerbotAI* ai) { return new LfgProposalActiveTrigger(ai); }
        static Trigger* invalid_target(PlayerbotAI* ai) { return new InvalidTargetTrigger(ai); }
        static Trigger* no_valid_target(PlayerbotAI* ai) { return new NoValidTargetTrigger(ai); }
        static Trigger* critical_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "critical aoe heal", "critical", 2); }
        static Trigger* low_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "low aoe heal", "low", 2); }
        static Trigger* medium_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "medium aoe heal", "medium", 2); }
        static Trigger* group_heal_occasion(PlayerbotAI* ai) { return new AoeInGroupTrigger(ai, "group heal occasion", "almost full", 0.4); }
        static Trigger* target_changed(PlayerbotAI* ai) { return new TargetChangedTrigger(ai); }
        static Trigger* swimming(PlayerbotAI* ai) { return new IsSwimmingTrigger(ai); }
        static Trigger* no_possible_targets(PlayerbotAI* ai) { return new NoPossibleTargetsTrigger(ai); }
        static Trigger* can_loot(PlayerbotAI* ai) { return new CanLootTrigger(ai); }
        static Trigger* far_from_loot_target(PlayerbotAI* ai) { return new FarFromCurrentLootTrigger(ai); }
        static Trigger* far_from_master(PlayerbotAI* ai) { return new FarFromMasterTrigger(ai); }
        static Trigger* behind_target(PlayerbotAI* ai) { return new IsBehindTargetTrigger(ai); }
        static Trigger* not_facing_target(PlayerbotAI* ai) { return new IsNotFacingTargetTrigger(ai); }
        static Trigger* panic(PlayerbotAI* ai) { return new PanicTrigger(ai); }
        static Trigger* no_drink(PlayerbotAI* ai) { return new NoDrinkTrigger(ai); }
        static Trigger* no_food(PlayerbotAI* ai) { return new NoFoodTrigger(ai); }
        static Trigger* LightAoe(PlayerbotAI* ai) { return new LightAoeTrigger(ai); }
        static Trigger* MediumAoe(PlayerbotAI* ai) { return new MediumAoeTrigger(ai); }
        static Trigger* HighAoe(PlayerbotAI* ai) { return new HighAoeTrigger(ai); }
        static Trigger* LoseAggro(PlayerbotAI* ai) { return new LoseAggroTrigger(ai); }
        static Trigger* HasAggro(PlayerbotAI* ai) { return new HasAggroTrigger(ai); }
        static Trigger* LowHealth(PlayerbotAI* ai) { return new LowHealthTrigger(ai); }
        static Trigger* MediumHealth(PlayerbotAI* ai) { return new MediumHealthTrigger(ai); }
        static Trigger* AlmostFullHealth(PlayerbotAI* ai) { return new AlmostFullHealthTrigger(ai); }
        static Trigger* CriticalHealth(PlayerbotAI* ai) { return new CriticalHealthTrigger(ai); }
        static Trigger* TargetCriticalHealth(PlayerbotAI* ai) { return new TargetCriticalHealthTrigger(ai); }
        static Trigger* LowMana(PlayerbotAI* ai) { return new LowManaTrigger(ai); }
        static Trigger* MediumMana(PlayerbotAI* ai) { return new MediumManaTrigger(ai); }
        static Trigger* LightRageAvailable(PlayerbotAI* ai) { return new LightRageAvailableTrigger(ai); }
        static Trigger* MediumRageAvailable(PlayerbotAI* ai) { return new MediumRageAvailableTrigger(ai); }
        static Trigger* HighRageAvailable(PlayerbotAI* ai) { return new HighRageAvailableTrigger(ai); }
        static Trigger* LightEnergyAvailable(PlayerbotAI* ai) { return new LightEnergyAvailableTrigger(ai); }
        static Trigger* MediumEnergyAvailable(PlayerbotAI* ai) { return new MediumEnergyAvailableTrigger(ai); }
        static Trigger* HighEnergyAvailable(PlayerbotAI* ai) { return new HighEnergyAvailableTrigger(ai); }
        static Trigger* LootAvailable(PlayerbotAI* ai) { return new LootAvailableTrigger(ai); }
        static Trigger* NoAttackers(PlayerbotAI* ai) { return new NoAttackersTrigger(ai); }
        static Trigger* TankAoe(PlayerbotAI* ai) { return new TankAoeTrigger(ai); }
        static Trigger* Timer(PlayerbotAI* ai) { return new TimerTrigger(ai); }
        static Trigger* NoTarget(PlayerbotAI* ai) { return new NoTargetTrigger(ai); }
        static Trigger* TargetInSight(PlayerbotAI* ai) { return new TargetInSightTrigger(ai); }
        static Trigger* not_least_hp_target_active(PlayerbotAI* ai) { return new NotLeastHpTargetActiveTrigger(ai); }
        static Trigger* has_nearest_adds(PlayerbotAI* ai) { return new HasNearestAddsTrigger(ai); }
        static Trigger* enemy_player_is_attacking(PlayerbotAI* ai) { return new EnemyPlayerIsAttacking(ai); }
		static Trigger* player_has_no_flag(PlayerbotAI* ai) { return new PlayerHasNoFlag(ai); }
		static Trigger* player_is_in_battleground(PlayerbotAI *ai) { return new PlayerIsInBattleground(ai); }
		static Trigger* player_is_in_battleground_no_flag(PlayerbotAI *ai) { return new PlayerIsInBattlegroundWithoutFlag(ai); }
		static Trigger* Random(PlayerbotAI* ai) { return new RandomTrigger(ai, "random", 7); }
		static Trigger* seldom(PlayerbotAI* ai) { return new RandomTrigger(ai, "seldom", 15); }
		static Trigger* often(PlayerbotAI* ai) { return new RandomTrigger(ai, "often", 5); }
        static Trigger* EnemyOutOfMelee(PlayerbotAI* ai) { return new EnemyOutOfMeleeTrigger(ai); }
        static Trigger* EnemyOutOfSpell(PlayerbotAI* ai) { return new EnemyOutOfSpellRangeTrigger(ai); }
        static Trigger* enemy_too_close_for_spell(PlayerbotAI* ai) { return new EnemyTooCloseForSpellTrigger(ai); }
		static Trigger* enemy_too_close_for_shoot(PlayerbotAI* ai) { return new EnemyTooCloseForShootTrigger(ai); }
        static Trigger* enemy_too_close_for_melee(PlayerbotAI* ai) { return new EnemyTooCloseForMeleeTrigger(ai); }
		static Trigger* enemy_is_close(PlayerbotAI* ai) { return new EnemyIsCloseTrigger(ai); }
        static Trigger* ComboPointsAvailable(PlayerbotAI* ai) { return new ComboPointsAvailableTrigger(ai, 5); }
        static Trigger* ComboPointsAvailable3(PlayerbotAI* ai) { return new ComboPointsAvailableTrigger(ai, 3); }
        static Trigger* MediumThreat(PlayerbotAI* ai) { return new MediumThreatTrigger(ai); }
        static Trigger* Dead(PlayerbotAI* ai) { return new DeadTrigger(ai); }
        static Trigger* PartyMemberDead(PlayerbotAI* ai) { return new PartyMemberDeadTrigger(ai); }
        static Trigger* CombatPartyMemberDead(PlayerbotAI* ai) { return new CombatPartyMemberDeadTrigger(ai); }
        static Trigger* PartyMemberLowHealth(PlayerbotAI* ai) { return new PartyMemberLowHealthTrigger(ai); }
        static Trigger* PartyMemberMediumHealth(PlayerbotAI* ai) { return new PartyMemberMediumHealthTrigger(ai); }
        static Trigger* PartyMemberAlmostFullHealth(PlayerbotAI* ai) { return new PartyMemberAlmostFullHealthTrigger(ai); }
        static Trigger* PartyMemberCriticalHealth(PlayerbotAI* ai) { return new PartyMemberCriticalHealthTrigger(ai); }
        static Trigger* no_pet(PlayerbotAI* ai) { return new NoPetTrigger(ai); }
        static Trigger* has_pet(PlayerbotAI* ai) { return new HasPetTrigger(ai); }
        static Trigger* has_attackers(PlayerbotAI* ai) { return new HasAttackersTrigger(ai); }
		static Trigger* random_bot_update_trigger(PlayerbotAI* ai) { return new RandomBotUpdateTrigger(ai); }
		static Trigger* no_non_bot_players_around(PlayerbotAI* ai) { return new NoNonBotPlayersAroundTrigger(ai); }
        static Trigger* avoid_aoe(PlayerbotAI* ai) { return new AvoidAOESpellTrigger(ai); }
        static Trigger* mutating_injection(PlayerbotAI* ai) { return new MutatingInjectionTrigger(ai); }
        static Trigger* mutating_injection_removed(PlayerbotAI* ai) { return new MutatingInjectionRemovedTrigger(ai); }
        static Trigger* grobbulus_cloud(PlayerbotAI* ai) { return new GrobbulusCloudTrigger(ai); }
        static Trigger* heigan_melee(PlayerbotAI* ai) { return new HeiganMeleeTrigger(ai); }
        static Trigger* heigan_ranged(PlayerbotAI* ai) { return new HeiganRangedTrigger(ai); }
        static Trigger* thaddius_phase_pet(PlayerbotAI* ai) { return new ThaddiusPhasePetTrigger(ai); }
        static Trigger* thaddius_phase_pet_lose_aggro(PlayerbotAI* ai) { return new ThaddiusPhasePetLoseAggroTrigger(ai); }
        static Trigger* thaddius_phase_transition(PlayerbotAI* ai) { return new ThaddiusPhaseTransitionTrigger(ai); }
        static Trigger* thaddius_phase_thaddius(PlayerbotAI* ai) { return new ThaddiusPhaseThaddiusTrigger(ai); }
        static Trigger* razuvious_tank(PlayerbotAI* ai) { return new RazuviousTankTrigger(ai); }
        static Trigger* horseman_attractors(PlayerbotAI* ai) { return new HorsemanAttractorsTrigger(ai); }
        static Trigger* horseman_except_attractors(PlayerbotAI* ai) { return new HorsemanExceptAttractorsTrigger(ai); }
        static Trigger* sapphiron_ground_main_tank(PlayerbotAI* ai) { return new SapphironGroundMainTankTrigger(ai); }
        static Trigger* sapphiron_ground_except_main_tank(PlayerbotAI* ai) { return new SapphironGroundExceptMainTankTrigger(ai); }
        static Trigger* sapphiron_flight(PlayerbotAI* ai) { return new SapphironFlightTrigger(ai); }
        static Trigger* sapphiron_ground_chill(PlayerbotAI* ai) { return new SapphironGroundChillTrigger(ai); }        
        static Trigger* kelthuzad(PlayerbotAI* ai) { return new KelthuzadTrigger(ai); }
    };
};
