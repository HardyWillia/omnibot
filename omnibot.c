//Main Omnibot Program

/* Last edit logs:
    -Willia 02/11/19: Added file and commit format
    -Willia 02/26/19: Started to create test cases for program
    -Willia 03/04/19: Removed need for file and changed to array
    -Willia 03/06/19: Need to add all the possible coordinates for coils after the midterm
    -Willia 04/03/19: Finished initial coil identification, there is a bug in the array
    -Willia 04/16/19: Added more test cases to main file
    -Willia 04/18/19: Cleaned code to remove any unnecessary items
*/
//#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "coilintense.h"


int main(){

    
  //magOutput with read in from control algorithm
  //Equations from control algorithm
    /*
    torquetheta = sin(PI/2 – thetat) * 0.5003 + (0.127 * ((PI /2 – thetat) -1) *  thetaprimet + 0.9738 * (PI/2  - thetat);
    torquephi  = (0.127 * ((π /2 – thetat) -1) * phiprimet 	
  */

    magOutput(0, 4.18);
    magOutput(0.84, 5.23);
    magOutput(1.7, 4.71);
    magOutput(0.77, 3.1);
    magOutput(2.093, 0);
    magOutput(0.784, 5.3);
    magOutput(1.57, 4.71);
    magOutput(0, 3.14);
    magOutput(2.03, 0);
    magOutput(2.55, 2.093);
    magOutput(0.51, 4.8);
    magOutput(2.3, 2.3);
    magOutput(0.74, 5);
  

    return 0;
}
