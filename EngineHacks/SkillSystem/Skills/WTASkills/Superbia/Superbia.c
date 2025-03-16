#include "gbafe.h"

extern bool(*gSkillTester)(Unit* unit, int skillID);


extern u8 SuperbiaEffectID_Link;
extern s8 WTHitBonus_Link;
extern s8 WTMtBonus_Link;

void SuperbiaEffect(BattleUnit* bunitA, BattleUnit* bunitB) {
	if(gSkillTester(&bunitA->unit, SuperbiaEffectID_Link)){ //if unit A has superbia, always has WTA
		bunitA->wTriangleHitBonus = 1 * WTHitBonus_Link;
		bunitA->wTriangleDmgBonus = 1 * WTMtBonus_Link;
		bunitB->wTriangleHitBonus = -1 * WTHitBonus_Link;
		bunitB->wTriangleDmgBonus = -1 * WTMtBonus_Link;
	}
	if(gSkillTester(&bunitB->unit, SuperbiaEffectID_Link)) { //if unit B, then they have WTA
		bunitA->wTriangleHitBonus = -1 * WTHitBonus_Link;
		bunitA->wTriangleDmgBonus = -1 * WTMtBonus_Link;
		bunitB->wTriangleHitBonus = 1 * WTHitBonus_Link;
		bunitB->wTriangleDmgBonus = 1 * WTMtBonus_Link;
	}
}
