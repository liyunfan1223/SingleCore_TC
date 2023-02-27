#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "HunterTriggers.h"
#include "HunterActions.h"

using namespace ai;

bool HunterNoStingsActiveTrigger::IsActive()
{
	Unit* target = AI_VALUE(Unit*, "current target");
    /// TODO: change HasAura to HasAuraFromBot
    return target && AI_VALUE2(uint8, "health", "current target") > 40 &&
        !ai->HasAuraFromBot("serpent sting", target) &&
        !ai->HasAuraFromBot("scorpid sting", target) &&
        !ai->HasAuraFromBot("viper sting", target);
}

bool HuntersPetDeadTrigger::IsActive()
{
    Unit* pet = AI_VALUE(Unit*, "pet target");
    return pet && AI_VALUE2(bool, "dead", "pet target") && !AI_VALUE2(bool, "mounted", "self target");
}


bool HuntersPetLowHealthTrigger::IsActive()
{
    Unit* pet = AI_VALUE(Unit*, "pet target");
    return pet && AI_VALUE2(uint8, "health", "pet target") < 40 &&
        !AI_VALUE2(bool, "dead", "pet target") && !AI_VALUE2(bool, "mounted", "self target");
}
