#include "gbafe.h"

extern u8 IgnisTriggerIDLink;
extern u8 IgnisTriggerMtLink;

extern bool(*gSkillTester)(Unit* unit, int skillID);
int GetUnitDistance(Unit* firstUnit, Unit* secondUnit);
int abs(int num);


int GetUnitDistance(Unit* firstUnit, Unit* secondUnit){
	return abs(firstUnit->xPos - secondUnit->xPos) + abs(firstUnit->yPos - secondUnit->yPos);
}

int abs(int num){
	if (num < 0){
		num *= -1;
	}
	return num;
}

void IgnisTriggerPreBattle(BattleUnit* bunitA, BattleUnit* bunitB) {
	if (gSkillTester(&bunitA->unit, IgnisTriggerIDLink)){
        if (gBattleStats.config & BATTLE_CONFIG_BIT2)
        {

        }
        if (GetUnitDistance(&bunitA->unit, &bunitB->unit) == 1) //if they are adjacent
        {
            bunitA->battleAttack = bunitA->unit.pow + IgnisTriggerMtLink; //use str
        }
        else
        {
            bunitA->battleAttack = bunitA->unit.skl + IgnisTriggerMtLink; //use skl
        }
    }
}
