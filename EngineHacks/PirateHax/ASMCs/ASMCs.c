#include "gbafe.h"

#define DesiderioCharId 3

void A3ReturnLogDroppedStatusASMC(){

    gEventSlot[0xC] = 0;

    u8 action = gActionData.unitActionType;

    Unit* target = GetUnit(gActionData.targetIndex);

    if (action != UNIT_ACTION_DROP || target->pClassData->number != 0x8C){
        return; //if action was not drop or target was not log, return 0 (nothing happens)
    }

    if (target->xPos == 0 && target->yPos == 14){

    }
    else if (target->xPos == 10 && target->yPos == 9){

    }
    else if (target->xPos == 18 && target->yPos == 0){

    }
    else{
        return; //if the target wasn't dropped at one of these three pos, return 0
    }

    Unit* currentLog;
    u8 logNum = 0; //number of logs on ruins

    for (int i = FACTION_GREEN + 0x1; i < FACTION_GREEN + 0x4; i++){
        currentLog = gUnitLookup[i]; //whatever log we're at
        if (currentLog->pClassData->number != 0x8C){ 
            break; //not the log class so not something we care about
        }
        if (currentLog->xPos == 0 && currentLog->yPos == 14){
            logNum++; //first pos
        }
        else if (currentLog->xPos == 10 && currentLog->yPos == 9){
            logNum++; //second pos
        }
        else if (currentLog->xPos == 18 && currentLog->yPos == 0){
            logNum++; //third pos
        }
        else{

        }
    }
    
    gEventSlot[0xC] = logNum;
}

void EyeForAnEyeResetASMC(){
    Unit* unit = GetUnitByCharId(DesiderioCharId);
    if (unit->state & US_UNAVAILABLE){
        //don't do anything because he's goneski
    }
    else{
        unit->supports[5] = 0; //last support byte set to be 0
    }
}