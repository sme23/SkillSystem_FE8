#include "ChapterKillCounter.h"

void ChapterKillCounter() {
	//are attacker and defender distinct?
	if (gBattleActor.unit.index == gBattleTarget.unit.index) return;
	
	//is attacker dead?
	BattleUnit* bunit = &gBattleActor;
	if (bunit->hpInitial != 0 && bunit->unit.curHP == 0 && gBattleTarget.unit.pCharacterData->number == gActiveUnit->pCharacterData->number) {
		//if so, increment the other unit's kill counter
		IncrementChapterKillCounter(GetUnit(gBattleTarget.unit.index));
	}
	
	//is defender dead?
	bunit = &gBattleTarget;
	if (bunit->hpInitial != 0 && bunit->unit.curHP == 0 && gBattleActor.unit.pCharacterData->number == gActiveUnit->pCharacterData->number) {
		//if so, increment the other unit's kill counter
		IncrementChapterKillCounter(GetUnit(gBattleActor.unit.index));
	}
}

void IncrementChapterKillCounter(Unit* unit) {
	u32* debuffEntry = GetUnitDebuffEntry(unit);
	u32 stat = UnpackData(debuffEntry, HardworkingBitOffset_Link, 3);
	if (stat < 7) stat++;
	PackData(debuffEntry, HardworkingBitOffset_Link, 3, stat);
}

int GetChapterKillCounter(Unit* unit) {
	u32* debuffEntry = GetUnitDebuffEntry(unit);
	return UnpackData(debuffEntry, HardworkingBitOffset_Link, 3);
}

void ClearChapterKillCounter(Unit* unit) {
	u32* debuffEntry = GetUnitDebuffEntry(unit);
	PackData(debuffEntry, HardworkingBitOffset_Link, 3, 0);	
}

void ClearAllChapterKillCounters() {
	//loop through every unit of relevant allegiance and set the counter to 0
	int unitID = 1;
	int maxCount = 62;
	
	while (unitID < maxCount) {
		//get the unit unitID
		Unit* curUnit = GetUnit(unitID);
	
		//clear the bit
		ClearChapterKillCounter(curUnit);
		unitID++;
	}
}

u32 HardworkingBuff(u32 stat, Unit* unit) {
	if (SkillTester(unit,HardworkingIDLink)) {
		int buff = GetChapterKillCounter(unit);
		if (buff > HardworkingStatCapLink) buff = HardworkingStatCapLink;
		return stat+buff;
	}
	return stat;
}

u32 StrTakerBuff(u32 stat, Unit* unit) {
	if (SkillTester(unit,StrTakerIDLink)) {
		int buff = GetChapterKillCounter(unit) * 2;
		if (buff > StrTakerStatCapLink) buff = StrTakerStatCapLink;
		return stat+buff;
	}
	return stat;
}

