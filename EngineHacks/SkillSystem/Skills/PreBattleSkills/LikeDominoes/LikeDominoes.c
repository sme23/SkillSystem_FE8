#include "gbafe.h"

extern bool SkillTester(Unit* unit, u8 skill);
extern u8 LikeDominoesID_Link;
extern u8 LikeDominoesAttackType_Link;
extern u8* AttackTypeByte_Link;
extern void GaleforceEvent;

void LikeDominoes(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void LikeDominoes_PostBattle();


void LikeDominoes(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (bunitA == &gBattleActor) return;
	if (
		bunitA->unit.curHP <= 5+bunitB->unit.skl
		&& SkillTester((Unit*)bunitB,LikeDominoesID_Link)
	) {
		//can't miss
		bunitA->battleAvoidRate = 0;
		bunitB->battleHitRate = 200;
		//will kill
		bunitA->battleDefense = 0;
		bunitB->battleAttack = bunitB->unit.curHP;
		//flag that the kill was due to this skill activating
		*AttackTypeByte_Link = LikeDominoesAttackType_Link;
	}
}

void LikeDominoes_PostBattle() {
	//if skill activated
	if (*AttackTypeByte_Link == LikeDominoesAttackType_Link
	//and no schenanigans kept them alive
	&& gBattleTarget.unit.curHP == 0
	&& gActionData.unitActionType == UNIT_ACTION_COMBAT
	) {
		//move again
		//unset status 0x42, set 0x400
		gActiveUnit->state &= 0xFFFFFFBD;
		gActiveUnit->state |= 0x0400;
		
		//call galeforce event (just does a sound effect)
		CallMapEventEngine(&GaleforceEvent, EV_RUN_CUTSCENE);
	}		
}

