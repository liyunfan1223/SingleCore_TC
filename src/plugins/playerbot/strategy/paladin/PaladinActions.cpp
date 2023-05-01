#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinActions.h"

using namespace ai;

Unit* CastRighteousDefenseAction::GetTarget()
{
    Unit* current_target = AI_VALUE(Unit*, "current target");
    if (!current_target) {
        return NULL;
    }
    return current_target->GetVictim();
}