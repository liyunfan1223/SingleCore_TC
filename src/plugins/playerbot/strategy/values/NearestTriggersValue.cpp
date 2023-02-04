#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "NearestTriggersValue.h"

#include "../../../Grids/Notifiers/GridNotifiers.h"
#include "../../../Grids/Notifiers/GridNotifiersImpl.h"
#include "../../../Grids/Cells/CellImpl.h"


using namespace ai;
using namespace Trinity;

void NearestTriggersValue::FindUnits(list<Unit*> &targets)
{
    Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(bot, bot, range);
    Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(bot, targets, u_check);
    bot->VisitNearbyObject(range, searcher);
}

bool NearestTriggersValue::AcceptUnit(Unit* unit)
{
    return dynamic_cast<Creature*>(unit) && dynamic_cast<Creature*>(unit)->IsTrigger();
}
