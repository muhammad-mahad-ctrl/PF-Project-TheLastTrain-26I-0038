#include<iostream>
#include "viewer_iface.h"
#include "util.h"
#include "level.h"
using namespace std;

// Terminal UI and dashboard rendering using primitive parameters
void renderDashboard(int playerFloor, int playerRoom, int energy, int time, int score, const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, int emergencyTripsLeft){

    printHeader("Status");
    cout<<"Location: F"<<playerFloor<<"-R"<<playerRoom<<endl;
    cout<<"Resources: "<<endl;
    cout<<"Energy: "<<energy<<" Time: "<<time<<" Emergency Trips Left: "<<emergencyTripsLeft<<" Score: "<<score<<endl;
    cout<<"Inventory: "<<inventoryCount<<endl;

    for(int i =0; i<inventoryCount; i++){
        cout<<getEntityName(inventory[i])<<" ("<<inventory[i]<<")";
    }
    cout<<endl;
}

void renderRoomDetails(int floor, int room, const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCount){

    if(floor < 1 || floor > 5 || room < 1 || room > 4){
        cout<<"Invalid Room!";
        return;
    }
    cout<<"Room: F"<<floor<<"-R"<<room<<endl;
    
    int display = 0;
    for(int i = 0; i < entityCount; i++) {
        if(roomEntities[floor - 1][room - 1][i] == ENT_CLUE_2 || roomEntities[floor - 1][room - 1][i] == ENT_CLUE_4 || roomEntities[floor - 1][room - 1][i] == ENT_CLUE_7)
        continue;
        display++;
        cout<<roomEntities[floor - 1][room - 1][i]<<" - "; //entity ka symbol
        cout<<" "<<getEntityName(roomEntities[floor - 1][room - 1][i])<<endl; //symbol pass horha
    }
    if(display == 0) cout<<"Nothing visible here :)"<<endl; //hidden 2,4,7 clues ky liye


}


void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES]){

    objectiveDone("Master Key", objectives[OBJ_MASTER_KEY]);
    objectiveDone("Clue Digit 4", objectives[OBJ_CLUE_4]);
    objectiveDone("Clue Digit 2", objectives[OBJ_CLUE_2]);
    objectiveDone("Clue Digit 7", objectives[OBJ_CLUE_7]);
    objectiveDone("Cabinet Unlocked", objectives[OBJ_CABINET_UNLOCKED]);
    objectiveDone("Train Key", objectives[OBJ_TRAIN_KEY]);
    objectiveDone("Fuse Collected", objectives[OBJ_FUSE_COLLECTED]);
    objectiveDone("Fuse Installed", objectives[OBJ_FUSE_INSTALLED]);
    objectiveDone("Lift Pass", objectives[OBJ_LIFT_PASS]);
    objectiveDone("Lift 2 Active", objectives[OBJ_LIFT2_ACTIVE]);
    objectiveDone("Passenger Rescued", objectives[OBJ_PASSENGER_RESCUED]);
    objectiveDone("Cat Carrier", objectives[OBJ_CAT_CARRIER]);
    objectiveDone("Cat Rescued", objectives[OBJ_CAT_SECURED]);
    objectiveDone("Train Prepared", objectives[OBJ_TRAIN_PREPARED]);
    
}


void renderAsciiBuilding(int playerFloor, int playerRoom){

    for(int floor = NUM_FLOORS; floor >= 1; floor-- ){
        for(int room = 1; room <= ROOMS_PER_FLOOR; room++){
            std::cout<< (floor == playerFloor && room == playerRoom ? "[U]" : "[ ]"); //agar player he to U
        }
        std::cout<<endl;
    }
}