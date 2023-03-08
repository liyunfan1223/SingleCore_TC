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
        NextAction::array(0, new NextAction("wrath of air totem", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mana spring totem",
        NextAction::array(0, new NextAction("healing stream totem", 19.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "strength of earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", 18.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "flametongue totem",
        NextAction::array(0, new NextAction("flametongue totem", 17.0f), NULL)));
}
