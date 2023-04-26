#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestActions.h"

using namespace ai;


NextAction** CastAbolishDiseaseAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("cure disease"), NULL), CastSpellAction::getAlternatives());
}

NextAction** CastAbolishDiseaseOnPartyAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("cure disease on party"), NULL), CastSpellAction::getAlternatives());
}

Unit* CastPowerWordShieldOnAlmostFullHealthBelow::GetTarget()
{
    Group *group = bot->GetGroup();
    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next())
    {
        Player* player = gref->GetSource();
        if (!player)
            continue;
        if (player->isDead()) {
            continue;
        }
        if (player->GetHealthPct() > sPlayerbotAIConfig.almostFullHealth) {
            continue;
        }
        if (player->GetDistance2d(bot) > sPlayerbotAIConfig.spellDistance) {
            continue;
        }
        if (ai->HasAnyAuraOf(player, "weakened soul", "power word: shield", NULL)) {
            continue;
        }
        return player;
    }
    return NULL;
}

bool CastPowerWordShieldOnAlmostFullHealthBelow::isUseful()
{
    Group *group = bot->GetGroup();
    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next())
    {
        Player* player = gref->GetSource();
        if (!player)
            continue;
        if (player->isDead()) {
            continue;
        }
        if (player->GetHealthPct() > sPlayerbotAIConfig.almostFullHealth) {
            continue;
        }
        if (player->GetDistance2d(bot) > sPlayerbotAIConfig.spellDistance) {
            continue;
        }
        if (ai->HasAnyAuraOf(player, "weakened soul", "power word: shield", NULL)) {
            continue;
        }
        return true;
    }
    return false;
}