#include "simulator.h"
#include "physics.h"
#include "switches.h"
#include "logger.h"
#include "viewer_iface.h"
#include "level.h"
#include "util.h"
#include<iostream>



void runSimulation(int& playerFloor, int& playerRoom, int& energy, int& time, int& score, char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft, char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1], char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]) {
    
      while (true)
      {
            std::cout<<"Enter Starting Floor:"<<std::endl;
            std::cin>>playerFloor;
            std::cout<<"Enter Starting Room:"<<std::endl;
            std::cin>>playerRoom;

            if(!std::cin){return;} //agar invalid input he

            if(!validateStartingRoom(playerFloor, playerRoom, horizontalConn)){
               std::cout<<"Enter Valid Location!"<<std::endl;
               continue;
            }   
            break;
      }
      
      //loop jab tk end conditions
      while(true){
            
            //lift 2
            bool lift2Operational = objectives[OBJ_FUSE_INSTALLED] && objectives[OBJ_LIFT_PASS];
            objectives[OBJ_LIFT2_ACTIVE] = lift2Operational;
            
            std::cout << "\n=============================================\n";
            
            renderDashboard(playerFloor, playerRoom, energy, time, score, inventory, inventoryCount, emergencyTripsLeft);
            renderRoomDetails(playerFloor, playerRoom, roomEntities, entityCounts[playerFloor-1][playerRoom-1]);
            renderAsciiBuilding(playerFloor, playerRoom);
       
            //ask action
            char action; //int action mein invalid par exit horha tha loop sy
            std::cout<<"Action (1 Move    2 Inspect    3 Collect    4 Use    5 Unlock cabinet    6 Save    7 Quit): "<<std::endl;
            std::cin>>action;

            if(!std::cin) break; 
            
            if(action <'1' || action > '7'){
              std::cout<<"Invalid Action!"<<std::endl;
              continue;      
            }

            if(action == '7') { break; }       
            else if(action == '1'){
               int floor, room;
               std::cout<<"Enter Target Floor: "<<std::endl;
               std::cin>>floor;
               std::cout<<"Enter Target Room: "<<std::endl;
               std::cin>>room;
               handleMoveCommand(floor, room, playerFloor, playerRoom, energy, time, horizontalConn, inventory, inventoryCount, emergencyTripsLeft, lift2Operational);
            }    
            else if(action == '2'){
                  handleInspectCommand(playerFloor, playerRoom, energy, time, roomEntities,  entityCounts[playerFloor-1][playerRoom-1], objectives, score);
            } 
            else if(action == '3'){
                  char itemSymbol;
                  std::cout<<"Collect: "<<std::endl;
                  std::cin>>itemSymbol;
                  handleCollectCommand(itemSymbol, playerFloor, playerRoom, energy, time, score, roomEntities, entityCounts[playerFloor-1][playerRoom-1], inventory, inventoryCount, objectives);
                  
                  //agar emergency card valid and collected he to trips = 3
                  bool is_card_collected = handleCollectCommand(itemSymbol, playerFloor, playerRoom, energy, time, score, roomEntities, entityCounts[playerFloor-1][playerRoom-1], inventory, inventoryCount, objectives);

                  if(itemSymbol == ENT_EMERGENCY_CARD && is_card_collected)
                  emergencyTripsLeft = 3;
            }
      }
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



bool handleInspectCommand(int currentFloor, int currentRoom, int& energy, int& time, const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCount, bool objectives[NUM_OBJECTIVES], int& score){
      
//clues check karta he and returns nothing found agr nhi he

      applyResourceDelta(energy, time, COST_INSPECT_ENERGY, COST_INSPECT_TIME);

      bool found = false;
      for(int i = 0; i < entityCount; i++) {
        if(roomEntities[currentFloor - 1][currentRoom - 1][i] == ENT_CLUE_2 || roomEntities[currentFloor - 1][currentRoom - 1][i] == ENT_CLUE_4 ||                roomEntities[currentFloor - 1][currentRoom - 1][i] == ENT_CLUE_7){

          std::cout<<"Clue Digit Found: "<<roomEntities[currentFloor - 1][currentRoom - 1][i]<<std::endl; 
          found = 1;
            
          if((!objectives[OBJ_CLUE_2] && roomEntities[currentFloor - 1][currentRoom - 1][i] == ENT_CLUE_2)){
            objectives[OBJ_CLUE_2] = 1; applyScoreDelta(score, SCORE_CLUE_FOUND);}

          else if((!objectives[OBJ_CLUE_4] && roomEntities[currentFloor - 1][currentRoom - 1][i] == ENT_CLUE_4)){
            objectives[OBJ_CLUE_4] = 1; applyScoreDelta(score, SCORE_CLUE_FOUND);}
            
          else if((!objectives[OBJ_CLUE_7] && roomEntities[currentFloor - 1][currentRoom - 1][i] == ENT_CLUE_7)){
            objectives[OBJ_CLUE_7] = 1; applyScoreDelta(score, SCORE_CLUE_FOUND);}
            }
      }

      if(!found)
      std::cout<<"Nothing Found :)"<<std::endl;

      return true;
}




bool handleCollectCommand(char itemSymbol, int currentFloor, int currentRoom, int& energy, int& time, int& score, char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int& entityCount, char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES]){

      for(int i = 0; i < entityCount; i++){
            if(itemSymbol == roomEntities[currentFloor-1][currentRoom-1][i]){
                  
                  if(itemSymbol == ENT_CAT || itemSymbol == ENT_PASSENGER || itemSymbol == ENT_CLUE_2 || itemSymbol == ENT_CLUE_4 || itemSymbol == ENT_CLUE_7 || itemSymbol == ENT_CONTROL_PANEL || itemSymbol == ENT_CABINET_TRAIN_KEY){
                        std::cout<<"Can't Pick this item!"<<std::endl;
                        return false;
                  }

                  if(inventoryCount >= MAX_INVENTORY_CAPACITY){
                        std::cout<<"Inventory Full!"<<std::endl;
                        return false;
                  }
                  
                  applyResourceDelta(energy, time, COST_ITEM_PICKUP_ENERGY, COST_ITEM_PICKUP_TIME);

                  if(itemSymbol == ENT_ENERGY_PACK){
                        applyResourceDelta(energy, time, BONUS_ENERGY_PACK, 0);
                        std::cout<<"Energy +"<<BONUS_ENERGY_PACK<<std::endl; 
                  }
                  else if(itemSymbol == ENT_EMERGENCY_TOOLKIT){
                        applyResourceDelta(energy, time, BONUS_EMERGENCY_TOOLKIT, 0);
                        std::cout<<"Energy +"<<BONUS_EMERGENCY_TOOLKIT<<std::endl; 
                  }
                  else if(itemSymbol == ENT_OBSERVATION_TOKEN){
                        applyResourceDelta(energy, time, 0, BONUS_OBSERVATION_TOKEN);
                        std::cout<<"Time +"<<BONUS_OBSERVATION_TOKEN<<std::endl; 
                  }
                  else {
                        addItem(inventory, inventoryCount, itemSymbol); 
                        if (itemSymbol == ENT_MASTER_KEY)  { objectives[OBJ_MASTER_KEY] = true;   applyScoreDelta(score, SCORE_KEY_COLLECT);}
                        if (itemSymbol == ENT_FUSE)        { objectives[OBJ_FUSE_COLLECTED] = true; }
                        if (itemSymbol == ENT_LIFT_PASS)   { objectives[OBJ_LIFT_PASS] = true;    applyScoreDelta(score, SCORE_LIFT_PASS); }
                        if (itemSymbol == ENT_CAT_CARRIER) { objectives[OBJ_CAT_CARRIER] = true; }
                  }

                  
                  //remove item from room 
                  for(int j = i; j < entityCount - 1; j++){
                        roomEntities[currentFloor-1][currentRoom-1][j] = roomEntities[currentFloor-1][currentRoom-1][j+1]; 
                  }
                  entityCount--;
                  return true;
            }
      }
      
      std::cout<<"Item Not Here!"<<std::endl;
      return false;
}



bool handleUseCommand(char itemSymbol, int currentFloor, int currentRoom, int& energy, int& time, int& score, char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES]){

                    return true;
                   }



bool handleUnlockCabinetCommand(const char* code, int currentFloor, int currentRoom, bool objectives[NUM_OBJECTIVES], int& score,  char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int& entityCount){

                    return true;
                   }



bool checkEndConditions(int energy, int time, const bool objectives[NUM_OBJECTIVES]){

                    return true;
                   }