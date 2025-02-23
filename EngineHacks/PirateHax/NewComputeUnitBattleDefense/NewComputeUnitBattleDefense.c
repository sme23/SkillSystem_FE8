#include "gbafe.h"

extern bool CheckBit(u32* address, u8 bitOffset);
extern u32* GetUnitDebuffEntry(Unit* unit);
extern u8 DelegationBitOffset_Link;
int GetUnitDistance(Unit* firstUnit, Unit* secondUnit);
int abs(int num);


void NewComputeBattleUnitDefense(struct BattleUnit* attacker, struct BattleUnit* defender) {
    if (GetItemIndex(defender->weapon) == 0xF7)
    {
        if (GetUnitDistance(&attacker->unit, &defender->unit) == 1) //if they are adjacent
        {
            attacker->battleDefense = attacker->terrainDefense + attacker->unit.def;
            return;
        }
        else
        {
            attacker->battleDefense = attacker->terrainResistance + attacker->unit.res;
            return;
        }
    }
    if (GetItemAttributes(defender->weapon) & IA_MAGICDAMAGE)
        attacker->battleDefense = attacker->terrainResistance + attacker->unit.res;
    else if (GetItemAttributes(defender->weapon) & IA_MAGIC)
        attacker->battleDefense = attacker->terrainResistance + attacker->unit.res;
	else if (CheckBit(GetUnitDebuffEntry(&defender->unit), DelegationBitOffset_Link)) {
		if (attacker->unit.def > attacker->unit.res)
			attacker->battleDefense = attacker->terrainResistance + attacker->unit.res;
		else
			attacker->battleDefense = attacker->terrainDefense + attacker->unit.def;
	}
    else
        attacker->battleDefense = attacker->terrainDefense + attacker->unit.def;
}
