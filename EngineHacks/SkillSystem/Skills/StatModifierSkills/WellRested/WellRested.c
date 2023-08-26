#include "WellRested.h"

u32 WellRested(u32 stat, Unit* unit) {

	//does unit have skill?
	if (SkillTester(unit,WellRestedIDLink)) {
		//add our bonus value to the stat
		stat += WellRested_GetBonus(unit);
	}
	return stat;
}

u8 WellRested_GetBonus(Unit* unit) {
	//given a unit, get their current bonus
	u32* debuffEntry = GetUnitDebuffEntry(unit);
	int val = UnpackData_Signed(debuffEntry, WellRestedBitOffset_Link, 5);
	return val;
}

void WellRested_IncrementBonus(Unit* unit) {
	u32* debuffEntry = GetUnitDebuffEntry(unit);
	int val = UnpackData_Signed(debuffEntry, WellRestedBitOffset_Link, 5);
	val++;
	if (val > 15) val = 15;
	//PackData_Signed(debuffEntry, WellRestedBitOffset_Link, 5, val);
}

void WellRested_DecrementBonus(Unit* unit) {
	u32* debuffEntry = GetUnitDebuffEntry(unit);
	int val = UnpackData_Signed(debuffEntry, WellRestedBitOffset_Link, 5);
	val--;
	u8 baseMov = unit->pClassData->baseMov;
	if (val < baseMov) val = baseMov;
	//PackData_Signed(debuffEntry, WellRestedBitOffset_Link, 5, val);	
}

void PrePrep_WellRestedBonus(Unit* unit) {
	//for each unit, if they have WellRested, either increment or decrement their bonus
	
	if (SkillTester(unit, WellRestedIDLink)) {
		if (unit->state & US_NOT_DEPLOYED) { WellRested_IncrementBonus(unit); }
		else { WellRested_DecrementBonus(unit); }
	}
}
