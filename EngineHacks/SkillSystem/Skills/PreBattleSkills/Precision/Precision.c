#include "gbafe.h"

extern bool SkillTester(struct BattleUnit* unit, int skill);
extern u8 PrecisionID_Link;

void Precision(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if(gBattleStats.range > 1 && SkillTester(bunitA, PrecisionID_Link)) {
		bunitA->battleCritRate += GetUnitSkill(&bunitA->unit);
	}
}
