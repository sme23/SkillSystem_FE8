#include "gbafe.h"

void StudiousBlow();
void StudiousBlowAtkBonus(BattleUnit* bunitA, BattleUnit* bunitB);
void ClearStudiousBlow();

extern bool SkillTester(Unit* unit, u8 skillID);
extern s8 prMagGetter(Unit* unit);
extern bool CheckBit(u32* address, u8 bitOffset);
extern void SetBit(u32* address, u8 bitOffset);
extern void UnsetBit(u32* address, u8 bitOffset);
extern u32* GetUnitDebuffEntry(Unit* unit);

extern u8* StudiousBlowByteLoc;
extern u8 StudiousBlowIDLink;
extern u8 StudiousBlowBitOffset_Link;

