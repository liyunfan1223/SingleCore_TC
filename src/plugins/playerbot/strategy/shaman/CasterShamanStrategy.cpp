#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "CasterShamanStrategy.h"

using namespace ai;

class CasterShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    CasterShamanStrategyActionNodeFactory()
    {
        creators["magma totem"] = &magma_totem;
        creators["totem of wrath"] = &totem_of_wrath;
    }
private:
    static ActionNode* magma_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("magma totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* totem_of_wrath(PlayerbotAI* ai)
    {
        return new ActionNode ("totem of wrath",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flametongue totem"), NULL),
            /*C*/ NULL);
    }
};

CasterShamanStrategy::CasterShamanStrategy(PlayerbotAI* ai) : GenericShamanStrategy(ai)
{
    actionNodeFactories.Add(new CasterShamanStrategyActionNodeFactory());
}

NextAction** CasterShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, 
        new NextAction("lava burst", 11.0f),
        new NextAction("lightning bolt", 10.0f), 
        NULL);
}

void CasterShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", 23.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "searing totem",
    //     NextAction::array(0, new NextAction("searing totem", 19.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "flame shock",
        NextAction::array(0, new NextAction("flame shock", 20.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "shock",
    //     NextAction::array(0, new NextAction("earth shock", 20.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "frost shock snare",
    //     NextAction::array(0, new NextAction("frost shock", 21.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "medium aoe",
    //     NextAction::array(0, new NextAction("fire nova", ACTION_NORMAL + 2), NULL)));
    
    triggers.push_back(new TriggerNode(
        "no fire totem",
        NextAction::array(0, new NextAction("totem of wrath", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
		NextAction::array(0, new NextAction("flee", 49.0f), NULL)));
}

void CasterAoeShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0, new NextAction("chain lightning", 25.0f), NULL)));       
}
