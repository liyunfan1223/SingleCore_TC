#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    class PartyMemberToDispel : public PartyMemberValue, public Qualified
	{
	public:
        PartyMemberToDispel(PlayerbotAI* ai) : 
          PartyMemberValue(ai) {}
    
    protected:
        virtual Unit* Calculate();
	};
}
