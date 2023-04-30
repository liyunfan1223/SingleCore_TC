#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockActions.h"
#include "../../Entities/Pet/Pet.h"

using namespace ai;



bool CastImmolateOnAttackerAction::isUseful() {
	return CastDebuffSpellOnAttackerAction::isUseful() && !ai->HasAuraFromBot("unstable affliction", GetTarget());
}