#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PartyMemberToHeal.h"
#include "../../PlayerbotAIConfig.h"
#include "../../../Entities/Pet/Pet.h"

using namespace ai;

class IsTargetOfHealingSpell : public SpellEntryPredicate
{
public:
    virtual bool Check(SpellInfo const* spell) {
        for (int i=0; i<3; i++) {
            if (spell->Effects[i].Effect == SPELL_EFFECT_HEAL ||
                spell->Effects[i].Effect == SPELL_EFFECT_HEAL_MAX_HEALTH ||
                spell->Effects[i].Effect == SPELL_EFFECT_HEAL_MECHANICAL ||
                spell->Effects[i].Effect == SPELL_EFFECT_HEAL_PCT)
                return true;
        }
        return false;
    }

};

Unit* PartyMemberToHeal::Calculate()
{

    IsTargetOfHealingSpell predicate;

    Group* group = bot->GetGroup();
    if (!group)
        return bot;

    bool isRaid = bot->GetGroup()->isRaidGroup();
    MinValueCalculator calc(100);
    
    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next())
    {
        Player* player = gref->GetSource();
        if (player && Check(player) && player->IsAlive()) {
            uint8 health = player->GetHealthPct();
            if (isRaid || health < sPlayerbotAIConfig.mediumHealth || !IsTargetOfSpellCast(player, predicate)) {
                if (player->GetDistance2d(bot) > sPlayerbotAIConfig.spellDistance) {
                    calc.probe(health + 30, player);
                } else {
                    calc.probe(health + player->GetDistance2d(bot) / 10, player);
                }

            }
        }

        Pet* pet = player->GetPet();
        if (pet && Check(pet) && pet->IsAlive()) {
            uint8 health = ((Unit*)pet)->GetHealthPct();
            if (isRaid || health < sPlayerbotAIConfig.mediumHealth)
                calc.probe(health + 30, pet);
        }

        Unit* charm = player->GetCharm();
        if (charm && Check(charm) && charm->IsAlive()) {
            uint8 health = charm->GetHealthPct();
            if (isRaid || health < sPlayerbotAIConfig.mediumHealth)
                calc.probe(health, charm);
        }
    }
    return (Unit*)calc.param;
}

bool PartyMemberToHeal::CanHealPet(Pet* pet)
{
    return true;
    // return HUNTER_PET == pet->getPetType();
}
