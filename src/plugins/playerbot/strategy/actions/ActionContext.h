#pragma once

#include "GenericActions.h"
#include "NonCombatActions.h"
#include "EmoteAction.h"
#include "AddLootAction.h"
#include "LootAction.h"
#include "AddLootAction.h"
#include "StayActions.h"
#include "FollowActions.h"
#include "ChangeStrategyAction.h"
#include "ChooseTargetActions.h"
#include "SuggestWhatToDoAction.h"
#include "PositionAction.h"
#include "AttackAction.h"
#include "CheckMailAction.h"
#include "SayAction.h"
#include "CheckMountStateAction.h"
#include "RandomBotUpdateAction.h"
#include "RevealGatheringItemAction.h"
#include "DelayAction.h"
#include "RaidNaxxAction.h"

namespace ai
{
    class ActionContext : public NamedObjectContext<Action>
    {
    public:
        ActionContext()
        {
            creators["attack"] = &ActionContext::melee;
            creators["melee"] = &ActionContext::melee;
            creators["reach spell"] = &ActionContext::ReachSpell;
            creators["reach heal"] = &ActionContext::ReachHeal;
            creators["reach melee"] = &ActionContext::ReachMelee;
            creators["reach party member to heal"] = &ActionContext::ReachPartyMemberToHeal;
            creators["reach party member to resurrect"] = &ActionContext::ReachPartyMemberToResurrect;
            creators["flee"] = &ActionContext::flee;
            creators["gift of the naaru"] = &ActionContext::gift_of_the_naaru;
            creators["shoot"] = &ActionContext::shoot;
            creators["lifeblood"] = &ActionContext::lifeblood;
            creators["arcane torrent"] = &ActionContext::arcane_torrent;
            creators["end pull"] = &ActionContext::end_pull;
            creators["healthstone"] = &ActionContext::healthstone;
            creators["healing potion"] = &ActionContext::healing_potion;
            creators["mana potion"] = &ActionContext::mana_potion;
            creators["food"] = &ActionContext::food;
            creators["drink"] = &ActionContext::drink;
            creators["tank assist"] = &ActionContext::tank_assist;
            creators["dps assist"] = &ActionContext::dps_assist;
            creators["attack rti target"] = &ActionContext::attack_rti_target;
            creators["loot"] = &ActionContext::loot;
            creators["add loot"] = &ActionContext::add_loot;
            creators["add gathering loot"] = &ActionContext::add_gathering_loot;
            creators["add all loot"] = &ActionContext::add_all_loot;
            creators["shoot"] = &ActionContext::shoot;
            creators["follow"] = &ActionContext::follow;
            creators["runaway"] = &ActionContext::runaway;
            creators["stay"] = &ActionContext::stay;
            creators["attack anything"] = &ActionContext::attack_anything;
            creators["attack least hp target"] = &ActionContext::attack_least_hp_target;
            creators["attack enemy player"] = &ActionContext::enemy_player_target;
            creators["emote"] = &ActionContext::emote;
            creators["suggest what to do"] = &ActionContext::suggest_what_to_do;
            creators["move random"] = &ActionContext::move_random;
            creators["move to loot"] = &ActionContext::move_to_loot;
            creators["open loot"] = &ActionContext::open_loot;
            creators["guard"] = &ActionContext::guard;
            creators["move out of enemy contact"] = &ActionContext::move_out_of_enemy_contact;
            creators["set facing"] = &ActionContext::set_facing;
            creators["attack duel opponent"] = &ActionContext::attack_duel_opponent;
            creators["drop target"] = &ActionContext::drop_target;
            creators["leave combat"] = &ActionContext::leave_combat;
            creators["check mail"] = &ActionContext::check_mail;
            creators["say"] = &ActionContext::say;
			creators["mount"] = &ActionContext::mount;
			creators["random bot update"] = &ActionContext::random_bot_update;
			creators["reveal gathering item"] = &ActionContext::reveal_gathering_item;
			creators["delay"] = &ActionContext::delay;
            creators["avoid aoe"] = &ActionContext::avoid_aoe;
            creators["try to get boss ai"] = &ActionContext::try_to_get_boss_ai;
            creators["toggle pet spell"] = &ActionContext::toggle_pet_spell;
            creators["grobbulus go behind the boss"] = &ActionContext::go_behind_the_boss;

            creators["rotate grobbulus"] = &ActionContext::rotate_grobbulus;
            creators["grobbulus move center"] = &ActionContext::grobbulus_move_center;

            creators["heigan dance melee"] = &ActionContext::heigan_dance_melee;
            creators["heigan dance ranged"] = &ActionContext::heigan_dance_ranged;

            creators["thaddius attack nearest pet"] = &ActionContext::thaddius_attack_nearest_pet;
            creators["thaddius melee to place"] = &ActionContext::thaddius_tank_to_place;
            creators["thaddius ranged to place"] = &ActionContext::thaddius_ranged_to_place;
            creators["thaddius move to platform"] = &ActionContext::thaddius_move_to_platform;
            creators["thaddius move polarity"] = &ActionContext::thaddius_move_polarity;

            creators["razuvious use obedience crystal"] = &ActionContext::razuvious_use_obedience_crystal;
            creators["razuvious target"] = &ActionContext::razuvious_target;

            creators["horseman attract alternatively"] = &ActionContext::horseman_attract_alternatively;
            creators["horseman attack in order"] = &ActionContext::horseman_attack_in_order;
            
            creators["sapphiron ground main tank position"] = &ActionContext::sapphiron_ground_main_tank_position;
            creators["sapphiron ground position"] = &ActionContext::sapphiron_ground_position;
            creators["sapphiron flight position"] = &ActionContext::sapphiron_flight_position;
            creators["sapphiron avoid chill"] = &ActionContext::sapphiron_avoid_chill;

            creators["kel'thuzad choose target"] = &ActionContext::kelthuzad_choose_target;
            creators["kel'thuzad position"] = &ActionContext::kelthuzad_position;

            creators["anub'rekhan choose target"] = &ActionContext::anubrekhan_choose_target;
            creators["anub'rekhan position"] = &ActionContext::anubrekhan_position;

            creators["gluth choose target"] = &ActionContext::gluth_choose_target;
            creators["gluth position"] = &ActionContext::gluth_position;
            creators["gluth slowdown"] = &ActionContext::gluth_slowdown;

            creators["loatheb position"] = &ActionContext::loatheb_position;
            creators["loatheb choose target"] = &ActionContext::loatheb_choose_target;
        }

