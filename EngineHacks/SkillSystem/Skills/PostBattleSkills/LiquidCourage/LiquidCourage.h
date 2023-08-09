#include "gbafe.h"

extern u8 LiquidCourageIDLink;
extern u32 LiquidCourageBitOffset_Link;
extern u8 LiquidCourageStrLink;
extern u8 LiquidCourageSklLink;
extern u8 LiquidCourageSpdLink;
extern u8 DebuffStatNumberOfBits_Link;
extern u8 LiquidCourageConsumables;

extern bool SkillTester(Unit* unit, u8 skillID);
extern bool CheckBit(u32* address, u8 bitOffset);
extern void SetBit(u32* address, u8 bitOffset);
extern void UnsetBit(u32* address, u8 bitOffset);
extern void PackData_Signed(u32* address, u8 bitOffset, u8 bitCount, u8 value);
extern int UnpackData_Signed(u32* address, u8 bitOffset, u8 bitCount);
extern u32* GetUnitDebuffEntry(Unit* unit);

void LiquidCourage();
void LQ_SetBuff(Unit* unit, u8 statIndex, u8 statChange);
void ResetLiquidCourage(Unit* unit);
bool AlwaysTrueFunc();
bool IsLiquidCourageConsumable(u16 item);

#define StrStatIndex 1
#define SklStatIndex 2
#define SpdStatIndex 3

