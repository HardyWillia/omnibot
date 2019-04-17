//Main Omnibot Program

/* Last edit logs:
    -Willia 02/11/19: Added file and commit format
    -Willia 02/26/19: Started to create test cases for program
    -Willia 03/04/19: Removed need for file and changed to array
    -Willia 03/06/19: Need to add all the possible coordinates for coils after the midterm
    -Willia 04/03/19: Finished initial coil identification, there is a bug in the array
    -Willia 04/16/19: Added more test cases to main file
*/
//#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "coilintense.h"


int main(){

    //used if a file was present
    //magOutput();
    
  //magoutput with read in from control algorithm, this can be called with all cases from control system
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
  
  /* Or if the control algorithm was able to output to a file
  
    int num = 0;
    char *line;
    FILE *fp;
    char datafile[] = "data.txt";

    fp = fopen(datafile, "r");
    if (fp == NULL)
    {
               perror("Error while opening the file.\n");
               exit(EXIT_FAILURE);
        
    }
    while (fgets(line, sizeof(line), fp))
    {

        fscanf(fp, "%lf %lf", &theta[num], &phi[num]);
            magOutput(theta[num], phi[num]);
            num++; 
    }

    fclose(fp);

*/
    return 0;
}
