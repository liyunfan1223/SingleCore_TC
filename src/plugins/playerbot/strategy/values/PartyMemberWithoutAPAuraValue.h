#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class PartyMemberWithoutAPAuraValue : public PartyMemberValue, public Qualified
	{
	public:
        PartyMemberWithoutAPAuraValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
          PartyMemberValue(ai) {}
          
    protected:
        virtual Unit* Calculate();
	};
}