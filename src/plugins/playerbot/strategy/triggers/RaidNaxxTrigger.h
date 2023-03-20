
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
}