#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueActions.h"

using namespace ai;

bool UseDeadlyPoisonAction::Execute(Event event) {
    vector<string> poison_suffixs = {" IX", " VIII", " VII", " VI", " V", " IV", " III", " II", ""};
    list<Item*> items;
    string poison_name;
    for (string& suffix: poison_suffixs) {
        poison_name = getName() + suffix;
        items = AI_VALUE2(list<Item*>, "inventory items", poison_name);
        if (!items.empty()) {
            break;
        }
    }
    if (items.empty()) {
        return false;
    }
    return UseItemAuto(*items.begin());
}

bool UseInstantPoisonAction::Execute(Event event) {
    vector<string> poison_suffixs = {" IX", " VIII", " VII", " VI", " V", " IV", " III", " II", ""};
    list<Item*> items;
    string poison_name;
    for (string& suffix: poison_suffixs) {
        poison_name = getName() + suffix;
        items = AI_VALUE2(list<Item*>, "inventory items", poison_name);
        if (!items.empty()) {
            break;
        }
    }
    if (items.empty()) {
        return false;
    }
    return UseItemAuto(*items.begin());
}

bool CastCancelStealthAction::isUseful() {
    return ai->HasAura("stealth", bot);
}

bool CastCancelStealthAction::Execute(Event event) {
    ai->RemoveAura("stealth");
    return true;
}