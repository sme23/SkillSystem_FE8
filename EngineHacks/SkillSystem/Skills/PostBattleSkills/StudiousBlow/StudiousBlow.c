#include "StudiousBlow.h"

void StudiousBlow() {
	//if action taken is attacking and both participants aren't the same, and active unit has studious blow, store active unit's mag to studious blow byte
	Unit* unit = gActiveUnit;
	
	if 	(	(gActionData.unitActionType == UNIT_ACTION_COMBAT) && 
			(gActionData.subjectIndex != gActionData.targetIndex) &&
			(SkillTester(unit,StudiousBlowIDLink))
		) {
		*StudiousBlowByteLoc = prMagGetter(unit);
		SetBit(GetUnitDebuffEntry(GetUnit(gActionData.targetIndex)), StudiousBlowBitOffset_Link);
		
	}
}

void StudiousBlowAtkBonus(BattleUnit* bunitA, BattleUnit* bunitB) {
	//if bunitA's allegiance is the current phase, add studious blow byte to atk
	
	
	if (( (bunitA->unit.index & 0xC0) == (gChapterData.currentPhase) ) && ( CheckBit(GetUnitDebuffEntry(GetUnit(bunitB->unit.index)), StudiousBlowBitOffset_Link) )) {
		if (bunitB->unit.pClassData != 0){ //is this a real fight
			bunitA->battleAttack += *StudiousBlowByteLoc;
		}
	}
}

void ClearStudiousBlow() {
	//set studious blow byte to 0
	*StudiousBlowByteLoc = 0;
	
	//loop through every unit of relevant allegiance and unset the studious blow target bit
	int faction = gChapterData.currentPhase;
	int unitID = faction+1;
	int maxCount = 0;
	
	switch (faction) {
		case UA_BLUE:
		maxCount = 62;
		break;
		
		case UA_RED:
		maxCount = 50;
		break;
		
		case UA_GREEN:
		maxCount = 20;
		break;
	}
	
	while ((unitID - faction) < maxCount) {
		//get the unit unitID
		Unit* curUnit = GetUnit(unitID);
	
		//clear the bit
		UnsetBit(GetUnitDebuffEntry(curUnit), StudiousBlowBitOffset_Link);
		unitID++;
	}

}



