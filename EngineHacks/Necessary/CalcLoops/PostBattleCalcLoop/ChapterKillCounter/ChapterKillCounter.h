#include "gbafe.h"

void ChapterKillCounter();
u32 HardworkingBuff(u32 stat, Unit* unit);
void IncrementChapterKillCounter(Unit* unit);
void ClearChapterKillCounter(Unit* unit);
void ClearAllChapterKillCounters();

extern bool SkillTester(Unit* unit, u8 skillID);
extern bool CheckBit(u32* address, u8 bitOffset);
extern void SetBit(u32* address, u8 bitOffset);
extern void UnsetBit(u32* address, u8 bitOffset);
extern void PackData_Signed(u32* address, u8 bitOffset, u8 bitCount, u8 value);
extern u32 UnpackData_Signed(u32* address, u8 bitOffset, u8 bitCount);
extern void PackData(u32* address, u8 bitOffset, u8 bitCount, u8 value);
extern u32 UnpackData(u32* address, u8 bitOffset, u8 bitCount);
extern u32* GetUnitDebuffEntry(Unit* unit);

extern u8 HardworkingIDLink;
extern u8 HardworkingBitOffset_Link;
extern u8 StrTakerStatCapLink;
extern u8 HardworkingStatCapLink;
extern u8 StrTakerIDLink;
