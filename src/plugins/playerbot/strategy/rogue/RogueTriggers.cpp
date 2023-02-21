#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueTriggers.h"
#include "RogueActions.h"

using namespace ai;

bool MainHandWeaponNoEnchantTrigger::IsActive() {
    Item* const itemForSpell = bot->GetItemByPos( INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND );
    if (!itemForSpell || itemForSpell->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
        return false;
    return true;
}

bool OffHandWeaponNoEnchantTrigger::IsActive() {
    Item* const itemForSpell = bot->GetItemByPos( INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND );
    if (!itemForSpell || itemForSpell->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
        return false;
    return true;
}

bool ExposeArmorTrigger::IsActive() {
    return DebuffTrigger::IsActive() && AI_VALUE2(uint8, "combo", "current target") <= 2;
}