#include "gbafe.h"

struct BridgeAssoc {
	u16 tileConfigID;
	u16 tileID;
} typedef BridgeAssoc;

//defined in EA
extern bool SkillTester(Unit* unit, u8 skill);
extern u8 BoardingPartyID_Link;
extern BridgeAssoc BoardingPartyBridgeTileList[];
extern struct ROMChapterData* GetChapterDefinition(u8 chapterID);
extern u16 BoardingPartySubtitleHelpTextID_Link;

#define UNIT_ACTION_BOARDINGPARTY 0x29
#define TRAP_DYNAMICTILECHANGE 32

//defined in ref
extern void GenericSelection_DeleteBBAndBG(TargetSelectionProc* proc);
//extern u8 GenericSelection_BackToUM(TargetSelectionProc* proc, struct TargetEntry* target);
extern Unit* gUnitSubject;
extern void UpdateAllLightRunes();

//prototypes
int BoardingPartyUsability(MenuCommandDefinition* command, int number);
int BoardingPartyEffect(MenuProc* menu, MenuCommandProc* menuItem);
bool CanBridgeOnCurrentMap();
u16 GetBridgeTileID();
void MakeTargetListForBoardingParty(Unit* unit);
void TryAddToBoardingPartyTargetList(int x, int y);
void BoardingPartySelection_OnInit(TargetSelectionProc* menu);
int BoardingPartySelection_OnSelect(TargetSelectionProc* proc, TargetEntry* target);
void BoardingPartyAction();

const struct TargetSelectionDefinition gSelectInfo_BoardingParty = 
{
	.onInit = BoardingPartySelection_OnInit,
	.onEnd = GenericSelection_DeleteBBAndBG,
	.onAPress = BoardingPartySelection_OnSelect,
	.onBPress = GenericSelection_BackToUM,
};



u16 GetBridgeTileID() {
	int configID;
	struct ROMChapterData* chData = GetChapterDefinition(gChapterData.chapterIndex);
	configID = chData->mapTileConfigId;
	for (int i = 0; ; i++) {
		if (BoardingPartyBridgeTileList[i].tileConfigID == 0xFFFF &&
			BoardingPartyBridgeTileList[i].tileID == 0xFFFF) return 0xFFFF;
		if (BoardingPartyBridgeTileList[i].tileConfigID == configID) return BoardingPartyBridgeTileList[i].tileID;
	}
}

bool CanBridgeOnCurrentMap() {
	return GetBridgeTileID() != 0xFFFF;
}

void MakeTargetListForBoardingParty(Unit* unit) {
	int x = unit->xPos;
	int y = unit->yPos;
	gUnitSubject = unit;
	BmMapFill(gMapRange, 0);
	ForEachAdjacentPosition(x, y, TryAddToBoardingPartyTargetList);
}

void TryAddToBoardingPartyTargetList(int x, int y) {
	struct Trap* trap;
	
	if (gMapUnit[y][x] != 0) {
		return;
	}
	
	AddTarget(x,y,0,0);
}

int BoardingPartyUsability(MenuCommandDefinition* command, int number) {
	//true if can bridge on current map and target list isn't empty and has skill
	MakeTargetListForBoardingParty(gActiveUnit);
	if (CanBridgeOnCurrentMap() &&
		GetTargetListSize() > 0 &&
		SkillTester(gActiveUnit, BoardingPartyID_Link)
		) return MCA_USABLE;
	return MCA_NONUSABLE;
}

int BoardingPartyEffect(MenuProc* menu, MenuCommandProc* menuItem) {
	//start selection with boarding party target list
	
	ClearBG0BG1();
	
	MakeTargetListForBoardingParty(gActiveUnit);
	
	StartTargetSelection(&gSelectInfo_BoardingParty);
	
	return ME_DISABLE | ME_END | ME_PLAY_BEEP;
}

void BoardingPartySelection_OnInit(TargetSelectionProc* menu) {
    StartBottomHelpText((Proc*)menu, GetStringFromIndex(BoardingPartySubtitleHelpTextID_Link)); 
}



int BoardingPartySelection_OnSelect(TargetSelectionProc* proc, TargetEntry* target) {

    gActionData.xOther = target->x;
    gActionData.yOther = target->y;

    gActionData.unitActionType = UNIT_ACTION_BOARDINGPARTY;

    return ME_DISABLE | ME_END | ME_PLAY_BEEP | ME_CLEAR_GFX;
}

struct DynamicTileChangeTrap {
	u8 xPosition;
	u8 yPosition;
	u8 type;
	u8 ext1;
	u16 tileID;
	u16 ext2;
} typedef DynamicTileChangeTrap;

void BoardingPartyAction() {
	int xPos, yPos;
    gBattleActor.hasItemEffectTarget = 0;

    xPos = gActionData.xOther;
    yPos = gActionData.yOther;
	
	//spawn a trap at the given position
	struct DynamicTileChangeTrap* trap = (DynamicTileChangeTrap*)AddTrap(xPos, yPos, TRAP_DYNAMICTILECHANGE, 0);
	trap->tileID = GetBridgeTileID();
	
	UpdateAllLightRunes();
	
	//possible todo: dust cloud effect at tile it's placed on
	
	PlaySfx(0x3CA);
	//PlaySfx(0x2F9);
}
