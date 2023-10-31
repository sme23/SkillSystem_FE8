#include "Harvesting.h"

u8 PickHarvestResult(HarvestResult* resultList) {
	int rand = NextRN_N(100) + 1; //value from 1-100
	
	while (true) {
		if (resultList->weight <= rand) return resultList->resultID;
		else rand -= resultList->weight;
		resultList++;
	}
	
}

