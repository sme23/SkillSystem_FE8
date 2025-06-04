#include "gbafe.h"

extern bool NewAuraSkillCheck(struct BattleUnit* unit, int skillID, int allyOption, int maxRange);
extern u8 MisfortuneID_Link;
extern u8 MisfortuneRange_Link;

void Misfortune(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if(NewAuraSkillCheck(bunitA, MisfortuneID_Link, 0x4, MisfortuneRange_Link)) {
		bunitA->battleAvoidRate /= 2;
	}
}
