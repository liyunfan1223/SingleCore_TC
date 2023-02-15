#pragma once
#include "../Value.h"

namespace ai
{
    class AoeAuraToAvoidValue : public AuraCalculatedValue, public Qualified
	{
	public:
    	AoeAuraToAvoidValue(PlayerbotAI* ai) : AuraCalculatedValue(ai) {}

    public:
    	virtual Aura* Calculate();
    };
}
