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
        NextAction::array(0, new NextAction("wrath of air totem", 8.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no water totem",
        NextAction::array(0, new NextAction("mana spring totem", 7.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "strength of earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", 6.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no fire totem",
        NextAction::array(0, new NextAction("flametongue totem", 5.0f), NULL)));
}
