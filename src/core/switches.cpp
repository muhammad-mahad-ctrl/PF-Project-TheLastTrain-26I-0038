#include "switches.h"
#include "util.h"
#include "physics.h"

// Door lock mechanics, lifts, and cabinet verification without structures

bool canUseLift1(int fromFloor, int toFloor){
    
    if((fromFloor == 1 || fromFloor == 2) && (toFloor == 1 || toFloor == 2)){
        if(fromFloor - toFloor == 1 || toFloor - fromFloor == 1 )
        return true;
    }
    return false;
}


bool canUseLift2(int fromFloor, int toFloor, bool lift2Operational, int emergencyTripsLeft){

    if((fromFloor == 2 || fromFloor == 4 || fromFloor == 5) && (toFloor == 2 || toFloor == 4 || toFloor == 5) && fromFloor != toFloor){
        if(lift2Operational == 1 || emergencyTripsLeft>0)
        return true;
    }
    return false;
}


bool unlockFloor3Door(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount){

    return hasItem(inventory, inventoryCount, ENT_MASTER_KEY);
}

bool verifyCabinetCode(const char* enteredCode, const bool objectives[NUM_OBJECTIVES]){

    if(objectives[OBJ_CLUE_4] == 1 && objectives[OBJ_CLUE_2] == 1 && objectives[OBJ_CLUE_7] == 1 && stringEquals(enteredCode, "427"))
    return true;
    else
    return false;
    
}

bool installFuseControlPanel(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES], int& score){

    if(hasItem(inventory, inventoryCount, ENT_FUSE) != 1 || objectives[OBJ_FUSE_INSTALLED] == 1) // if no fuse in inventory or alr fuse installed 
    return false;

    removeItem(inventory, inventoryCount, ENT_FUSE);
    objectives[OBJ_FUSE_INSTALLED] = true;
    applyScoreDelta(score, SCORE_INSTALL_FUSE);
    return true;

}


