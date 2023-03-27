
#pragma once
#include "../Trigger.h"
#include "../../PlayerbotAIConfig.h"
#include "GenericTriggers.h"

namespace ai
{
    class MutatingInjectionTrigger : public HasAuraTrigger
    {
    public:
        MutatingInjectionTrigger(PlayerbotAI* ai): HasAuraTrigger(ai, "mutating injection", 1) {}
    };

    class AuraRemovedTrigger : public Trigger
    {
    public:
        AuraRemovedTrigger(PlayerbotAI* ai, string name): Trigger(ai, name, 1) {
            this->name = name;
            this->prev_check = false;
        }
        virtual bool IsActive() {
            bool check = ai->HasAuraWithDuration(name, bot);
            bool ret = false;
            // bot->Yell(to_string(prev_check) + to_string(check), LANG_UNIVERSAL);
            if (prev_check && !check) {
                ret = true;
            }
            prev_check = check;
            return ret;
        }
    protected:
        bool prev_check;
    };

    class MutatingInjectionRemovedTrigger : public AuraRemovedTrigger
    {
    public:
        MutatingInjectionRemovedTrigger(PlayerbotAI* ai): AuraRemovedTrigger(ai, "mutating injection") {}
    };

    class BossEventTrigger : public Trigger
    {
    public:
        BossEventTrigger(PlayerbotAI* ai, uint32 boss_entry, uint32 event_id, string name = "boss event"): Trigger(ai, name, 1) {
            this->boss_entry = boss_entry;
            this->event_id = event_id;
            this->last_event_time = -1;
        }
        virtual bool IsActive();
    protected:
        uint32 boss_entry, event_id, last_event_time;
    };

    class GrobbulusCloudTrigger : public BossEventTrigger
    {
    public:
        GrobbulusCloudTrigger(PlayerbotAI* ai): BossEventTrigger(ai, 15931, 2, "grobbulus cloud event") {}
        virtual bool IsActive();
    };

    class HeiganMeleeTrigger : public Trigger
    {
    public:
        HeiganMeleeTrigger(PlayerbotAI* ai): Trigger(ai, "heigan melee") {}
        virtual bool IsActive();
    };

    class HeiganRangedTrigger : public Trigger
    {
    public:
        HeiganRangedTrigger(PlayerbotAI* ai): Trigger(ai, "heigan ranged") {}
        virtual bool IsActive();
    };
}