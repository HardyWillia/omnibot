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

    
    //Add test cases here

    pickMapping();

    magOutput();


    return 0;
}
