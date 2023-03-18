#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "TotemsShamanStrategy.h"

using namespace ai;

TotemsShamanStrategy::TotemsShamanStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
}

void TotemsShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    // GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "wrath of air totem",
        NextAction::array(0, new NextAction("wrath of air totem", 13.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no water totem",
        NextAction::array(0, new NextAction("healing stream totem", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "strength of earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no fire totem",
        NextAction::array(0, new NextAction("flametongue totem", 10.0f), NULL)));
}
