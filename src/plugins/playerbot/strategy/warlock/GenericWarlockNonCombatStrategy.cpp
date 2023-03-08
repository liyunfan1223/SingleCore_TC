#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockMultipliers.h"
#include "GenericWarlockNonCombatStrategy.h"

using namespace ai;

class GenericWarlockNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericWarlockNonCombatStrategyActionNodeFactory()
    {
        creators["fel armor"] = &fel_armor;
        creators["demon armor"] = &demon_armor;
        creators["summon felhunter"] = &summon_felhunter;
    }
private:
    static ActionNode* fel_armor(PlayerbotAI* ai)
    {
        return new ActionNode ("fel armor",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("demon armor"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* demon_armor(PlayerbotAI* ai)
    {
        return new ActionNode ("demon armor",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("demon skin"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* summon_felhunter(PlayerbotAI* ai)
    {
        return new ActionNode ("summon felhunter",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("summon imp"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* summon_felguard(PlayerbotAI* ai)
    {
        return new ActionNode ("summon felguard",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("summon voidwalker"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* summon_voidwalker(PlayerbotAI* ai)
    {
        return new ActionNode ("summon voidwalker",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("summon imp"), NULL),
            /*C*/ NULL);
    }
};

GenericWarlockNonCombatStrategy::GenericWarlockNonCombatStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericWarlockNonCombatStrategyActionNodeFactory());
}

void GenericWarlockNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demon armor",
        NextAction::array(0, new NextAction("fel armor", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no healthstone",
		NextAction::array(0, new NextAction("create healthstone", 15.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no firestone",
		NextAction::array(0, new NextAction("create firestone", 14.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no spellstone",
		NextAction::array(0, new NextAction("create spellstone", 13.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "spellstone",
        NextAction::array(0, new NextAction("spellstone", 13.0f), NULL)));

    // triggers.push_back(new TriggerNode(
    //     "no pet",
    //     NextAction::array(0, new NextAction("summon felhunter", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "has pet",
        NextAction::array(0, new NextAction("toggle pet spell", 11.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"in battleground without flag",
		NextAction::array(0, new NextAction("mount", 1.0f), NULL)));
}

SummonImpStrategy::SummonImpStrategy(PlayerbotAI* ai): NonCombatStrategy(ai) {}

void SummonImpStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon imp", 11.0f), NULL)));
}

SummonFelguardStrategy::SummonFelguardStrategy(PlayerbotAI* ai): NonCombatStrategy(ai) {}

void SummonFelguardStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felguard", 11.0f), NULL)));
}

SummonFelhunterStrategy::SummonFelhunterStrategy(PlayerbotAI* ai): NonCombatStrategy(ai) {}

void SummonFelhunterStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felhunter", 11.0f), NULL)));
}