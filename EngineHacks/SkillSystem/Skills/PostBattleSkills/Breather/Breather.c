#include "gbafe.h"

extern bool(*gSkillTester)(Unit* unit, int skillID);
const void* BreatherMapEvent();
extern u8 BreatherIDLink;

void BreatherPostBattle()
{
	Unit* unit = gActiveUnit;
	
	if (gSkillTester(unit, BreatherIDLink)) //does the unit have Breather
	{
		if 	((gActionData.unitActionType == UNIT_ACTION_WAIT)) //did the unit Wait
		{
			if (unit->curHP < unit->maxHP) //are they damaged?
			{
				CallMapEventEngine(BreatherMapEvent, EV_RUN_CUTSCENE);
				if (unit->curHP >= unit->maxHP / 2) //ex: if they have 10 / 20 HP or higher
				{
					unit->curHP = unit->maxHP;
				}
				else
				{
					unit->curHP += (unit->maxHP / 2);
				}
			}
		}
	}
	
}