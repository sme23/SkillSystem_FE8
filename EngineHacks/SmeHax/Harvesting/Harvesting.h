#include "gbafe.h"

//structs
struct HarvestResult {
  u8 resultID;
  u8 weight;
} typedef HarvestResult;

struct HarvestSet {
	HarvestResult* toolResult[256];
} typedef HarvestSet;

struct HarvestTable {
	HarvestSet* set[256];
} typedef HarvestTable;

//EA literals


//function prototypes
u8 PickHarvestResult(HarvestResult* resultList);
