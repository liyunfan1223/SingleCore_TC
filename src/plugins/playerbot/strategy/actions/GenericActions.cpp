#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GenericActions.h"
#include "Pet.h"

using namespace ai;

bool TogglePetSpellAutoCastAction::Execute(Event event) {
    Pet* pet = bot->GetPet();
    if (!pet) {
        return false;
    }
    for (PetSpellMap::const_iterator itr = pet->m_spells.begin(); itr != pet->m_spells.end(); ++itr)
    {
        if(itr->second.state == PETSPELL_REMOVED)
            continue;

        uint32 spellId = itr->first;
        const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (spellInfo->IsPassive())
            continue;

        // imp's spell, felhunte's intelligence, ghoul's leap
        if (spellId == 4511 || 
            spellId == 54424 || spellId == 57564 || spellId == 57565 || spellId == 57566 || spellId == 57567 || spellId == 47482) {
            pet->ToggleAutocast(spellInfo, false);
        } else {
            pet->ToggleAutocast(spellInfo, true);
        }
    }
    return true; 
}