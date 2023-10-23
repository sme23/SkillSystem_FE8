#include "gbafe.h"

extern bool SkillTester(Unit* unit, u8 skillID);

extern u8 MiraclemakerID_Link;
extern u32 MiraclemakerBitOffset_Link;

extern void SetBit(u32* address, u8 bitOffset);
extern void UnsetBit(u32* address, u8 bitOffset);
extern bool CheckBit(u32* address, u8 bitOffset);
extern u32* GetUnitDebuffEntry(Unit* unit);

void Miraclemaker(Unit* unit) {
	if(gActionData.unitActionType == UNIT_ACTION_STAFF && SkillTester(unit, MiraclemakerID_Link)) {
		u32* entry = GetUnitDebuffEntry(GetUnit(gActionData.targetIndex));
		SetBit(entry, MiraclemakerBitOffset_Link);
	}
}
