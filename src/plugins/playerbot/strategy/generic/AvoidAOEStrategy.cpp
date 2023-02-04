#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "AvoidAOEStrategy.h"

using namespace ai;

void AvoidAOEStrategy::InitTriggers(list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "avoid aoe",
        NextAction::array(0, new NextAction("avoid aoe", ACTION_EMERGENCY + 1), NULL)));
}
