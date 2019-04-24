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

/*
//ISR
#define PERIOD_10ms 0x01
#define PERIOD_14ms 0x02
#define PERIOD_19ms 0x03

void Timer_ISR(void)
{
  static char State = PERIOD_10ms;

  switch (State)
  {
      case PERIOD_10ms:
      {
        // Toggle pin;
        // Timer Stop;
        // Change period to 14ms;
        // Timer Start;
        break;
      }
      case PERIOD_14ms:
      {
        // Toggle pin;
        // Timer Stop;
        // Change period to 19ms;
        // Timer Start;
        break;
      }
      case PERIOD_19ms:
      {
        // Toggle pin;
        // Timer Stop;
        // Change period to 10ms;
        // Timer Start;
        break;
      }
      default:
      {
        //Timer_ISR entered undefined state 
        // Make default period 10ms
        break;
      }
  }
}
*/

//Coil Array
int coilcoords[3][25][1] = {
    {0, 0, 0},
    {0, 1, 1},
    {0, 2, 2},
    {0, 3, 3},
    {0, 4, 4},
    {0, 5, 5},
    {1, 0, 6},
    {1, 1, 7},
    {1, 2, 8},
    {1, 3, 9},
    {1, 4, 10},
    {1, 5, 11},
    {2, 0, 12},
    {2, 1, 13},
    {2, 2, 14},
    {2, 3, 15},
    {2, 4, 16},
    {2, 5, 17},
    {3, 0, 18},
    {3, 1, 19},
    {3, 2, 20},
    {3, 3, 21},
    {3, 4, 22},
    {3, 5, 23},
    {4, 0, 24},
    {4, 1, 25},
    {4, 2, 26},
    {4, 3, 27},
    {4, 4, 28},
    {4, 5, 29},
    {5, 0, 30},
    {5, 1, 31},
    {5, 2, 32},
    {5, 3, 33},
    {5, 4, 34},
    {5, 5, 35},
    {6, 0, 36},
    {6, 1, 37},
    {6, 2, 38},
    {6, 3, 39},
    {6, 4, 40},
    {6, 5, 41}
};

int main()
{

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
