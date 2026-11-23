#include "level.h"
#include "util.h"
#include<fstream>
#include<iostream>
#include<string>

using namespace std;

// Modular implementation using primitive arrays for map parsing and verification

bool loadBuildingMap(const char *filename, char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1], char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){

  ifstream building(filename);
    
  if (!building.is_open()) { 
    return false;
  }

//clearing arrays before updating

  for (int i = 0; i < NUM_FLOORS; i++) { //clear all connType = none 
    for (int j = 0; j < ROOMS_PER_FLOOR - 1; j++) {
        horizontalConn[i][j] = CONN_NONE;
    }
  }  


  for (int i = 0; i < NUM_FLOORS; i++) { //clear all entitycount = 0 
    for (int j = 0; j < ROOMS_PER_FLOOR; j++) {
        entityCounts[i][j] = 0;
    }
  }  

  for (int i = 0; i < NUM_FLOORS; i++) { //clear all entities = none 
    for (int j = 0; j < ROOMS_PER_FLOOR; j++) {
        for(int slot = 0; slot < MAX_ENTITIES_PER_ROOM; slot ++)
        roomEntities[i][j][slot] = ENT_NONE;
    }
  }  


//storing connections and entities 

  char line[MAX_LINE_LEN];

  while (building.getline(line, MAX_LINE_LEN)) { //set connType

   if (line[10] == 'F' && line[13] == 'R') {  
      int floor = line[11]-'0'; //ascii conversion '5'/53 -'0'/48 = 5
      horizontalConn[floor-1][0] = line[20]; //conn 1
      horizontalConn[floor-1][1] = line[32]; //conn 2
      horizontalConn[floor-1][2] = line[44]; //conn 3

      if (horizontalConn[floor - 1][1] == CONN_LIFT1) {
        horizontalConn[floor - 1][1] = CONN_NONE;
      }

      building.getline(line, MAX_LINE_LEN); //getting exact next line for items 
      for (int r = 0; r < ROOMS_PER_FLOOR; r++) {
        for (int col = 9 + 12 * r; col <= 19 + 12 * r; col++) {
            if (line[col] != ' ' && entityCounts[floor - 1][r] < MAX_ENTITIES_PER_ROOM) {
              roomEntities[floor - 1][r][entityCounts[floor - 1][r]] = line[col];
              entityCounts[floor - 1][r]++;
            }
        }
      }
    }
  }

  building.close();

  return true;

}


const char* getEntityName(char entitySymbol) {
    if (entitySymbol == ENT_MASTER_KEY) {
        return "Master Key";
    }
    else if (entitySymbol == ENT_ENERGY_PACK) {
        return "Energy Pack";
    }
    else if (entitySymbol == ENT_EMERGENCY_TOOLKIT) {
        return "Emergency Tool Kit";
    }
    else if (entitySymbol == ENT_CLUE_4) {
        return "Clue Digit 4";
    }
    else if (entitySymbol == ENT_FUSE) {
        return "Fuse";
    }
    else if (entitySymbol == ENT_CAT) {
        return "Stranded Cat";
    }
    else if (entitySymbol == ENT_CONTROL_PANEL) {
        return "Control Panel";
    }
    else if (entitySymbol == ENT_LIFT_PASS) {
        return "Lift Pass";
    }
    else if (entitySymbol == ENT_PASSENGER) {
        return "Stranded Passenger";
    }
    else if (entitySymbol == ENT_MEDICAL_KIT) {
        return "Medical Kit";
    }
    else if (entitySymbol == ENT_EMERGENCY_CARD) {
        return "Emergency Card";
    }
    else if (entitySymbol == ENT_CLUE_2) {
        return "Clue Digit 2";
    }
    else if (entitySymbol == ENT_CLUE_7) {
        return "Clue Digit 7";
    }
    else if (entitySymbol == ENT_CABINET_TRAIN_KEY) {
        return "Cabinet / Train Key";
    }
    else if (entitySymbol == ENT_CAT_CARRIER) {
        return "Cat Carrier";
    }
    else if (entitySymbol == ENT_OBSERVATION_TOKEN) {
        return "Observation Token";
    }
    return "NONE";
}


bool loadInitialState(const char *filename, int &playerFloor, int &playerRoom, int &energy, int &time, int &score, char inventory[MAX_INVENTORY_CAPACITY], int &inventoryCount, bool objectives[NUM_OBJECTIVES], int &emergencyTripsLeft){

  ifstream state(filename);
    
  if (!state.is_open()) { 
    return false;
  }

  //set everything initial
  energy = INITIAL_ENERGY;
  time = INITIAL_TIME;
  score = INITIAL_SCORE;
  inventoryCount = 0;
  emergencyTripsLeft = 0;

  for(int i = 0; i < NUM_OBJECTIVES; i++){
    objectives[i] = 0;
  }


  char line[MAX_LINE_LEN];

  while (state.getline(line, MAX_LINE_LEN)){
    cout << line << endl;
  }


  state.close();
  return true;
}

bool validateStartingRoom(int startFloor, int startRoom, const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]){

  return true;
}
