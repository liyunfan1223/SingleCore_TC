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
        GoBehindTheBossAction(PlayerbotAI* ai, float distance = 24.0f, float delta_angle = M_PI / 8) : MovementAction(ai, "go behind the boss") {
            this->distance = distance;
            this->delta_angle = delta_angle;
        }
        virtual bool Execute(Event event);
    protected:
        float distance, delta_angle;
    };

    class MoveToPointForceAction : public MovementAction
    {
    public:
        MoveToPointForceAction(PlayerbotAI* ai, float x, float y) : MovementAction(ai, "move to point force") {
            this->x = x;
            this->y = y;
        }
        virtual bool Execute(Event event);
    protected:
        float x, y;
    };

    class RotateAroundTheCenterPointAction : public MovementAction
    {
    public:
        RotateAroundTheCenterPointAction(PlayerbotAI* ai, float center_x, float center_y, float radius = 40.0f, 
            uint32 intervals = 16, bool clockwise = true, float start_angle = 0) : MovementAction(ai, "rotate around the center point") {
            this->center_x = center_x;
            this->center_y = center_y;
            this->radius = radius;
            this->intervals = intervals;
            this->clockwise = clockwise;
            this->call_counters = 0;
            for (int i = 0; i < intervals; i++) {
                float angle = start_angle + 2 * M_PI * i / intervals;
                waypoints.push_back(std::make_pair(center_x + cos(angle) * radius, center_y + sin(angle) * radius));
            }
        }
        virtual bool Execute(Event event);
    protected:
        virtual uint32 GetCurrWaypoint() = 0;
        uint32 FindNearestWaypoint();
        float center_x, center_y, radius;
        uint32 intervals, call_counters;
        bool clockwise;
        std::vector<std::pair<float, float>> waypoints;
    };

    class RotateGrobbulusAction : public RotateAroundTheCenterPointAction
    {
    public:
        RotateGrobbulusAction(PlayerbotAI* ai): RotateAroundTheCenterPointAction(ai, 3281.23f, -3310.38f, 35.0f, 8, true, M_PI) {}
        virtual bool isUseful() {
            return RotateAroundTheCenterPointAction::isUseful() && ai->IsMainTank(bot) && AI_VALUE2(bool, "has aggro", "boss target");
        }
        virtual uint32 GetCurrWaypoint();
    protected:
    };

    class GrobblulusMoveCenterAction : public MoveToPointForceAction
    {
    public:
        GrobblulusMoveCenterAction(PlayerbotAI* ai) : MoveToPointForceAction(ai, 3281.23f, -3310.38f) {}
    };
}