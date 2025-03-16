#include "gbafe.h"

#define CA_ARMSMASTER (1 << 6)
extern s8 WTHitBonus_Link;
extern s8 WTMtBonus_Link;

bool CheckArmsMasterLegality(BattleUnit* bunit1, BattleUnit* bunit2);
bool CheckSameWType(BattleUnit* bunit1, BattleUnit* bunit2);


void ArmsMasterSkill(BattleUnit* bunitA, BattleUnit* bunitB) {
	if (CheckArmsMasterLegality(bunitA, bunitB)){
		if (bunitA->unit.pClassData->attributes & CA_ARMSMASTER){
			bunitA->wTriangleHitBonus = 1 * WTHitBonus_Link;
			bunitA->wTriangleDmgBonus = 1 * WTMtBonus_Link;
			bunitB->wTriangleHitBonus = -1 * WTHitBonus_Link;
			bunitB->wTriangleDmgBonus = -1 * WTMtBonus_Link;
		}
		else if (bunitB->unit.pClassData->attributes & CA_ARMSMASTER){
			bunitA->wTriangleHitBonus = -1 * WTHitBonus_Link;
			bunitA->wTriangleDmgBonus = -1 * WTMtBonus_Link;
			bunitB->wTriangleHitBonus = 1 * WTHitBonus_Link;
			bunitB->wTriangleDmgBonus = 1 * WTMtBonus_Link;
		}
		else{
			//do nothing
		}
	}
}

bool CheckArmsMasterLegality(BattleUnit* bunit1, BattleUnit* bunit2){
	if (CheckSameWType(bunit1, bunit2)){
		if ((bunit1->unit.pClassData->attributes & CA_ARMSMASTER) && (bunit2->unit.pClassData->attributes & CA_ARMSMASTER))
		{
			return false; //if both have it, fail
		}

		return true; //if only one has it and it works, then return true
	}

	return false; //if not same wType, fail
}

bool CheckSameWType(BattleUnit* bunit1, BattleUnit* bunit2) {
	if (bunit1->weapon == 0 || bunit2->weapon == 0)
	{
		return false;
	}
	int wType1 = GetItemData(GetItemIndex(bunit1->weapon))->weaponType;
	int wType2 = GetItemData(GetItemIndex(bunit2->weapon))->weaponType;
	if (wType1 == wType2)
	{
		return true;
	}
	else{
		return false;
	}
}