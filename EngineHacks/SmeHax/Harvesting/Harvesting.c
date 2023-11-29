#include "Harvesting.h"

u8 PickHarvestResult(HarvestResult* resultList) {
	int rand = NextRN_N(100) + 1; //value from 1-100
	
	while (true) {
		if (resultList->weight <= rand) return resultList->resultID;
		else rand -= resultList->weight;
		resultList++;
	}
	
}

void InitalizeHarvestToolLevels() {
	for (int i = 0; i < 16; i++) {
		*HarvestToolTiers[i] = 0;
	}
}

void SetHarvestToolLevel(int tool, int level) {
	*HarvestToolTiers[tool] = level;
}

void SetHarvestToolLevelIfHigher(int tool, int level) {
	if (level > *HarvestToolTiers[tool]) *SetHarvestToolLevel[tool] = level;
}

int GetHarvestToolLevel(int tool) {
	return *HarvestToolTiers[tool];
}

void BuildToolList(u16* listPtr, Trap* harvestTile) {
	// for each tool,
	// if its level is >0, 
	// and the harvest set has a nonzero pointer, 
	// add to list and increment list pointer
	
	
	
}

void AddHarvestTile_ASMC(Proc* parent) {
	int x = gEventSlot[0xB] & 0xFFFF;
	int y = gEventSlot[0xB] >> 16;
	Trap* trap = AddTrap(x, y, TRAP_HARVEST_TILE, 0);
	
	trap->data[TRAP_EXTDATA_HARVEST_TILE_SET_ID] = gEventSlot[1];
	trap->data[TRAP_EXTDATA_HARVEST_TILE_HARVESTED] = 0;
}





