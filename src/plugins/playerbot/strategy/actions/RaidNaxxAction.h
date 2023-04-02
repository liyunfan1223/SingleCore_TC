#pragma once
#include "../Action.h"
#include "MovementActions.h"
#include "AttackAction.h"

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

    class MoveInsideAction : public MovementAction
    {
    public:
        MoveInsideAction(PlayerbotAI* ai, float x, float y, float distance = 5.0f) : MovementAction(ai, "move inside") {
            this->x = x;
            this->y = y;
            this->distance = distance;
        }
        virtual bool Execute(Event event);
    protected:
        float x, y, distance;
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

    class GrobblulusMoveCenterAction : public MoveInsideAction
    {
    public:
        GrobblulusMoveCenterAction(PlayerbotAI* ai) : MoveInsideAction(ai, 3281.23f, -3310.38f, 5.0f) {}
    };

    class HeiganDanceAction : public MovementAction
    {
    public:
        HeiganDanceAction(PlayerbotAI* ai) : MovementAction(ai, "heigan dance") {
            this->prev_phase = 0;
            this->prev_erupt = 0;
            this->prev_timer = 0;
            waypoints.push_back(std::make_pair(2784.58f, -3665.50f));
            waypoints.push_back(std::make_pair(2769.59f, -3674.88f));
            waypoints.push_back(std::make_pair(2759.60f, -3690.45f));
            waypoints.push_back(std::make_pair(2755.99f, -3703.96f));
        }
    protected:
        bool CalculateSafe();
        void ResetSafe() { curr_safe = 0; curr_dir = 1; }
        void NextSafe() { curr_safe += curr_dir; if (curr_safe == 3 || curr_safe == 0) { curr_dir = -curr_dir; } }
        uint32 prev_phase, prev_erupt, prev_timer;
        uint32 curr_safe, curr_dir;
        std::vector<std::pair<float, float>> waypoints;
    };

    class HeiganDanceMeleeAction : public HeiganDanceAction
    {
    public:
        HeiganDanceMeleeAction(PlayerbotAI* ai) : HeiganDanceAction(ai) {}
        virtual bool Execute(Event event);
    };

    class HeiganDanceRangedAction : public HeiganDanceAction
    {
    public:
        HeiganDanceRangedAction(PlayerbotAI* ai) : HeiganDanceAction(ai) {
            platform = std::make_pair(2794.26f, -3706.67f);
        }
        virtual bool Execute(Event event);
    protected:
        std::pair<float, float> platform;
    };

    class ThaddiusAttackNearestPetAction : public AttackAction
    {
    public:
        ThaddiusAttackNearestPetAction(PlayerbotAI* ai) : AttackAction(ai, "thaddius attack nearest pet") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class ThaddiusMeleeToPlaceAction : public MovementAction
    {
    public:
        ThaddiusMeleeToPlaceAction(PlayerbotAI* ai) : MovementAction(ai, "thaddius melee to place") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class ThaddiusRangedToPlaceAction : public MovementAction
    {
    public:
        ThaddiusRangedToPlaceAction(PlayerbotAI* ai) : MovementAction(ai, "thaddius ranged to place") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class ThaddiusMoveToPlatformAction : public MovementAction
    {
    public:
        ThaddiusMoveToPlatformAction(PlayerbotAI* ai) : MovementAction(ai, "thaddius move to platform") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class ThaddiusMovePolarityAction : public MovementAction
    {
    public:
        ThaddiusMovePolarityAction(PlayerbotAI* ai) : MovementAction(ai, "thaddius move polarity") {}
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

    class RazuviousUseObedienceCrystalAction : public MovementAction
    {
    public:
        RazuviousUseObedienceCrystalAction(PlayerbotAI* ai) : MovementAction(ai, "razuvious use obedience crystal") {}
        virtual bool Execute(Event event);
    };

    class HorsemanAttractAlternativelyAction : public AttackAction
    {
    public:
        HorsemanAttractAlternativelyAction(PlayerbotAI* ai) : AttackAction(ai, "horseman attract alternatively") {
            this->last_voidzone = 0;
            this->voidzone_counter = 0;
        }
        virtual bool Execute(Event event);
    protected:
        uint32 last_voidzone, voidzone_counter;
    };

    class HorsemanAttactInOrderAction : public AttackAction
    {
    public:
        HorsemanAttactInOrderAction(PlayerbotAI* ai) : AttackAction(ai, "horseman attact in order") {}
        virtual bool Execute(Event event);
    };

    class SapphironGroundMainTankPositionAction : public MovementAction
    {
    public:
        SapphironGroundMainTankPositionAction(PlayerbotAI* ai) : MovementAction(ai, "sapphiron ground main tank position") {}
        virtual bool Execute(Event event);
    };

    class SapphironGroundPositionAction : public MovementAction
    {
    public:
        SapphironGroundPositionAction(PlayerbotAI* ai) : MovementAction(ai, "sapphiron ground position") {
            this->reset = 1;
            this->last_flight = 0;
            this->reset_timer = 0;
        }
        virtual bool Execute(Event event);
    protected:
        bool reset;
        uint32 last_flight, reset_timer;
    };
    
    class SapphironFlightPositionAction : public MovementAction
    {
    public:
        SapphironFlightPositionAction(PlayerbotAI* ai) : MovementAction(ai, "sapphiron flight position") {
            this->last_explosion = 0;
            this->move_ice_bolt = 0;
        }
        virtual bool Execute(Event event);
    protected:
        uint32 last_explosion;
        bool move_ice_bolt;
        bool MoveToNearestIcebolt();
    };

    class SapphironAvoidChillAction : public MovementAction
    {
    public:
        SapphironAvoidChillAction(PlayerbotAI* ai) : MovementAction(ai, "sapphiron avoid chill") {}
        virtual bool Execute(Event event);
    };
}