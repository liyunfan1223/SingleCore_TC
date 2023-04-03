#pragma once
#include "../Value.h"

namespace ai
{
    class ThreatValue : public Uint8CalculatedValue, public Qualified
	{
	public:
        ThreatValue(PlayerbotAI* ai) : Uint8CalculatedValue(ai) {}

    public:
    	virtual uint8 Calculate();

    protected:
    	uint8 Calculate(Unit* target);
    };

    class NeglectThreatResetValue : public ManualSetValue<bool>
    {
    public:
        NeglectThreatResetValue(PlayerbotAI* ai, bool defaultValue = false, string name = "neglect threat") :
            ManualSetValue<bool>(ai, defaultValue, name) {}
        virtual bool Get() {
            bool ret = value;
            Reset();
            return ret; 
        }
    };
}
