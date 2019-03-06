//Main Omnibot Program

/* Last edit logs:

    -Willia 02/11/19: Added file and commit format
    -Willia 02/26/19: Started to create test cases for program
    -Willia 03/04/19: Removed need for file and changed to array
    -Willia 03/06/19: Need to add all the possible coordinates for coils after the midterm



*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include "veccon.h"
#include "coilintense.h"

using namespace std;


int main(){

    double theta[100];
    double phi[100];
    int radius = 17;
    int coilnum = 1;

    
    //Add test cases here

    pickMapping();

    //Points are on a 7x5 grid, some of the points are listed for testing    
    PointType points[] = { { 0, 3 }, { 1, 1 }, { 2, 2 }, { 3, 2 }, { 0, 0 },
            { 1, 2 }, { 3, 1 }, { 3, 3 } };
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << "Coil " << coilnum << " is coordinates: " << "(" << points[i].x << ", " << points[j].y1 << ")" << endl;
            coilnum++;
        }
    }


    // for(int i = 0; i < 9; i++){
    //     magOutput(points[i], points[i+1]);
    // }


    return 0;
}
