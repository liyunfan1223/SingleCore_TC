#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PartyMemberWithoutManaAuraValue.h"
#include "../../../Entities/Pet/Pet.h"

using namespace ai;

class PlayerWithoutManaAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutManaAuraPredicate(PlayerbotAI* ai, string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), aura(aura) {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (!pet)
                return false;
            return pet->IsAlive() && !ai->HasAura(aura, pet);
        }
        Player* player = dynamic_cast<Player*>(unit);
        return player->IsAlive() && !ai->HasAura(aura, player) && ((ai->IsRanged(player) && player->getClass() != CLASS_HUNTER) || ai->IsHeal(player));
    }

private:
    string aura;
};

Unit* PartyMemberWithoutManaAuraValue::Calculate()
{
	PlayerWithoutManaAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}
