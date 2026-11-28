#include "util.h"
#include<iostream>
using namespace std;

// Primitive helper utilities, clamping, and screen control

int clampInt(int val, int minVal, int maxVal){

    if(val < minVal)
    return minVal;
    if(val > maxVal)
    return maxVal;
    else
    return val;

}


void printHeader(const char* title){

    cout<<"========"<<title<<"========"<<endl;

}

bool stringEquals(const char* a, const char* b){

    int count = 0;
     while (a[count] != '\0' && b[count] != '\0' ) {
        if(a[count] != b[count])
        return false;
        count++;
    }

    return a[count] == '\0' && b[count] == '\0';
}

void objectiveDone(const char* objectiveLabel, bool is_done){ //viewer_iface mein used 
    if(is_done)
        std::cout<<" (X) "<<objectiveLabel<<endl;
    else
        std::cout<<" ( ) "<<objectiveLabel<<endl;
}
void clearScreen(){

    cout<<"\033[2J\033[H";
}