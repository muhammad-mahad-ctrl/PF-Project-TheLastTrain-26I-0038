#include "simulator.h"
#include "physics.h"
#include "switches.h"
#include "logger.h"
#include "viewer_iface.h"
#include "util.h"
#include<iostream>

// Modular simulation loop using primitive variables


void runSimulation(int& playerFloor, int& playerRoom, int& energy, int& time, int& score, char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft, char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1], char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]) {
    

}

bool handleMoveCommand(int targetFloor, int targetRoom,  int& currentFloor, int& currentRoom, int& energy, int& time, const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1], const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, int& emergencyTripsLeft, bool lift2Operational){

      char connType; 
      int deltaEnergy = COST_MOVE_ORDINARY_ENERGY, deltaTime = COST_MOVE_ORDINARY_TIME; //default door 

      if(!isDirectlyConnected(currentFloor, currentRoom, targetFloor, targetRoom, horizontalConn, connType)){
            std::cout<<"No direct connection!"<<std::endl;
            return false;
      }

      if(!canTraverse(targetFloor, targetRoom, connType, inventory, inventoryCount, emergencyTripsLeft, lift2Operational)){
            std::cout<<"Cannot Traverse!"<<std::endl;
            return false;
      }

      //decide delta time energy
      if(connType == CONN_WINDOW)                              { deltaEnergy = COST_MOVE_WINDOW_ENERGY; deltaTime = COST_MOVE_WINDOW_TIME;}
      else if(connType == CONN_LIFT1 || connType == CONN_LIFT2){ deltaEnergy = COST_MOVE_LIFT_ENERGY; deltaTime = COST_MOVE_LIFT_TIME;}

      applyResourceDelta(energy, time, deltaEnergy, deltaTime);

      if(connType == CONN_LIFT2 && lift2Operational != 1)   emergencyTripsLeft--;

      //target location current ban jayegi
      currentFloor = targetFloor;
      currentRoom = targetRoom;
                        
return true;
}

bool handleInspectCommand(int currentFloor, int currentRoom,
                          int& energy, int& time,
                          const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                          int entityCount,
                          bool objectives[NUM_OBJECTIVES], int& score){

                    return true;
                   }

bool handleCollectCommand(char itemSymbol, int currentFloor, int currentRoom,
                          int& energy, int& time, int& score,
                          char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                          int& entityCount,
                          char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                          bool objectives[NUM_OBJECTIVES]){

                    return true;
                   }

bool handleUseCommand(char itemSymbol, int currentFloor, int currentRoom,
                      int& energy, int& time, int& score,
                      char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                      bool objectives[NUM_OBJECTIVES]){

                    return true;
                   }

bool handleUnlockCabinetCommand(const char* code, int currentFloor, int currentRoom,
                                bool objectives[NUM_OBJECTIVES], int& score,
                                char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                                int& entityCount){

                    return true;
                   }

bool checkEndConditions(int energy, int time, const bool objectives[NUM_OBJECTIVES]){

                    return true;
                   }