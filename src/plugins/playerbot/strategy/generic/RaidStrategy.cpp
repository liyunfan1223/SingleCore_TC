#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RaidStrategy.h"
#include "MovementActions.h"
#include "ScriptedCreature.h"
#include "RaidNaxxAction.h"
#include "GenericSpellActions.h"
#include "ChooseTargetActions.h"
#include "ReachTargetActions.h"
#include "UseMeetingStoneAction.h"
#include "FollowActions.h"
#include "ShamanActions.h"
#include "PriestActions.h"
#include "DKActions.h"
#include "HunterActions.h"
#include "MageActions.h"
#include "RogueActions.h"
#include "DruidActions.h"
#include "PaladinActions.h"
#include "WarriorActions.h"

using namespace ai;

float HeiganDanceMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "heigan the unclean");
    if (!boss) {
        return 1.0f;
    }
    BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    uint32 curr_phase = eventMap->GetPhaseMask();
	uint32 curr_dance = eventMap->GetNextEventTime(4);
	uint32 curr_timer = eventMap->GetTimer();
	if (curr_phase != 2 && (int32)curr_dance - curr_timer >= 3000) {
		return 1.0f;
	}
	if (dynamic_cast<HeiganDanceAction*>(action) || dynamic_cast<CurePartyMemberAction*>(action)) {
		return 1.0f;
	}
	return 0.0f;
}

float LoathebGenericMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "loatheb");
    if (!boss) {
		// bot->Yell("Can\'t find Loatheb...", LANG_UNIVERSAL);
        return 1.0f;
    }
	context->GetValue<bool>("neglect threat")->Set(true);
	if (ai->GetCurrentState() == BOT_STATE_COMBAT && 
		(dynamic_cast<AttackLeastHpTargetAction*>(action) || 
		 dynamic_cast<TankAssistAction*>(action) ||
		 dynamic_cast<CastDebuffSpellOnAttackerAction*>(action) ||
		 dynamic_cast<FleeAction*>(action))) {
		return 0.0f;
	}
	if (!dynamic_cast<CastHealingSpellAction*>(action)) {
		return 1.0f;
	}
	// bot->Yell("It\'s a healing spell!", LANG_UNIVERSAL);
	Aura* aura = ai->GetAura("necrotic aura", bot);
	if (!aura || aura->GetDuration() <= 1500) {
		return 1.0f;
	}
	return 0.0f;
}

float ThaddiusGenericMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "thaddius");
	if (!boss) {
        return 1.0f;
    }
	BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    uint32 curr_phase = eventMap->GetPhaseMask();
	// pet phase
	if (curr_phase == 2 && 
		( dynamic_cast<AttackLeastHpTargetAction*>(action) || 
		dynamic_cast<TankAssistAction*>(action) || 
		dynamic_cast<CastDebuffSpellOnAttackerAction*>(action) ||
		dynamic_cast<ReachHealAction*>(action) || 
		dynamic_cast<BuffOnMainTankAction*>(action) )) {
		return 0.0f;
	}
	// die at the same time
	Unit* target = AI_VALUE(Unit*, "current target");
	Unit* feugen = AI_VALUE2(Unit*, "find target", "feugen");
    Unit* stalagg = AI_VALUE2(Unit*, "find target", "stalagg");
	if (curr_phase == 2 && target && feugen && stalagg && 
		target->GetHealthPct() <= 40 && 
		(feugen->GetHealthPct() >= target->GetHealthPct() + 3 || stalagg->GetHealthPct() >= target->GetHealthPct() + 3)) {
		if (dynamic_cast<CastSpellAction*>(action) && !dynamic_cast<CastHealingSpellAction*>(action)) {
			return 0.0f;
		}
	}
	// magnetic pull
	// uint32 curr_timer = eventMap->GetTimer();
	// // if (curr_phase == 2 && bot->GetPositionZ() > 312.5f && dynamic_cast<MovementAction*>(action)) {
	// if (curr_phase == 2 && (curr_timer % 20000 >= 18000 || curr_timer % 20000 <= 2000) && dynamic_cast<MovementAction*>(action)) {
	// 	// MotionMaster *mm = bot->GetMotionMaster();
	// 	// mm->Clear();
	// 	return 0.0f;
	// }
	// thaddius phase
	if (curr_phase == 8 && dynamic_cast<FleeAction*>(action)) {
			return 0.0f;
	}
	return 1.0f;
}

float SapphironGenericMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "sapphiron");
	if (!boss) {
        return 1.0f;
    }
	if (dynamic_cast<FollowAction*>(action) || 
		dynamic_cast<CastDeathGripAction*>(action)) {
		return 0.0f;
	}
	BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
    EventMap* eventMap = boss_ai->GetEvents();
    uint32 curr_phase = eventMap->GetPhaseMask();
	uint32 timer = eventMap->GetTimer();
	uint32 explosion = eventMap->GetNextEventTime(10);
	if (curr_phase == 4 && explosion > timer && 
		(dynamic_cast<MovementAction*>(action) && 
		 !dynamic_cast<SapphironFlightPositionAction*>(action) && 
		 !dynamic_cast<SummonAction*>(action))) {
		return 0.0f;
	}
	return 1.0f;
}

float InstructorRazuviousGenericMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "instructor razuvious");
	if (!boss) {
        return 1.0f;
    }
	context->GetValue<bool>("neglect threat")->Set(true);
	if (ai->GetCurrentState() == BOT_STATE_COMBAT &&
	   (dynamic_cast<AttackLeastHpTargetAction*>(action) ||
		dynamic_cast<TankAssistAction*>(action) || 
		dynamic_cast<CastTauntAction*>(action) ||
		dynamic_cast<CastDarkCommandAction*>(action) || 
		dynamic_cast<CastHandOfReckoningAction*>(action) || 
		dynamic_cast<CastGrowlAction*>(action))) {
		return 0.0f;
	}
	return 1.0f;
}

float KelthuzadGenericMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "kel'thuzad");
	if (!boss) {
        return 1.0f;
    }
	if ((dynamic_cast<AttackLeastHpTargetAction*>(action) || 
		 dynamic_cast<TankAssistAction*>(action) || 
		 dynamic_cast<CastDebuffSpellOnAttackerAction*>(action) || 
		 dynamic_cast<FollowAction*>(action) || 
		 dynamic_cast<FleeAction*>(action))) {
		return 0.0f;
	}
	BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
	EventMap* eventMap = boss_ai->GetEvents();
    uint32 curr_phase = eventMap->GetPhaseMask();
	
	if (curr_phase == 1) {
		if (dynamic_cast<CastTotemAction*>(action) || 
			dynamic_cast<CastShadowfiendAction*>(action) ||
			dynamic_cast<CastRaiseDeadAction*>(action) ||
			dynamic_cast<CastFeignDeathAction*>(action) || 
			dynamic_cast<CastInvisibilityAction*>(action) ||
			dynamic_cast<CastVanishAction*>(action)) {
			return 0.0f;
		}
	}
	if (curr_phase == 2) {
		if (dynamic_cast<CastBlizzardAction*>(action) || 
			dynamic_cast<CastFrostNovaAction*>(action)) {
			return 0.0f;
		}
		
	}
	return 1.0f;
}

float AnubrekhanGenericMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "anub'rekhan");
	if (!boss) {
        return 1.0f;
    }
	if ((dynamic_cast<AttackLeastHpTargetAction*>(action) || 
		 dynamic_cast<TankAssistAction*>(action) || 
		 dynamic_cast<FollowAction*>(action))) {
		return 0.0f;
	}
	BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
	EventMap* eventMap = boss_ai->GetEvents();
    uint32 curr_phase = eventMap->GetPhaseMask();
	if (curr_phase == 2) {
		if (dynamic_cast<FleeAction*>(action)) {
			return 0.0f;
		}
	}
	return 1.0f;
}

float FourhorsemanGenericMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "sir zeliek");
	if (!boss) {
        return 1.0f;
    }
	if ((dynamic_cast<AttackLeastHpTargetAction*>(action) || 
		 dynamic_cast<TankAssistAction*>(action))) {
		return 0.0f;
	}
	return 1.0f;
}

float GothikGenericMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "gothik the harvester");
	if (!boss) {
        return 1.0f;
    }
	BossAI* boss_ai = dynamic_cast<BossAI*>(boss->GetAI());
	EventMap* eventMap = boss_ai->GetEvents();
    uint32 curr_phase = eventMap->GetPhaseMask();
	if (curr_phase == 1 && (dynamic_cast<FollowAction*>(action))) {
		return 0.0f;
	}
	if (curr_phase == 1 && (dynamic_cast<AttackAction*>(action))) {
		Unit* target = action->GetTarget();
		if (target == boss) {
			return 0.0f;
		}
	}
	return 1.0f;
}

float GluthGenericMultiplier::GetValue(Action* action)
{
	Unit* boss = AI_VALUE2(Unit*, "find target", "gluth");
	if (!boss) {
        return 1.0f;
    }
	if ((dynamic_cast<AttackLeastHpTargetAction*>(action) || 
		 dynamic_cast<TankAssistAction*>(action) ||
		 dynamic_cast<FleeAction*>(action) || 
		 dynamic_cast<CastDebuffSpellOnAttackerAction*>(action) ||
		 dynamic_cast<CastStarfallAction*>(action))) {
		return 0.0f;
	}
	
	if (ai->IsMainTank(bot)) {
		Aura* aura = ai->GetAuraWithDuration("mortal wound", bot);
		if (aura && aura->GetStackAmount() >= 5) {
			if (dynamic_cast<CastTauntAction*>(action) ||
				dynamic_cast<CastDarkCommandAction*>(action) || 
				dynamic_cast<CastHandOfReckoningAction*>(action) || 
				dynamic_cast<CastGrowlAction*>(action)) {
				return 0.0f;
			}
		}
	}
	return 1.0f;
}

void RaidNaxxGenericStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	// triggers.push_back(new TriggerNode(
	// 	"often", 
	// 	NextAction::array(0, new NextAction("try to get boss ai", ACTION_RAID), NULL)));
	
	// Grobbulus
	triggers.push_back(new TriggerNode(
		"mutating injection", 
		NextAction::array(0, new NextAction("grobbulus go behind the boss", ACTION_RAID + 2), NULL)));
	
	triggers.push_back(new TriggerNode(
		"mutating injection removed", 
		NextAction::array(0, new NextAction("grobbulus move center", ACTION_RAID + 1), NULL)));

	triggers.push_back(new TriggerNode(
		"grobbulus cloud", 
		NextAction::array(0, new NextAction("rotate grobbulus", ACTION_RAID + 1), NULL)));

	// Heigan the Unclean
	triggers.push_back(new TriggerNode(
		"heigan melee", 
		NextAction::array(0, new NextAction("heigan dance melee", ACTION_RAID + 1), NULL)));

	triggers.push_back(new TriggerNode(
		"heigan ranged", 
		NextAction::array(0, new NextAction("heigan dance ranged", ACTION_RAID + 1), NULL)));

	// Thaddius
	triggers.push_back(new TriggerNode(
		"thaddius phase pet", 
		NextAction::array(0, 
			new NextAction("thaddius attack nearest pet", ACTION_RAID + 1), 
			new NextAction("thaddius melee to place", ACTION_RAID),
			new NextAction("thaddius ranged to place", ACTION_RAID),
			NULL)));

	triggers.push_back(new TriggerNode(
		"thaddius phase pet lose aggro", 
		NextAction::array(0, new NextAction("taunt spell", ACTION_RAID + 2), NULL)));

	triggers.push_back(new TriggerNode(
		"thaddius phase transition", 
		NextAction::array(0, new NextAction("thaddius move to platform", ACTION_RAID + 1), NULL)));

	triggers.push_back(new TriggerNode(
		"thaddius phase thaddius", 
		NextAction::array(0, new NextAction("thaddius move polarity", ACTION_RAID + 1), NULL)));

	// Instructor Razuvious
	triggers.push_back(new TriggerNode(
		"razuvious tank", 
		NextAction::array(0, new NextAction("razuvious use obedience crystal", ACTION_RAID + 1), NULL)));
	
	triggers.push_back(new TriggerNode(
		"razuvious nontank", 
		NextAction::array(0, new NextAction("razuvious target", ACTION_RAID + 1), NULL)));

	// four horseman
	triggers.push_back(new TriggerNode(
		"horseman attractors", 
		NextAction::array(0, new NextAction("horseman attract alternatively", ACTION_RAID + 1), NULL)));
	
	triggers.push_back(new TriggerNode(
		"horseman except attractors", 
		NextAction::array(0, new NextAction("horseman attack in order", ACTION_RAID + 1), NULL)));

	// sapphiron
	triggers.push_back(new TriggerNode(
		"sapphiron ground main tank", 
		NextAction::array(0, new NextAction("sapphiron ground main tank position", ACTION_RAID + 1), NULL)));
	
	triggers.push_back(new TriggerNode(
		"sapphiron ground except main tank", 
		NextAction::array(0, new NextAction("sapphiron ground position", ACTION_RAID + 1), NULL)));
	
	triggers.push_back(new TriggerNode(
		"sapphiron flight", 
		NextAction::array(0, new NextAction("sapphiron flight position", ACTION_RAID + 1), NULL)));
	
	triggers.push_back(new TriggerNode(
		"sapphiron chill", 
		NextAction::array(0, new NextAction("sapphiron avoid chill", ACTION_RAID + 1), NULL)));
	
	// Kel'Thuzad
	triggers.push_back(new TriggerNode(
		"kel'thuzad", 
		NextAction::array(0, 
			new NextAction("kel'thuzad choose target", ACTION_RAID + 1), 
   			new NextAction("kel'thuzad position", ACTION_RAID + 1),
		NULL)));

	// Anub'Rekhan
	triggers.push_back(new TriggerNode(
		"anub'rekhan", 
		NextAction::array(0, 
			new NextAction("anub'rekhan choose target", ACTION_RAID + 1), 
   			new NextAction("anub'rekhan position", ACTION_RAID + 1),
		NULL)));

	// Gluth
	triggers.push_back(new TriggerNode(
		"gluth", 
		NextAction::array(0, 
			new NextAction("gluth choose target", ACTION_RAID + 1), 
   			new NextAction("gluth position", ACTION_RAID + 1),
			new NextAction("gluth slowdown", ACTION_RAID),
		NULL)));
	
	triggers.push_back(new TriggerNode(
		"gluth main tank mortal wound", 
		NextAction::array(0, 
			new NextAction("taunt spell", ACTION_RAID + 1), NULL)));
	// Loatheb
	triggers.push_back(new TriggerNode(
		"loatheb", 
		NextAction::array(0, 
			new NextAction("loatheb position", ACTION_RAID + 1),
			new NextAction("loatheb choose target", ACTION_RAID + 1),
			NULL)));
}

void RaidNaxxGenericStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
	multipliers.push_back(new HeiganDanceMultiplier(ai));
	multipliers.push_back(new LoathebGenericMultiplier(ai));
	multipliers.push_back(new ThaddiusGenericMultiplier(ai));
	multipliers.push_back(new SapphironGenericMultiplier(ai));
	multipliers.push_back(new InstructorRazuviousGenericMultiplier(ai));
	multipliers.push_back(new KelthuzadGenericMultiplier(ai));
	multipliers.push_back(new AnubrekhanGenericMultiplier(ai));
	multipliers.push_back(new FourhorsemanGenericMultiplier(ai));
	multipliers.push_back(new GothikGenericMultiplier(ai));
	multipliers.push_back(new GluthGenericMultiplier(ai));
		
}
