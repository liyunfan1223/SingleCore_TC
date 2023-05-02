#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "HealShamanStrategy.h"

using namespace ai;

class HealShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    HealShamanStrategyActionNodeFactory()
    {
        creators["earthliving weapon"] = &earthliving_weapon;
        creators["frostbrand weapon"] = &frostbrand_weapon;
        creators["mana tide totem"] = &mana_tide_totem;
    }
private:
    static ActionNode* earthliving_weapon(PlayerbotAI* ai)
    {
        return new ActionNode ("earthliving weapon",
            /*P*/ NULL,
            /*A*/ NULL,
            // /*A*/ NextAction::array(0, new NextAction("flametongue weapon"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* frostbrand_weapon(PlayerbotAI* ai)
    {
        return new ActionNode ("frostbrand weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flametongue weapon"), NULL),
            /*C*/ NULL);
	}
    static ActionNode* mana_tide_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("mana tide totem",
            /*P*/ NULL,
            // /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }

};

HealShamanStrategy::HealShamanStrategy(PlayerbotAI* ai) : GenericShamanStrategy(ai)
{
    actionNodeFactories.Add(new HealShamanStrategyActionNodeFactory());
}

void HealShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"group heal occasion",
		NextAction::array(0, new NextAction("chain heal", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
		NextAction::array(0, new NextAction("riptide on party", 24.0f), new NextAction("lesser healing wave on party", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
		NextAction::array(0, new NextAction("riptide on party", 18.0f), new NextAction("lesser healing wave on party", 17.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "party member medium health",
		NextAction::array(0, new NextAction("riptide on party", 15.0f), new NextAction("lesser healing wave on party", 14.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        "party member almost full health",
		NextAction::array(0, new NextAction("riptide on party", 12.0f), new NextAction("lesser healing wave on party", 11.0f), NULL)));

	// triggers.push_back(new TriggerNode(
	// 	"medium aoe heal",
	// 	NextAction::array(0, new NextAction("riptide on party", 23.0f), new NextAction("chain heal", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cleanse spirit poison",
        NextAction::array(0, 
            new NextAction("cleanse spirit poison on party", ACTION_DISPEL + 2), 
            new NextAction("cleansing totem", ACTION_DISPEL + 2),
            NULL)));

    triggers.push_back(new TriggerNode(
        "party member cleanse spirit disease",
        NextAction::array(0, 
            new NextAction("cleanse spirit disease on party", ACTION_DISPEL + 2), 
            new NextAction("cleansing totem", ACTION_DISPEL + 1),
        NULL)));

    triggers.push_back(new TriggerNode(
        "party member cleanse spirit curse",
        NextAction::array(0, new NextAction("cleanse spirit curse on party", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "no fire totem",
        NextAction::array(0, new NextAction("fire elemental totem", 11.0f), new NextAction("flametongue totem", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no water totem",
        NextAction::array(0, new NextAction("healing stream totem", 13.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        "earth shield on main tank",
		NextAction::array(0, new NextAction("earth shield on main tank", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
		NextAction::array(0, new NextAction("flee", 49.0f), NULL)));
}
