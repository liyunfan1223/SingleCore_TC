#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PartyMemberWithoutAuraValue.h"
#include "../../../Entities/Pet/Pet.h"

using namespace ai;

class PlayerWithoutAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutAuraPredicate(PlayerbotAI* ai, string aurastr) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), aurastr(aurastr) {
            int pos;
            while((pos = aurastr.find("::")) != string::npos) {
                auras.push_back(aurastr.substr(0, pos));
                aurastr = aurastr.substr(pos + 2);
            }
            auras.push_back(aurastr);
        }

public:
    virtual bool Check(Unit* unit)
    {
        for (string aura : auras) {
            if (ai->HasAura(aura, unit)) {
                return false;
            }
        }
        return unit->IsAlive();
    }

private:
    string aurastr;
    vector<string> auras;
};

Unit* PartyMemberWithoutAuraValue::Calculate()
{
	PlayerWithoutAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}
