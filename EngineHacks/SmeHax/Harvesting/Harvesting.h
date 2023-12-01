#include "gbafe.h"

//lib stuff
struct HelpBoxInfo;

struct HelpBoxProc
{
    /* 00 */ PROC_HEADER;

    /* 2C */ const struct HelpBoxInfo* info;

    /* 30 */ short xBox;
    /* 32 */ short yBox;
    /* 34 */ short wBox;
    /* 36 */ short hBox;
    /* 38 */ short xBoxInit;
    /* 3A */ short yBoxInit;
    /* 3C */ short xBoxFinal;
    /* 3E */ short yBoxFinal;
    /* 40 */ short wBoxInit;
    /* 42 */ short hBoxInit;
    /* 44 */ short wBoxFinal;
    /* 46 */ short hBoxFinal;
    /* 48 */ short timer;
    /* 4A */ short timerMax;

    /* 4C */ u16 mid;
    /* 4E */ u16 item;

    /* 50 */ u16 moveKey; // move ctrl proc only

    /* 52 */ u8 unk52;

    // NOTE: there's likely more, need to decompile more files
} typedef HelpBoxProc;


struct HelpBoxInfo
{
    /* 00 */ const struct HelpBoxInfo* adjUp;
    /* 04 */ const struct HelpBoxInfo* adjDown;
    /* 08 */ const struct HelpBoxInfo* adjLeft;
    /* 0C */ const struct HelpBoxInfo* adjRight;
    /* 10 */ u8 xDisplay;
    /* 11 */ u8 yDisplay;
    /* 12 */ u16 mid;
    /* 14 */ void(*redirect)(struct HelpBoxProc* proc);
    /* 18 */ void(*populate)(struct HelpBoxProc* proc);
} typedef HelpBoxInfo;

extern HelpBoxInfo gSomeTextRelatedStuff;

extern struct Vec2 gHelpTextOriginTile;

extern void StartHelpBoxExt(const HelpBoxInfo* info, int unk);
extern MenuProc* StartMenu_AndDoSomethingCommands(const MenuDefinition* def, int xSubject, int xTileLeft, int xTileRight);

extern MenuDefinition gMenu_UnitMenu;

#define TILEMAP_INDEX(aX, aY) (0x20 * (aY) + (aX))




//structs
struct HarvestResult {
  u8 resultID;
  u8 weight;
} typedef HarvestResult;

struct HarvestSet {
	HarvestResult* toolResult[16];
} typedef HarvestSet;

struct HarvestTable {
	HarvestSet* set[256];
} typedef HarvestTable;

enum {
	TOOL_STAFF 			= 0, 	// hit things to knock off materials
	TOOL_SCYTHE 		= 1, 	// cut off materials
	TOOL_AXE 			= 2, 	// break things open, take them apart wholly
	TOOL_BUG_NET 		= 3, 	// catch bugs on thing
	TOOL_FISHING_ROD	= 4, 	// catch fish on thing
	TOOL_EXPLOSIVES	 	= 5, 	// blow it up, fire transmutation
	TOOL_ICE_CHARGE		= 6, 	// freeze it, ice transmutation
	TOOL_PINWHEEL		= 7, 	// blow at it, wind transmutation
	TOOL_LIGHTNING_ROD	= 8,	// electrify it, thunder transmutation
	TOOL_SPLASH_BOTTLE 	= 9, 	// make it wet, water transmutation
	TOOL_FERTILIZER		= 10,	// magically grow it, earth transmutation
	TOOL_LIGHTBULB 		= 11, 	// infuse with light, light transmutation
	TOOL_DARKBULB 		= 12, 	// infuse with darkness, dark transmutation
	//there's room for 16 of these if needed

	TRAP_HARVEST_TILE	= 20,
	
	TRAP_EXTDATA_HARVEST_TILE_SET_ID 	= 0, // ID 
	TRAP_EXTDATA_HARVEST_TILE_HARVESTED = 1
	
};

//EA literals
extern u8* HarvestToolTiers[16];
extern HarvestTable HarvestingTable;
extern u16* HarvestToolBuffer[16];

//function prototypes
u8 PickHarvestResult(HarvestResult* resultList);
void InitalizeHarvestToolLevels();
void SetHarvestToolLevel(int tool, int level);
void SetHarvestToolLevelIfHigher(int tool, int level);
int GetHarvestToolLevel(int tool);
HarvestResult* GetHarvestResult(int id, int tool);
void BuildToolList(u16* listPtr, Trap* harvestTile);
void AddHarvestTile_ASMC(Proc* parent);
u8 HarvestMenuHelpBox(MenuProc* menu, MenuCommandProc* menuItem);
u8 HarvestMenu_ButtonBPressed(MenuProc* menu, MenuCommandProc* menuItem);
u8 HarvestMenu_Usability(const MenuCommandDefinition* command, int number);
int HarvestMenu_TextDraw(MenuProc* menu, MenuCommandProc* menuItem);
u8 HarvestMenu_Effect(MenuProc* menu, MenuCommandProc* menuItem);
int HarvestMenu_SwitchIn(MenuProc* menu, MenuCommandProc* menuItem);
int HarvestMenu_SwitchOut(MenuProc* menu, MenuCommandProc* menuItem);
void StartHarvestHelpBox(int x, int y, int tool);
void HbPopulate_AutoTool(HelpBoxProc* proc);

