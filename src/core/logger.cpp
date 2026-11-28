#include "logger.h"
#include "util.h"
#include <fstream>
#include<iostream>
using namespace std;


void writeGameSummaryReport(const char* filename, int score, int remainingEnergy, int remainingTime, const bool objectives[NUM_OBJECTIVES], bool victory){

    ofstream summary(filename);
    
    if(!summary.is_open()) {
        cout<<"Couldn't open file!"<<endl;
        return;
    }

    summary<<"===Game Summary==="<<endl;
    if(victory)
    summary<<"Result: Victory"<<endl;
    else
    summary<<"Result: Lost"<<endl;
    summary<<"Energy: "<<remainingEnergy<<endl;
    summary<<"Time: "<<remainingTime<<endl;
    summary<<"Score: "<<score<<endl;
    summary<<"Objectives: "<<endl;

    if(objectives[OBJ_MASTER_KEY])  summary<<" (X) " <<"Master Key"<< std::endl;
    else  summary<<" ( ) " <<"Master Key"<< std::endl;

    if(objectives[OBJ_CLUE_2])  summary<<" (X) " <<"Clue Digit 2"<< std::endl;
    else  summary<<" ( ) " <<"Clue Digit 2"<< std::endl;

    if(objectives[OBJ_CLUE_4])  summary<<" (X) " <<"Clue Digit 4"<< std::endl;
    else  summary<<" ( ) " <<"Clue Digit 4"<< std::endl;

    if(objectives[OBJ_CLUE_7])  summary<<" (X) " <<"Clue Digit 7"<< std::endl;
    else  summary<<" ( ) " <<"Clue Digit 7"<< std::endl;

    if(objectives[OBJ_CABINET_UNLOCKED])  summary<<" (X) " <<"Cabinet Unlocked"<< std::endl;
    else  summary<<" ( ) " <<"Cabinet Unlocked"<< std::endl;

    if(objectives[OBJ_TRAIN_KEY])  summary<<" (X) " <<"Train Key"<< std::endl;
    else  summary<<" ( ) " <<"Train Key"<< std::endl;

    if(objectives[OBJ_FUSE_COLLECTED])  summary<<" (X) " <<"Fuse Collected"<< std::endl;
    else  summary<<" ( ) " <<"Fuse Collected"<< std::endl;

    if(objectives[OBJ_FUSE_INSTALLED])  summary<<" (X) " <<"Fuse Installed"<< std::endl;
    else  summary<<" ( ) " <<"Fuse Installed"<< std::endl;

    if(objectives[OBJ_LIFT_PASS])  summary<<" (X) " <<"Lift Pass"<< std::endl;
    else  summary<<" ( ) " <<"Lift Pass"<< std::endl;

    if(objectives[OBJ_LIFT2_ACTIVE])  summary<<" (X) " <<"Lift 2 Active"<< std::endl;
    else  summary<<" ( ) " <<"Lift 2 Active"<< std::endl;

    if(objectives[OBJ_PASSENGER_RESCUED])  summary<<" (X) " <<"Passenger Rescued"<< std::endl;
    else  summary<<" ( ) " <<"Passenger Rescued"<< std::endl;

    if(objectives[OBJ_CAT_CARRIER])  summary<<" (X) " <<"Cat Carrier"<< std::endl;
    else  summary<<" ( ) " <<"Cat Carrier"<< std::endl;

    if(objectives[OBJ_CAT_SECURED])  summary<<" (X) " <<"Cat Secured"<< std::endl;
    else  summary<<" ( ) " <<"Cat Secured"<< std::endl;

    if(objectives[OBJ_TRAIN_PREPARED])  summary<<" (X) " <<"Train Prepared"<< std::endl;
    else  summary<<" ( ) " <<"Train Prepared"<< std::endl;

     summary.close();
}


bool saveGameStateToFile(const char* filename, int playerFloor, int playerRoom, int energy, int time, int score, const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, const bool objectives[NUM_OBJECTIVES], int emergencyTripsLeft, const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], const int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){

    ofstream save(filename);
    
    if(!save.is_open()) {
        cout<<"Couldn't open file!"<<endl;
        return false;
    }

    save<<"LASTTRAIN_SAVE"<<endl;
    save<<playerFloor<<" "<<playerRoom<<endl;
    save<<energy<<" "<<time<<" "<<score<<endl;
    save<<emergencyTripsLeft<<endl;
    
    //inventory
    save<<inventoryCount<<" ";
    for(int i = 0; i < inventoryCount; i++ )
    save<<inventory[i]<<" ";
    save<<endl;

    //objectives
    for(int i = 0; i<NUM_OBJECTIVES; i++)
    save<<objectives[i]<<" ";
    save<<endl;

    //room details
    for(int floor = 0; floor < NUM_FLOORS; floor++){
        for(int room = 0; room < ROOMS_PER_FLOOR; room++){
            save<<entityCounts[floor][room]<<" ";
            for(int ent = 0; ent <entityCounts[floor][room]; ent++)
            save<<roomEntities[floor][room][ent]<<" ";
            save<<endl;
        }

    }
    save.close();
    return true;
}


bool loadGameStateFromFile(const char* filename, int& playerFloor, int& playerRoom, int& energy, int& time, int& score, char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft, char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){

    ifstream load(filename);

    if(!load.is_open()) {
        cout<<"Couldn't open file!"<<endl;
        return false;
    }

    char line[MAX_LINE_LEN];

    load.getline(line, MAX_LINE_LEN);

    if (!stringEquals(line, "LASTTRAIN_SAVE")) {
        return false;
    }

    load>>playerFloor>>playerRoom;
    load>>energy>>time>>score>>emergencyTripsLeft;
    load>>inventoryCount;
    
    //inventory items
    for(int i = 0; i < inventoryCount; i++)
    load >> inventory[i];

    for(int i = 0; i < NUM_OBJECTIVES; i++)
    load >> objectives[i];

    for (int floor = 0; floor < NUM_FLOORS; floor++) {
        for (int room = 0; room < ROOMS_PER_FLOOR; room++) {
            load>>entityCounts[floor][room];

            for(int ent = 0; ent<entityCounts[floor][room]; ent++)
            load>>roomEntities[floor][room][ent];    
                     
        }
    }

    load.close();
    return 1;
}