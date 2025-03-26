#include "gbafe.h"

// decompnathan
#define SECTION(name) __attribute__((section(name)))
#define CONST_DATA SECTION(".data")

//stuff defined in the reference file but not the headers
extern void BattleInitItemEffect(Unit* unit, u8 itemIndex);
extern void BattleInitItemEffectTarget(Unit* unit);
extern void BattleApplyItemEffect(Proc* proc);
extern void BeginBattleAnimations();

extern Unit* gUnitSubject;

//debuff functions
extern void SetBit(u32* address, u8 bitOffset);
extern void UnsetBit(u32* address, u8 bitOffset);
extern bool CheckBit(u32* address, u8 bitOffset);
extern u32* GetUnitDebuffEntry(Unit* unit);
extern void Item_TURange(struct Unit* unit, void* func, int item);

// fortune staff EA labels
extern u32 FortuneStaffBitOffset_Link;
extern u8 FortuneStaffBuffAmount_Link;
extern u16 FortuneStaffSubtitleText_Link;
extern struct TargetSelectionDefinition CONST_DATA FortuneStaffSelectInfo;
extern u8 FortuneStaffID_Link;

//function prototypes
bool IsFortuneBitSet(Unit* unit);
void SetFortuneBit(Unit* unit);
void UnsetFortuneBit(Unit* unit);
void FortuneHitBoost(BattleUnit* bunitA, BattleUnit* bunitB);
void ClearFortuneBitEachTurn();
void AddUnitToTargetListIfUnfortunate(Unit* unit);
void MakeTargetListForFortune(Unit* unit);
void FortuneUsabilityWrapper();
bool FortuneUsability(Unit* unit);

