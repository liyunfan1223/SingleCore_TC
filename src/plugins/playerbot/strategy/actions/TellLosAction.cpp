#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GridDefines.h"
#include "TellLosAction.h"


using namespace ai;

bool TellLosAction::Execute(Event event)
{
    string param = event.getParam();

    if (param.empty() || param == "targets")
    {
        list<ObjectGuid> targets = *context->GetValue<list<ObjectGuid> >("possible targets");
        ListUnits("--- Targets ---", targets);
    }

    if (param.empty() || param == "npcs")
    {
        list<ObjectGuid> npcs = *context->GetValue<list<ObjectGuid> >("nearest npcs");
        ListUnits("--- NPCs ---", npcs);
    }

    if (param.empty() || param == "corpses")
    {
        list<ObjectGuid> corpses = *context->GetValue<list<ObjectGuid> >("nearest corpses");
        ListUnits("--- Corpses ---", corpses);
    }

    if (param.empty() || param == "gos" || param == "game objects")
    {
        list<ObjectGuid> gos = *context->GetValue<list<ObjectGuid> >("nearest game objects");
        ListGameObjects("--- Game objects ---", gos);
    }

    return true;
}

void TellLosAction::ListUnits(string title, list<ObjectGuid> units)
{
    ai->TellMaster(title);

    for (list<ObjectGuid>::iterator i = units.begin(); i != units.end(); i++)
    {
        Unit* unit = ai->GetUnit(*i);
        if (unit)
            ai->TellMaster(unit->GetName());
    }

}
void TellLosAction::ListGameObjects(string title, list<ObjectGuid> gos)
{
    ai->TellMaster(title);

    for (list<ObjectGuid>::iterator i = gos.begin(); i != gos.end(); i++)
    {
        GameObject* go = ai->GetGameObject(*i);
        if (go)
            ai->TellMaster(chat->formatGameobject(go));
    }
}

bool TellAuraAction::Execute(Event event)
{
    ai->TellMaster("--- Auras ---");
    sLog->outMessage("playerbot", LOG_LEVEL_DEBUG, "--- Auras ---");
    Unit::AuraApplicationMap& map = bot->GetAppliedAuras();
	for (Unit::AuraApplicationMap::iterator i = map.begin(); i != map.end(); ++i)
	{
		Aura * aura  = i->second->GetBase();
		if (!aura)
			continue;

		const string auraName = aura->GetSpellInfo()->SpellName[0];
        sLog->outMessage("playerbot", LOG_LEVEL_DEBUG, "Info of Aura - name: " + auraName);
		AuraObjectType type = aura->GetType();
		WorldObject* owner = aura->GetOwner();
        string owner_name = owner ? owner->GetName() : "unknown";
        float distance = bot->GetDistance2d(owner);
        Unit* caster = aura->GetCaster();
        string caster_name = caster ? caster->GetName() : "unknown";
        bool is_area = aura->IsArea();
        int32 duration = aura->GetDuration();
        const SpellInfo* spellInfo = aura->GetSpellInfo();
        int32 spellId = aura->GetSpellInfo()->Id;
        bool isPositive = aura->GetSpellInfo()->IsPositive();
        sLog->outMessage("playerbot", LOG_LEVEL_DEBUG, "Info of Aura - name: " + auraName +
                       " caster: " + caster_name + 
                       " type: " + to_string(type) + 
                       " owner: " + owner_name + 
                       " distance: " + to_string(distance) +
                       " isArea: " + to_string(is_area) +
                       " duration: " + to_string(duration) +
                       " spellId: " + to_string(spellId) +
                       " isPositive: " + to_string(isPositive));

		ai->TellMaster("Info of Aura - name: " + auraName +
                       " caster: " + caster_name + 
                       " type: " + to_string(type) + 
                       " owner: " + owner_name + 
                       " distance: " + to_string(distance) +
                       " isArea: " + to_string(is_area) +
                       " duration: " + to_string(duration) +
                       " spellId: " + to_string(spellId) +
                       " isPositive: " + to_string(isPositive));

        if (type == DYNOBJ_AURA_TYPE) {
            DynamicObject* dyn_owner = aura->GetDynobjOwner();
            float radius = dyn_owner->GetRadius();
            int32 spellId = dyn_owner->GetSpellId();
            int32 duration = dyn_owner->GetDuration();
            sLog->outMessage("playerbot", LOG_LEVEL_DEBUG, string("Info of DynamicObject -") +
                           " name: " + dyn_owner->GetName() + 
                           " radius: " + to_string(radius) +
                           " spell id: " + to_string(spellId) +
                           " duration: " + to_string(duration));

            ai->TellMaster(string("Info of DynamicObject -") +
                           " name: " + dyn_owner->GetName() + 
                           " radius: " + to_string(radius) +
                           " spell id: " + to_string(spellId) +
                           " duration: " + to_string(duration));
        }
	}
	return true;
}