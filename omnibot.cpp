//Main Omnibot Program

/* Last edit logs:

    -Willia 02/11/19: Added file and commit format
    -Willia 02/26/19: Started to create test cases for program



*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include "veccon.h"
#include "coilintense.h"

using namespace std;


int main(){

    double furthestcoil;
    double closestcoil;
    double x;
    double y;
    double theta[100];
    double phi[100];
    int radius = 17;
    double coilAddress[300];
    //Add test cases here

    pickMapping();
    //findDistance();
    returnAngle();

    cout << "What is the angle of the furthest coil?: ";
    cin >> furthestcoil;

    cout << "What is the angle of the closest coil?: ";
    cin >> closestcoil;

    magOutput(furthestcoil, closestcoil);



    return 0;
}