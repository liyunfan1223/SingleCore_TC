#pragma once
#include "../Action.h"
#include "MovementActions.h"

namespace ai
{
    class TryToGetBossAIAction : public Action
    {
    public:
        TryToGetBossAIAction(PlayerbotAI* ai) : Action(ai, "try to get boss ai") {}

    public:
        virtual bool Execute(Event event);
    };

    class GoBehindTheBossAction : public MovementAction
    {
    public:
        GoBehindTheBossAction(PlayerbotAI* ai, float distance = 30.0f) : MovementAction(ai, "go behind the boss") {
            this->distance = distance;
        }
        virtual bool Execute(Event event);
    protected:
        float distance;
    };
}