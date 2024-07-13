#include "gbafe.h"

extern u8* GetUnitsInRange(Unit* unit, int allyOption, int range);
extern bool(*gSkillTester)(Unit* unit, int skillID);

extern u8 WanderersFocusID_Link;
extern u8 WanderersFocusRange_Link;
extern s8 WTHitBonus_Link;
extern s8 WTMtBonus_Link;

void WanderersFocus(BattleUnit* bunitA, BattleUnit* bunitB) {
	if (gSkillTester(&bunitA->unit, WanderersFocusID_Link)) // does the unit have Wanderer's Focus
	{
		if (GetUnitsInRange(&bunitA->unit, 0, WanderersFocusRange_Link) == 0) //do you not have an ally within 3 range, if so keep going
		{
			if (gBattleTarget.unit.pCharacterData->number == bunitA->unit.pCharacterData->number) //is bUnitA also the target
			{
				bunitA->wTriangleHitBonus = WTHitBonus_Link;
				bunitA->wTriangleDmgBonus = WTMtBonus_Link;
			}
		}
	}

	if (gSkillTester(&bunitB->unit, WanderersFocusID_Link)) // does the unit have Wanderer's Focus
	{
		if (GetUnitsInRange(&bunitB->unit, 0, WanderersFocusRange_Link) == 0) //do you not have an ally within 3 range, if so keep going
		{
			if (gBattleTarget.unit.pCharacterData->number == bunitB->unit.pCharacterData->number) //is bUnitB also the target
			{
				bunitB->wTriangleHitBonus = WTHitBonus_Link;
				bunitB->wTriangleDmgBonus = WTMtBonus_Link;
			}
		}
	}
}
