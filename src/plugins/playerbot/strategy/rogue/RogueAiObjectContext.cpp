#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueActions.h"
#include "RogueTriggers.h"
#include "RogueAiObjectContext.h"
#include "DpsRogueStrategy.h"
#include "GenericRogueNonCombatStrategy.h"
#include "../generic/PullStrategy.h"
#include "../NamedObjectContext.h"
#include "AssassinationRogueStrategy.h"

using namespace ai;


namespace ai
{
    namespace rogue
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["dps"] = &rogue::StrategyFactoryInternal::dps;
                creators["melee"] = &rogue::StrategyFactoryInternal::melee;
                creators["nc"] = &rogue::StrategyFactoryInternal::nc;
                creators["pull"] = &rogue::StrategyFactoryInternal::pull;
            }

        private:
            static Strategy* dps(PlayerbotAI* ai) { return new DpsRogueStrategy(ai); }
            static Strategy* melee(PlayerbotAI* ai) { return new AssassinationRogueStrategy(ai); }
            static Strategy* nc(PlayerbotAI* ai) { return new GenericRogueNonCombatStrategy(ai); }
            static Strategy* pull(PlayerbotAI* ai) { return new PullStrategy(ai, "shoot"); }
        };
    };
};

namespace ai
{
    namespace rogue
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["kick"] = &TriggerFactoryInternal::kick;
                creators["rupture"] = &TriggerFactoryInternal::rupture;
                creators["slice and dice"] = &TriggerFactoryInternal::slice_and_dice;
                creators["expose armor"] = &TriggerFactoryInternal::expose_armor;
                creators["kick on enemy healer"] = &TriggerFactoryInternal::kick_on_enemy_healer;
                creators["main hand weapon no enchant"] = &TriggerFactoryInternal::main_hand_weapon_no_enchant;
                creators["off hand weapon no enchant"] = &TriggerFactoryInternal::off_hand_weapon_no_enchant;
                creators["tricks of the trade on main tank"] = &TriggerFactoryInternal::tricks_of_the_trade_on_main_tank;
            }

        private:
            static Trigger* kick(PlayerbotAI* ai) { return new KickInterruptSpellTrigger(ai); }
            static Trigger* rupture(PlayerbotAI* ai) { return new RuptureTrigger(ai); }
            static Trigger* slice_and_dice(PlayerbotAI* ai) { return new SliceAndDiceTrigger(ai); }
            static Trigger* expose_armor(PlayerbotAI* ai) { return new ExposeArmorTrigger(ai); }
            static Trigger* kick_on_enemy_healer(PlayerbotAI* ai) { return new KickInterruptEnemyHealerSpellTrigger(ai); }
            static Trigger* main_hand_weapon_no_enchant(PlayerbotAI* ai) { return new MainHandWeaponNoEnchantTrigger(ai); }
            static Trigger* off_hand_weapon_no_enchant(PlayerbotAI* ai) { return new OffHandWeaponNoEnchantTrigger(ai); }
            static Trigger* tricks_of_the_trade_on_main_tank(PlayerbotAI* ai) { return new TricksOfTheTradeOnMainTankTrigger(ai); }
        };
    };
};


namespace ai
{
    namespace rogue
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["riposte"] = &AiObjectContextInternal::riposte;
                creators["mutilate"] = &AiObjectContextInternal::mutilate;
                creators["sinister strike"] = &AiObjectContextInternal::sinister_strike;
                creators["kidney shot"] = &AiObjectContextInternal::kidney_shot;
                creators["rupture"] = &AiObjectContextInternal::rupture;
                creators["slice and dice"] = &AiObjectContextInternal::slice_and_dice;
                creators["eviscerate"] = &AiObjectContextInternal::eviscerate;
                creators["vanish"] = &AiObjectContextInternal::vanish;
                creators["evasion"] = &AiObjectContextInternal::evasion;
                creators["kick"] = &AiObjectContextInternal::kick;
                creators["feint"] = &AiObjectContextInternal::feint;
                creators["backstab"] = &AiObjectContextInternal::backstab;
                creators["expose armor"] = &AiObjectContextInternal::expose_armor;
                creators["kick on enemy healer"] = &AiObjectContextInternal::kick_on_enemy_healer;
				creators["stealth"] = &AiObjectContextInternal::stealth;
                creators["cancel stealth"] = &AiObjectContextInternal::cancel_stealth;
                creators["use instant poison"] = &AiObjectContextInternal::use_instant_poison;
                creators["use deadly poison"] = &AiObjectContextInternal::use_deadly_poison;
                creators["envenom"] = &AiObjectContextInternal::envenom;
                creators["fan of knives"] = &AiObjectContextInternal::fan_of_knives;
                creators["sprint"] = &AiObjectContextInternal::sprint;
                creators["tricks of the trade on main tank"] = &AiObjectContextInternal::tricks_of_the_trade_on_main_tank;
            }

        private:
            static Action* riposte(PlayerbotAI* ai) { return new CastRiposteAction(ai); }
            static Action* mutilate(PlayerbotAI* ai) { return new CastMutilateAction(ai); }
            static Action* sinister_strike(PlayerbotAI* ai) { return new CastSinisterStrikeAction(ai); }
            static Action* kidney_shot(PlayerbotAI* ai) { return new CastKidneyShotAction(ai); }
            static Action* rupture(PlayerbotAI* ai) { return new CastRuptureAction(ai); }
            static Action* slice_and_dice(PlayerbotAI* ai) { return new CastSliceAndDiceAction(ai); }
            static Action* eviscerate(PlayerbotAI* ai) { return new CastEviscerateAction(ai); }
            static Action* vanish(PlayerbotAI* ai) { return new CastVanishAction(ai); }
            static Action* evasion(PlayerbotAI* ai) { return new CastEvasionAction(ai); }
            static Action* kick(PlayerbotAI* ai) { return new CastKickAction(ai); }
            static Action* feint(PlayerbotAI* ai) { return new CastFeintAction(ai); }
            static Action* backstab(PlayerbotAI* ai) { return new CastBackstabAction(ai); }
            static Action* expose_armor(PlayerbotAI* ai) { return new CastExposeArmorAction(ai); }
            static Action* kick_on_enemy_healer(PlayerbotAI* ai) { return new CastKickOnEnemyHealerAction(ai); }
			static Action* stealth(PlayerbotAI* ai) { return new CastStealthAction(ai); }
            static Action* cancel_stealth(PlayerbotAI* ai) { return new CastCancelStealthAction(ai); }
            static Action* use_instant_poison(PlayerbotAI* ai) { return new UseInstantPoisonAction(ai); }
            static Action* use_deadly_poison(PlayerbotAI* ai) { return new UseDeadlyPoisonAction(ai); }
            static Action* envenom(PlayerbotAI* ai) { return new EnvenomAction(ai); }
            static Action* fan_of_knives(PlayerbotAI* ai) { return new FanOfKnivesAction(ai); }
            static Action* sprint(PlayerbotAI* ai) { return new CastSprintAction(ai); }
            static Action* tricks_of_the_trade_on_main_tank(PlayerbotAI* ai) { return new CastTricksOfTheTradeOnMainTankAction(ai); }
        };
    };
};

RogueAiObjectContext::RogueAiObjectContext(PlayerbotAI* ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::rogue::StrategyFactoryInternal());
    actionContexts.Add(new ai::rogue::AiObjectContextInternal());
    triggerContexts.Add(new ai::rogue::TriggerFactoryInternal());
}
