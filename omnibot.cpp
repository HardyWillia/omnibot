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
#include "coilintensetest1.h"

using namespace std;



int main(){

    //double theta[100];
    //double phi[100];
    int radius = 17;

    
    //Add test cases here

    //pickMapping();
    //magOutput();

    typedef pair<long long, long long> pairll;
    pairll pnts[40] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}};
    
    magOutput(pnts, 29);


    return 0;
}
