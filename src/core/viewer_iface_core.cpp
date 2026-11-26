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

    for(int i =0; i<inventoryCount; i++)
        cout<<getEntityName(inventory[i]);
}
