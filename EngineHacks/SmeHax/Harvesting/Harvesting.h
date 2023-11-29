#include "gbafe.h"

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
	
}

//EA literals
extern u8* HarvestToolTiers[16];

//function prototypes
u8 PickHarvestResult(HarvestResult* resultList);
void InitalizeHarvestToolLevels();

