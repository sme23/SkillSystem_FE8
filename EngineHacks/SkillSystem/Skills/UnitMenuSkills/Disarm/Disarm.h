#include "gbafe.h"

extern u8 DisarmIDLink;
extern u16 DisarmHelpTextLink;
extern bool(*gSkillTester)(struct Unit* unit, int skillID);

extern struct SelectInfo const SelectInfo_Disarm;
u8 DisarmUsability(const struct MenuItemDef* def, int number);
u8 DisarmEffect(struct MenuProc* menu, struct MenuItemProc* menuItem);
u8 DisarmSelection_OnSelect(ProcPtr proc, struct SelectTarget* target);
void DisarmSelection_OnInit(ProcPtr menu);
u8 DisarmSelection_OnChange(ProcPtr proc, struct SelectTarget* target);
void DoDisarmEffect(int targetUid);
void MakeDisarmTargetList(struct Unit* unit);
void TryAddUnitToDisarmTargetList(struct Unit* unit);

extern int BreakBitOffset_Link;
extern int BreakInBattleBitOffset_Link;
extern int DebuffStatBitOffset_Def;

extern void SetBit(u32* address, u8 bitOffset);
extern void UnsetBit(u32* address, u8 bitOffset);
extern bool CheckBit(u32* address, u8 bitOffset);
extern u32* GetUnitDebuffEntry(struct Unit* unit);

void ForEachAdjacentUnit(int x, int y, void(*)(struct Unit*)); //! FE8U = 0x8024F71
extern void ApplyDebuff(struct Unit* unit, int amount, int offset);

const void* DisarmMapEvent();
void CallMapEventEngine(const void* scene, int runKind);