    private:
        static Action* check_mail(PlayerbotAI* ai) { return new CheckMailAction(ai); }
        static Action* drop_target(PlayerbotAI* ai) { return new DropTargetAction(ai); }
        static Action* leave_combat(PlayerbotAI* ai) { return new LeaveCombatAction(ai); }
        static Action* attack_duel_opponent(PlayerbotAI* ai) { return new AttackDuelOpponentAction(ai); }
        static Action* guard(PlayerbotAI* ai) { return new GuardAction(ai); }
        static Action* open_loot(PlayerbotAI* ai) { return new OpenLootAction(ai); }
        static Action* move_to_loot(PlayerbotAI* ai) { return new MoveToLootAction(ai); }
        static Action* move_random(PlayerbotAI* ai) { return new MoveRandomAction(ai); }
        static Action* shoot(PlayerbotAI* ai) { return new CastShootAction(ai); }
        static Action* melee(PlayerbotAI* ai) { return new MeleeAction(ai); }
        static Action* ReachSpell(PlayerbotAI* ai) { return new ReachSpellAction(ai); }
        static Action* ReachHeal(PlayerbotAI* ai) { return new ReachHealAction(ai); }
        static Action* ReachMelee(PlayerbotAI* ai) { return new ReachMeleeAction(ai); }
        static Action* ReachPartyMemberToHeal(PlayerbotAI* ai) { return new ReachPartyMemberToHealAction(ai); }
        static Action* ReachPartyMemberToResurrect(PlayerbotAI* ai) { return new ReachPartyMemberToResurrectAction(ai); }
        static Action* flee(PlayerbotAI* ai) { return new FleeAction(ai); }
        static Action* gift_of_the_naaru(PlayerbotAI* ai) { return new CastGiftOfTheNaaruAction(ai); }
        static Action* lifeblood(PlayerbotAI* ai) { return new CastLifeBloodAction(ai); }
        static Action* arcane_torrent(PlayerbotAI* ai) { return new CastArcaneTorrentAction(ai); }
        static Action* end_pull(PlayerbotAI* ai) { return new ChangeCombatStrategyAction(ai, "-pull"); }

