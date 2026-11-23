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








bool loadInitialState(const char *filename, int &playerFloor, int &playerRoom, int &energy, int &time, int &score, char inventory[MAX_INVENTORY_CAPACITY], int &inventoryCount, bool objectives[NUM_OBJECTIVES], int &emergencyTripsLeft){

  return true;
}

bool validateStartingRoom(int startFloor, int startRoom, const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]){

  return true;
}
