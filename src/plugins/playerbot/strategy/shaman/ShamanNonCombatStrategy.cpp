#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "ShamanNonCombatStrategy.h"

using namespace ai;

void ShamanNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
		"party member to resurrect",
		NextAction::array(0, new NextAction("ancestral spirit", ACTION_HIGH + 9), NULL)));

	triggers.push_back(new TriggerNode(
		"water breathing",
		NextAction::array(0, new NextAction("water breathing", 12.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"water walking",
		NextAction::array(0, new NextAction("water walking", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "water breathing on party",
        NextAction::array(0, new NextAction("water breathing on party", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "water walking on party",
        NextAction::array(0, new NextAction("water walking on party", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("healing wave on party", 27.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", 26.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member medium health",
		NextAction::array(0, new NextAction("healing wave on party", 25.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member almost full health",
		NextAction::array(0, new NextAction("healing wave on party", 24.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("chain heal", 27.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"in battleground without flag",
		NextAction::array(0, new NextAction("mount", 1.0f), NULL)));

	// triggers.push_back(new TriggerNode(
	// 	"cure poison",
	// 	NextAction::array(0, new NextAction("cure poison", 21.0f), NULL)));

	// triggers.push_back(new TriggerNode(
	// 	"party member cure poison",
	// 	NextAction::array(0, new NextAction("cure poison on party", 21.0f), NULL)));

	// triggers.push_back(new TriggerNode(
	// 	"cure disease",
	// 	NextAction::array(0, new NextAction("cure disease", 31.0f), NULL)));

	// triggers.push_back(new TriggerNode(
	// 	"party member cure disease",
	// 	NextAction::array(0, new NextAction("cure disease on party", 30.0f), NULL)));
}

void ShamanNonCombatStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    NonCombatStrategy::InitMultipliers(multipliers);
}

