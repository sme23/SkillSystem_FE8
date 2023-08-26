#include "gbafe.h"

extern bool SkillTester(Unit* unit, u8 skillID);
extern bool CheckBit(u32* address, u8 bitOffset);
extern void SetBit(u32* address, u8 bitOffset);
extern void UnsetBit(u32* address, u8 bitOffset);
extern void PackData_Signed(u32* address, u8 bitOffset, u8 bitCount, u8 value);
extern int UnpackData_Signed(u32* address, u8 bitOffset, u8 bitCount);
extern u32* GetUnitDebuffEntry(Unit* unit);

extern u8 WellRestedIDLink;
extern u8 WellRestedBitOffset_Link;

u32 WellRested(u32 stat, Unit* unit); 
u8 WellRested_GetBonus(Unit* unit);
void WellRested_IncrementBonus(Unit* unit);
void WellRested_DecrementBonus(Unit* unit);
void PrePrep_WellRestedBonus(Unit* unit);