        static Action* emote(PlayerbotAI* ai) { return new EmoteAction(ai); }
        static Action* suggest_what_to_do(PlayerbotAI* ai) { return new SuggestWhatToDoAction(ai); }
        static Action* attack_anything(PlayerbotAI* ai) { return new AttackAnythingAction(ai); }
        static Action* attack_least_hp_target(PlayerbotAI* ai) { return new AttackLeastHpTargetAction(ai); }
        static Action* enemy_player_target(PlayerbotAI* ai) { return new AttackEnemyPlayerAction(ai); }
        static Action* stay(PlayerbotAI* ai) { return new StayAction(ai); }
        static Action* runaway(PlayerbotAI* ai) { return new RunAwayAction(ai); }
        static Action* follow(PlayerbotAI* ai) { return new FollowAction(ai); }
        static Action* add_gathering_loot(PlayerbotAI* ai) { return new AddGatheringLootAction(ai); }
        static Action* add_loot(PlayerbotAI* ai) { return new AddLootAction(ai); }
        static Action* add_all_loot(PlayerbotAI* ai) { return new AddAllLootAction(ai); }
        static Action* loot(PlayerbotAI* ai) { return new LootAction(ai); }
        static Action* dps_assist(PlayerbotAI* ai) { return new DpsAssistAction(ai); }
        static Action* attack_rti_target(PlayerbotAI* ai) { return new AttackRtiTargetAction(ai); }
        static Action* tank_assist(PlayerbotAI* ai) { return new TankAssistAction(ai); }
        static Action* drink(PlayerbotAI* ai) { return new DrinkAction(ai); }
        static Action* food(PlayerbotAI* ai) { return new EatAction(ai); }
        static Action* mana_potion(PlayerbotAI* ai) { return new UseManaPotion(ai); }
        static Action* healing_potion(PlayerbotAI* ai) { return new UseHealingPotion(ai); }
        static Action* healthstone(PlayerbotAI* ai) { return new UseItemAction(ai, "healthstone"); }
        static Action* move_out_of_enemy_contact(PlayerbotAI* ai) { return new MoveOutOfEnemyContactAction(ai); }
        static Action* set_facing(PlayerbotAI* ai) { return new SetFacingTargetAction(ai); }
        static Action* say(PlayerbotAI* ai) { return new SayAction(ai); }
		static Action* mount(PlayerbotAI *ai) { return new CastSpellAction(ai,"mount"); }
		static Action* random_bot_update(PlayerbotAI* ai) { return new RandomBotUpdateAction(ai); }
		static Action* reveal_gathering_item(PlayerbotAI* ai) { return new RevealGatheringItemAction(ai); }
		static Action* delay(PlayerbotAI* ai) { return new DelayAction(ai); }
        static Action* avoid_aoe(PlayerbotAI* ai) { return new AvoidAOEAction(ai); }
        static Action* try_to_get_boss_ai(PlayerbotAI* ai) { return new TryToGetBossAIAction(ai); }
        static Action* toggle_pet_spell(PlayerbotAI* ai) { return new TogglePetSpellAutoCastAction(ai); }
        static Action* go_behind_the_boss(PlayerbotAI* ai) { return new GoBehindTheBossAction(ai); }
        static Action* rotate_grobbulus(PlayerbotAI* ai) { return new RotateGrobbulusAction(ai); }
        static Action* grobbulus_move_center(PlayerbotAI* ai) { return new GrobblulusMoveCenterAction(ai); }
        static Action* heigan_dance_melee(PlayerbotAI* ai) { return new HeiganDanceMeleeAction(ai); }
        static Action* heigan_dance_ranged(PlayerbotAI* ai) { return new HeiganDanceRangedAction(ai); }
        static Action* thaddius_attack_nearest_pet(PlayerbotAI* ai) { return new ThaddiusAttackNearestPetAction(ai); }
        static Action* thaddius_tank_to_place(PlayerbotAI* ai) { return new ThaddiusMeleeToPlaceAction(ai); }
        static Action* thaddius_ranged_to_place(PlayerbotAI* ai) { return new ThaddiusRangedToPlaceAction(ai); }
        static Action* thaddius_move_to_platform(PlayerbotAI* ai) { return new ThaddiusMoveToPlatformAction(ai); }
        static Action* thaddius_move_polarity(PlayerbotAI* ai) { return new ThaddiusMovePolarityAction(ai); }
        static Action* razuvious_target(PlayerbotAI* ai) { return new RazuviousTargetAction(ai); }
        static Action* razuvious_use_obedience_crystal(PlayerbotAI* ai) { return new RazuviousUseObedienceCrystalAction(ai); }
        static Action* horseman_attract_alternatively(PlayerbotAI* ai) { return new HorsemanAttractAlternativelyAction(ai); }
        static Action* horseman_attack_in_order(PlayerbotAI* ai) { return new HorsemanAttactInOrderAction(ai); }
        static Action* sapphiron_ground_main_tank_position(PlayerbotAI* ai) { return new SapphironGroundMainTankPositionAction(ai); }
        static Action* sapphiron_ground_position(PlayerbotAI* ai) { return new SapphironGroundPositionAction(ai); }
        static Action* sapphiron_flight_position(PlayerbotAI* ai) { return new SapphironFlightPositionAction(ai); }
        static Action* sapphiron_avoid_chill(PlayerbotAI* ai) { return new SapphironAvoidChillAction(ai); }
        static Action* kelthuzad_choose_target(PlayerbotAI* ai) { return new KelthuzadChooseTargetAction(ai); }
        static Action* kelthuzad_position(PlayerbotAI* ai) { return new KelthuzadPositionAction(ai); }
        static Action* anubrekhan_choose_target(PlayerbotAI* ai) { return new AnubrekhanChooseTargetAction(ai); }
        static Action* anubrekhan_position(PlayerbotAI* ai) { return new AnubrekhanPositionAction(ai); }
        static Action* gluth_choose_target(PlayerbotAI* ai) { return new GluthChooseTargetAction(ai); }
        static Action* gluth_position(PlayerbotAI* ai) { return new GluthPositionAction(ai); }
        static Action* gluth_slowdown(PlayerbotAI* ai) { return new GluthSlowdownAction(ai); }
        static Action* loatheb_position(PlayerbotAI* ai) { return new LoathebPositionAction(ai); }
        static Action* loatheb_choose_target(PlayerbotAI* ai) { return new LoathebChooseTargetAction(ai); }
    };

};
