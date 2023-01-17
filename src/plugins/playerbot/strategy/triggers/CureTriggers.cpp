#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GenericTriggers.h"
#include "CureTriggers.h"

using namespace ai;

bool NeedCureTrigger::IsActive() 
{
	Unit* target = GetTarget();
	// sLog->outMessage("playerbot", LOG_LEVEL_INFO, "NeedCureTrigger::IsActive()  %d %d %s", dispelType, target ? ai->HasAuraToDispel(target, dispelType) : 0, 
	// 	target ? target->GetName() : "|no target|");
	return target && ai->HasAuraToDispel(target, dispelType);
}

Value<Unit*>* PartyMemberNeedCureTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member to dispel", dispelType);
}
