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
	if (level > *HarvestToolTiers[tool]) SetHarvestToolLevel(tool, level);
}

int GetHarvestToolLevel(int tool) {
	return *HarvestToolTiers[tool];
}

HarvestResult* GetHarvestResult(int id, int tool) {
	HarvestSet* e = HarvestingTable.set[id];
	return e->toolResult[tool];
}

void BuildToolList(u16* listPtr, Trap* harvestTile) {
	// for each tool,
	// if its level is >0, 
	// and the harvest set has a nonzero pointer, 
	// add to list and increment list pointer
	
	int tool = harvestTile->data[0];
	
	for (u16 i = 0; i < 16; i++) {
		if (!GetHarvestToolLevel(i)) continue;
		if (!GetHarvestResult(i, tool)) continue;
		
		*listPtr = i;
		listPtr++;		
	}
	
	*listPtr = 0;
	
}

void AddHarvestTile_ASMC(Proc* parent) {
	int x = gEventSlot[0xB] & 0xFFFF;
	int y = gEventSlot[0xB] >> 16;
	Trap* trap = AddTrap(x, y, TRAP_HARVEST_TILE, 0);
	
	trap->data[TRAP_EXTDATA_HARVEST_TILE_SET_ID] = gEventSlot[1];
	trap->data[TRAP_EXTDATA_HARVEST_TILE_HARVESTED] = 0;
}


u8 HarvestMenuHelpBox(MenuProc* menu, MenuCommandProc* menuItem) {
	//runs when the help box is being drawn.
	//responsible for making the help box for this menu
	
	int tool = *HarvestToolBuffer[menuItem->commandDefinitionIndex - 1];
	
	StartHarvestHelpBox(menuItem->xDrawTile << 3, menuItem->yDrawTile << 3, tool);
	
	return 0;
	
}

void StartHarvestHelpBox(int x, int y, int tool) {
	gSomeTextRelatedStuff.adjUp    = NULL;
    gSomeTextRelatedStuff.adjDown  = NULL;
    gSomeTextRelatedStuff.adjLeft  = NULL;
    gSomeTextRelatedStuff.adjRight = NULL;

    gSomeTextRelatedStuff.xDisplay = x;
    gSomeTextRelatedStuff.yDisplay = y;
    gSomeTextRelatedStuff.mid      = tool;

    gSomeTextRelatedStuff.redirect = NULL;
    gSomeTextRelatedStuff.populate = HbPopulate_AutoTool;

    gHelpTextOriginTile.x = 0;
    gHelpTextOriginTile.y = 0;

    StartHelpBoxExt(&gSomeTextRelatedStuff, FALSE);
}

void HbPopulate_AutoTool(HelpBoxProc* proc) {
	//this will eventually be what's responsible for picking the thing to display
	//which will be from a table based on the tool ID which is in proc->info->mid
}

u8 HarvestMenu_ButtonBPressed(MenuProc* menu, MenuCommandProc* menuItem) {
	FillBgMap(gBg2MapBuffer, 0);
    EnableBgSyncByMask(BG2_SYNC_BIT);

    Text_ResetTileAllocation();

    StartMenu_AndDoSomethingCommands(&gMenu_UnitMenu, gGameState.cameraRealPos.x - gGameState.cameraRealPos.y, 1, 22);

    HideMoveRangeGraphics();
	
	 return ME_DISABLE | ME_END | ME_PLAY_BOOP | ME_CLEAR_GFX | ME_END_FACE0;
}


u8 HarvestMenu_Usability(const MenuCommandDefinition* command, int number) {
	//returns 1 if the # has a tool, otherwise returns 3
	return 1;
}
int HarvestMenu_TextDraw(MenuProc* menu, MenuCommandProc* menuItem) {
	int tool = *HarvestToolBuffer[menuItem->commandDefinitionIndex - 1];

	//DrawItemMenuLine is not going to do the thing that its supposed to, it will draw the item of the tool's ID. need to copy this later
    DrawItemMenuLine(&menuItem->text, tool, 1, gBg0MapBuffer + TILEMAP_INDEX(menuItem->xDrawTile, menuItem->yDrawTile));

    return 0;
}

u8 HarvestMenu_Effect(MenuProc* menu, MenuCommandProc* menuItem) {
	//roll the harvest result, do a popup for it, set the action to wait
}

int HarvestMenu_SwitchIn(MenuProc* menu, MenuCommandProc* menuItem) {
	//runs when you move the cursor and the menuItem index is the newly selected option
}

int HarvestMenu_SwitchOut(MenuProc* menu, MenuCommandProc* menuItem) {
	//runs when you move the cursor and the menuItem index is the previously selected option
}






