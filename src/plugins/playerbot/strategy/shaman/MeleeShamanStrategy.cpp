#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "MeleeShamanStrategy.h"

using namespace ai;

class MeleeShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    MeleeShamanStrategyActionNodeFactory()
    {
        creators["stormstrike"] = &stormstrike;
        creators["lava lash"] = &lava_lash;
        creators["magma totem"] = &magma_totem;
    }
private:
    static ActionNode* stormstrike(PlayerbotAI* ai)
    {
        return new ActionNode ("stormstrike",
            /*P*/ NULL,
            // /*A*/ NextAction::array(0, new NextAction("lava lash"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* lava_lash(PlayerbotAI* ai)
    {
        return new ActionNode ("lava lash",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* magma_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("magma totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("searing totem"), NULL),
            /*C*/ NULL);
    }
};

MeleeShamanStrategy::MeleeShamanStrategy(PlayerbotAI* ai) : GenericShamanStrategy(ai)
{
    actionNodeFactories.Add(new MeleeShamanStrategyActionNodeFactory());
}

NextAction** MeleeShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, 
        new NextAction("stormstrike", ACTION_NORMAL + 6), 
        new NextAction("earth shock", ACTION_NORMAL + 2), 
        new NextAction("stormstrike", ACTION_NORMAL + 1), 
        new NextAction("melee", ACTION_NORMAL), 
        NULL);
}

void MeleeShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "flame shock",
        NextAction::array(0, new NextAction("flame shock", 24.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_NORMAL + 7), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "enemy too close for melee",
    //     NextAction::array(0, new NextAction("move out of enemy contact", ACTION_NORMAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "strength of earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_LIGHT_HEAL), NULL)));
    
    triggers.push_back(new TriggerNode(
        "no fire totem",
        NextAction::array(0, new NextAction("reach melee", 23.0f), new NextAction("magma totem", 22.0f), NULL)));
}

void MeleeAoeShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("reach melee", ACTION_NORMAL + 8), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "magma totem",
    //     NextAction::array(0, new NextAction("magma totem", 26.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "medium aoe",
    //     NextAction::array(0, new NextAction("fire nova totem", 25.0f), NULL)));
}
