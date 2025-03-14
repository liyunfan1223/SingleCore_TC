#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TankTargetValue.h"

using namespace ai;

class FindTargetForTankStrategy : public FindTargetStrategy
{
public:
    FindTargetForTankStrategy(PlayerbotAI* ai) : FindTargetStrategy(ai)
    {
        minThreat = 0;
        minTankCount = 0;
        maxDpsCount = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager)
    {
        Player* bot = ai->GetBot();
        float threat = threatManager->getThreat(bot);
        if (!result) {
            minThreat = threat;
            result = creature;
        }
        // neglect if victim is main tank, or no victim (for untauntable target)
        if (threatManager->getCurrentVictim()) {
            float max_threat = threatManager->getThreat(threatManager->getCurrentVictim()->getTarget());
            Unit* victim = threatManager->getCurrentVictim()->getTarget();
            // !creature->GetVictim() ||
            if (victim && victim->ToPlayer() && ai->IsMainTank(victim->ToPlayer())) {
                return;
            }
        }
        if (minThreat >= threat)
        {
            minThreat = threat;
            result = creature;
        }
    }

protected:
    float minThreat;
    int minTankCount;
    int maxDpsCount;
};


Unit* TankTargetValue::Calculate()
{
    FindTargetForTankStrategy strategy(ai);
    return FindTarget(&strategy);
}
