#pragma once
#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "AoeAuraToAvoidValue.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

Aura* AoeAuraToAvoidValue::Calculate()
{
    Unit::AuraApplicationMap& map = bot->GetAppliedAuras();
	for (Unit::AuraApplicationMap::iterator i = map.begin(); i != map.end(); ++i)
	{
		Aura * aura  = i->second->GetBase();
		if (!aura)
			continue;
		AuraObjectType type = aura->GetType();
		if (type != DYNOBJ_AURA_TYPE) {
			continue;
		}
		
		bool IsPositive = aura->GetSpellInfo()->IsPositive();
		if (IsPositive) {
			continue;
		}

		const string auraName = aura->GetSpellInfo()->SpellName[0];
		DynamicObject* owner = aura->GetDynobjOwner();
		double radius = owner->GetRadius();
		int32_t duration = owner->GetDuration();
		sLog->outMessage("playerbot", LOG_LEVEL_DEBUG, "bot: %s triggerd avoid aoe: %s, radius: %.4f, duration: %d", 
			bot->GetName().c_str(), auraName.c_str(), radius, duration);
		return aura;
	}
    return NULL;
}