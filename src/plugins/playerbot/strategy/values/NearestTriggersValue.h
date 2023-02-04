#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class NearestTriggersValue : public NearestUnitsValue
	{
	public:
        NearestTriggersValue(PlayerbotAI* ai, float range = 12.0f) :
            NearestUnitsValue(ai, range) {}

    protected:
        void FindUnits(list<Unit*> &targets);
        bool AcceptUnit(Unit* unit);
	};
}
