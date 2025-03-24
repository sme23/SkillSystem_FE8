#include "gbafe.h"

// debuff functions
extern void SetBit(u32* address, u8 bitOffset);
extern void UnsetBit(u32* address, u8 bitOffset);
extern bool CheckBit(u32* address, u8 bitOffset);
extern u32* GetUnitDebuffEntry(struct Unit* unit);

// ea labels
extern u32 DoubleFalconBitOffset_Link;
extern int SkillTester(struct BattleUnit* unit, u8 skill);
extern u8 DoubleFalconID_Link;
extern u16 DoubleFalconEvent;

bool IsDoubleFalconBitSet(struct Unit* unit) {
	return CheckBit(GetUnitDebuffEntry(unit), DoubleFalconBitOffset_Link);
}

void SetDoubleFalconBit(struct Unit* unit) {
	SetBit(GetUnitDebuffEntry(unit), DoubleFalconBitOffset_Link);
}

void UnsetDoubleFalconBit(struct Unit* unit) {
	UnsetBit(GetUnitDebuffEntry(unit), DoubleFalconBitOffset_Link);
}

void DoubleFalconPostbattle() {
	if((gActionData.unitActionType == UNIT_ACTION_COMBAT) && (gActionData.subjectIndex != gActionData.targetIndex)) {
		struct BattleUnit* bunitA = &gBattleActor;
		struct BattleUnit* bunitB = &gBattleTarget;		

		UnsetDoubleFalconBit(&(bunitA->unit));
		UnsetDoubleFalconBit(&(bunitB->unit));
		
		if(bunitA->unit.curHP <= 0 && SkillTester(bunitB, DoubleFalconID_Link)) {
			SetDoubleFalconBit(&(bunitB->unit));
			CallMapEventEngine(&DoubleFalconEvent, 0x1);
		}
		else if(bunitB->unit.curHP <= 0 && SkillTester(bunitA, DoubleFalconID_Link)) {
			SetDoubleFalconBit(&(bunitA->unit));
			CallMapEventEngine(&DoubleFalconEvent, 0x1);
		}
	}
}

// goes in the prebattle calc loop
// i love prebattle skills that don't require a call to skilltester
void DoubleFalconPrebattle(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if(IsDoubleFalconBitSet(&(bunitA->unit))) {
		bunitA->weaponAttributes |= IA_BRAVE;
	}
	
	if(IsDoubleFalconBitSet(&(bunitB->unit))) {
		bunitB->weaponAttributes |= IA_BRAVE;
	}
}
