#pragma once

#include "../Action.h"
#include "GenericSpellActions.h"
#include "ReachTargetActions.h"
#include "ChooseTargetActions.h"
#include "MovementActions.h"

namespace ai
{
    class MeleeAction : public AttackAction 
    {
    public:
        MeleeAction(PlayerbotAI* ai) : AttackAction(ai, "melee") {}

        virtual string GetTargetName() { return "current target"; }
    };

    class TogglePetSpellAutoCastAction: public Action
	{
	public:
		TogglePetSpellAutoCastAction(PlayerbotAI* ai): Action(ai, "toggle pet spell auto cast") {}
		virtual bool Execute(Event event);
	};
}