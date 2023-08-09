#include "LiquidCourage.h"


void LiquidCourage() {
	Unit* unit = gActiveUnit;
	if ( 	(gActionData.unitActionType == UNIT_ACTION_USE_ITEM) && 
			(IsLiquidCourageConsumable(unit->items[gActionData.itemSlotIndex])) && 
			(SkillTester(unit,LiquidCourageIDLink)) && 
			(!CheckBit(GetUnitDebuffEntry(unit), LiquidCourageBitOffset_Link)) 
		) {
		SetBit(GetUnitDebuffEntry(unit), LiquidCourageBitOffset_Link);
		LQ_SetBuff(unit, StrStatIndex, LiquidCourageStrLink);
		LQ_SetBuff(unit, SklStatIndex, LiquidCourageSklLink);
		LQ_SetBuff(unit, SpdStatIndex, LiquidCourageSpdLink);
		m4aSongNumStart(0x10F);
	}
	
}

void LQ_SetBuff(Unit* unit, u8 statIndex, u8 statChange) {
	u32* debuffPtr = GetUnitDebuffEntry(unit); 
	u8 bitCount = DebuffStatNumberOfBits_Link;
	u8 bitOffset = (statIndex * bitCount);
	u8 newStat = UnpackData_Signed(debuffPtr, bitOffset, bitCount) + statChange;
	PackData_Signed(debuffPtr, bitOffset, bitCount, newStat);
	
}

void ResetLiquidCourage(Unit* unit) {
	UnsetBit(GetUnitDebuffEntry(unit),LiquidCourageBitOffset_Link);
}

bool AlwaysTrueFunc() {
	return true;
}

bool IsLiquidCourageConsumable(u16 item) {
	u8 id = (item & 0xFF);
	
	u8* listPos = &LiquidCourageConsumables;
	
	while (*listPos != 0) {
		if (*listPos == id) return true;
		listPos++;
	}
	return false;
}
