#include "physics.h"
#include "util.h"

// Movement validation and resource adjustments without structures
void applyResourceDelta(int &energy, int &time, int deltaEnergy, int deltaTime)
{

    energy += deltaEnergy;
    time += deltaTime;
    energy = clampInt(energy, 0, MAX_ENERGY);
    time = clampInt(time, 0, MAX_TIME);
}

void applyScoreDelta(int &score, int deltaScore)
{

    score += deltaScore;
    score = clampInt(score, 0, 520);
}

bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol)
{

    for (int i = 0; i < inventoryCount; i++)
        if (inventory[i] == itemSymbol)
            return true;
    return false;
}

bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int &inventoryCount, char itemSymbol)
{
    if (inventoryCount >= MAX_INVENTORY_CAPACITY)
        return false;

    inventoryCount++;
    inventory[inventoryCount - 1] = itemSymbol;
    return true;
}

bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int &inventoryCount, char itemSymbol)
{

    if (inventoryCount <= 0)
        return false;

    for (int i = 0; i < inventoryCount; i++)
    {
        if (inventory[i] == itemSymbol)
        {
            for (int j = i; j < inventoryCount - 1; j++)
                inventory[j] = inventory[j + 1];
        inventoryCount--;
        return true;
        }
    }
    

    return false;
}

bool isDirectlyConnected(int fromF, int fromR, int toF, int toR, const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1], char &outConnType){
    
    if(fromF <1 || fromF > 5 || toF < 1 || toF > 5 || fromR < 1 || fromR > 4 || toR < 1 || toR > 4 ){ //invalid room or floor
        outConnType = CONN_NONE;
        return false;
    }

    if(fromF == toF && (fromR - toR == 1 || toR - fromR == 1)){ //consecutive jump connection

        int smaller = (fromR < toR) ? fromR : toR;
        int gap = smaller - 1;
        outConnType = horizontalConn[fromF - 1][gap];
        return outConnType != CONN_NONE;
    }

    if(fromR == 1 && toR == 1 && (fromF - toF == 1 || toF - fromF == 1 ) ){ //stairs connection
    
        if ((fromF == 3 && toF == 4) || (fromF == 4 && toF == 3)){
        outConnType = CONN_NONE;
        return false;
        }
        outConnType = CONN_STAIRS;
        return true;
    }

    if(((fromF == 1 && toF == 2) || (fromF == 2 && toF == 1)) && (fromR == 2 || fromR == 3) && (toR == 2 || toR == 3)){ //lift 1

        outConnType = CONN_LIFT1;
        return true;
    }

    if( (fromF == 2 || fromF == 4 || fromF == 5) && (toF == 2 || toF == 4 || toF == 5) && (fromF != toF ) && (fromR == 4 && toR == 4)){ //lift 2

        outConnType = CONN_LIFT2;
        return true;
    }
    outConnType = CONN_NONE;
    return false;
}

bool canTraverse(int targetFloor, int targetRoom, char connType, const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, int emergencyTripsLeft, bool lift2Operational){

(void)targetFloor;
(void)targetRoom;

    if(connType == CONN_NONE || connType == CONN_SOLID_WALL) // wall or none
    return false;

    if(connType == CONN_LOCKED_DOOR ){ // locked door and master key 

        return hasItem(inventory, inventoryCount, ENT_MASTER_KEY);

    }

    if(connType == CONN_LIFT1 || connType == CONN_DOOR || connType == CONN_STAIRS || connType == CONN_WINDOW) // lift1, door, stairs, window allowed
    return true;

    if (connType == CONN_LIFT2) //lift 2
    {
        if (emergencyTripsLeft > 0 || lift2Operational == 1)
        {
            return true;
        }

        return false;

    }
    
    return false;
}