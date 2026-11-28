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
