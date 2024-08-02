#include "gbafe.h"

extern bool SkillTester(BattleUnit* unit, u8 skill);
extern u8 HandCannonID_Link;

void Proc_HandCannon(BattleUnit* bunitA, BattleUnit* bunitB, struct BattleHit* curRound, struct BattleStats* stats) {
	//if bunitA has Hand Cannon
	if (SkillTester(bunitA, HandCannonID_Link)) {
		//destroy equipped weapon
		bunitA->weapon &= 0xFF;
		bunitA->weaponBroke = true;
	}
}

