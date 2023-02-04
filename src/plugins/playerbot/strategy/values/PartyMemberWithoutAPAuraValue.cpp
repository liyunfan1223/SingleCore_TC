#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PartyMemberWithoutAPAuraValue.h"
#include "../../../Entities/Pet/Pet.h"

using namespace ai;

class PlayerWithoutAPAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutAPAuraPredicate(PlayerbotAI* ai, string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), aura(aura) {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
            return pet->IsAlive() && !ai->HasAura(aura, pet);
        }
        Player* player = dynamic_cast<Player*>(unit);
        return player->IsAlive() && !ai->HasAura(aura, player) && ((!ai->IsRanged(player) || player->getClass() == CLASS_HUNTER) && !ai->IsHeal(player));
    }

private:
    string aura;
};

Unit* PartyMemberWithoutAPAuraValue::Calculate()
{
	PlayerWithoutAPAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}
