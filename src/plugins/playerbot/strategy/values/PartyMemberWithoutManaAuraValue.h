#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class PartyMemberWithoutManaAuraValue : public PartyMemberValue, public Qualified
	{
	public:
        PartyMemberWithoutManaAuraValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};
}