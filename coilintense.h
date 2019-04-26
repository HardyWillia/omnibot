//Coil Intensity Test Program
#ifndef COILINTENSE_H
#define COILINTENSE_H

/* Last edit logs:
    -Willia 02/11/19: Added base pseudocode from diagram
    -Willia 02/26/19: Added function for computing magnitude
    -Willia 03/04/19: Debugging the code to determine why the values are printing incorrectly
    -Willia 04/01/19: Added coilintensetest as a test program for further improvements
    -Willia 04/03/19: Finished initial coil identification, there is a bug in the array
    -Willia 04/08/19: Added more conditions based on coil positions
    -Willia 04/14/19: Removed while loop that called file to work better with control algorithm
    -Willia 04/15/19: Reduced timing of program to 16.62 milliseconds
    -Willia 04/16/19: Added better current mag calculation instead of manual input
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "adc.h"

#define PI 3.14159265

//ISR
#define PERIOD_10ms 0x01

//Coil Array
int coilcoords[42][3] =
   { {0, 0, 0},
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

void matchCoil(int val1, int val2)
{

  int i, j, thirdParam;
  for (i = 0; i < 41; ++i)
  {
    for (j = 0; j < 2; ++j)
    {
       if(val1 == coilcoords[i][0] && val2 == coilcoords[i][1]){
		      thirdParam = coilcoords[i][2];       
 		      printf("Coil(%d , %d) = %d\n", val1, val2, thirdParam);
              ms_delay(5000);
              printf( "\f" ); 
		      break;
	      }
    }
  }
}

//Global variables
double theta;
double phi;
double intendvec;
double farcoilforce;
double closecoilforce;
double vecmag;
double farcoilmag;
double closecoilmag;
int intensity[2];
int radius = 17;

double angle, result, x, y;

//Intensify the furthest coil to 100%, always (until a better method is found)
//Calculate the force of the closest coil
//Calculate the current vector magnitude based on provided theta and phi from control
//Multiply the magnitudes of force at both coils
//Get the magnitudes for each coil
//Output the magnitudes (determines coil intensity for switching)


//Output the magnitude
double magOutput(double theta, double phi)
{

    double mapping[2];
    double mapping2[2] = {x, y};
    double mapping1[2] = {x, y};

    //Conditions for Mapping 2 (Bullseye)
    if (theta < PI / 4)
    {
        x = sqrt(pow(radius, 2) - pow(cos(theta), 2) * pow(radius, 2)) * cos(phi);
        y = sqrt(pow(radius, 2) - pow(cos(theta), 2) * pow(radius, 2)) * sin(phi);

        mapping[2] = mapping2[2];
       // printf("\nMapping 2 has been chosen\n");
        /*
ms_delay(5000);
   printf( "\f" );*/
        if (x < 0)
        {
            x *= -1;
            y *= -1;
            result = atan2(y, x);
            angle = result * 180 / PI;
            if (angle < 0)
            {
                angle = angle + 180;
            }
            //printf("The angle is: %0.1lf\n", angle);
            /*
                ms_delay(5000);
   printf( "\f" ); */
        }
        else
        {
            result = atan2(y, x) * 180 / PI;
            angle = fabs(result);
            //printf("The angle is: %0.1lf\n", angle);
            /* 
                ms_delay(5000);
   printf( "\f" ); */
        }
    }

    else
    {
        //Conditions for Mapping 1 (grid)
        x = theta;
        y = phi;
        mapping[2] = mapping1[2];
       // printf("\nMapping 1 has been chosen\n");
        /*
            ms_delay(5000);
   printf( "\f" ); */
        if (x < 0)
        {
            x *= -1;
            y *= -1;
            result = atan2(y, x);
            angle = result * 180 / PI;
            if (angle < 0)
            {
                angle = angle + 180;
            }
           // printf("The angle is: %0.1lf\n", angle);
            /* 
                ms_delay(5000);
                printf( "\f" ); */
        }
        else
        {
            result = atan2(y, x) * 180 / PI;
            angle = fabs(result);
          //  printf("The angle is: %0.0lf\n", angle);
            /*
                ms_delay(5000);
   printf( "\f" );*/
        }
    }
    int currentposx = x;
    int currentposy = y;
    int closex, closey;
    //printf("Your current position: (%d , %d) \n", currentposx, currentposy);
    /*
        ms_delay(5000);
   printf( "\f" ); */
   // currentposition(a, b);
    int n = 2;
    int i;
    //Sort through the coordinates to find the closest to a given point
    for (i = 1; i < n; ++i)
    {

        if (currentposx >= 7 || currentposy < 0)
        {
            closex = 1;
            closey = 5;

            if (angle >= 0.0 && angle < 40.0)
            {
                currentposx += 1;
                closex = currentposx;
            }
            else if (angle > 40.0 && angle <= 90.0)
            {
                currentposy += 1;
                closey = currentposy;
            }
            else if (angle > 90 && angle <= 180)
            {
                currentposx = abs(7 - currentposx);
                currentposy += 2;
                closex = currentposx;
                closey = currentposy;
            }
        }
        else
        {
            currentposx += 1;
            closex = currentposx;
        }
    }

    int farposx = abs(6 - currentposx);
    int farposy = abs(5 - currentposy);
    double val = 30.0;
    farcoilforce = sin(theta) * val;
    closecoilforce = (sin(fabs(theta) * val)) / (sin(fabs(phi)));

    /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W
                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
    */

    vecmag = cos(fabs(theta)) * 100.0 + cos(fabs(phi)) * (closecoilforce);
    int intendedmag = pow(theta, 2) + pow(phi, 2);

    closecoilforce *= intendedmag / vecmag;
    closecoilmag = fabs(closecoilforce) * 100;

    if (closecoilmag != closecoilmag || closecoilmag > 100.0)
    {
        //printf("The vector cannot be re-created \n");
                /*
           ms_delay(5000);
            printf( "\f" ); */
        //printf("ONLY intensify the closest coil at position (%d, %d) to: %d\n", closex, closey, 100);
        /*
           ms_delay(5000);
            printf( "\f" ); */
        closex = closex;
        closey = closey;
        closecoilmag = 100.0;
        matchCoil(closex, closey);
        printf("CloseCoil Only (%d,%d):\n%0.0lf", closex, closey, closecoilmag);
           ms_delay(5000);
            printf( "\f" ); 
        
    }
    else if (closecoilmag == 0.0)
    {
        //printf("ONLY intensify the furthest coil at position (%d, %d) to: %d\n", farposx, farposy, 100);
        /*   
            ms_delay(5000);
            printf( "\f" ); */
        farposx = farposx;
        farposy = farposy;
        farcoilmag = 100.0;
        matchCoil(farposx, farposy);
        printf("FarCoil Only (%d,%d):\n%0.0lf", farposx, farposy, farcoilmag);
           ms_delay(5000);
           printf( "\f" );
 
    }
    else
    {
       // printf("Intensify the furthest coil at position (%d, %d) to: %d\n", farposx, farposy, 100);
        /* 
            ms_delay(5000);
            printf( "\f" ); 
        */
         //   printf ( "Intensify the closest coil at position (%d, %d) to: %0.0lf\n", closex, closey, closecoilmag);
        /* ms_delay(5000);
         printf( "\f" ); */
        farcoilmag = 100.0;
        farposx = farposx;
        farposy = farposy;
        matchCoil(farposx, farposy);
        
        closecoilmag = closecoilmag;
        closex = closex;
        closey = closey;
        matchCoil(closex, closey);
        
        printf("FarCoil (%d,%d):\n%0.0lf", farposx, farposy, farcoilmag);
        ms_delay(5000);
        printf( "\f" );

        printf("CloseCoil (%d,%d):\n%0.0lf", closex, closey, closecoilmag);
           ms_delay(5000);
            printf( "\f" );
    }
    
    return closex, closey, closecoilmag, farposx, farposy, farcoilmag;
}

void Timer_ISR(void)
{
    static char State = PERIOD_10ms;
    switch (State)
    {
    case PERIOD_10ms:
    {
        //Toggle PIN 
        //SENSOR4 = 1;
        
        // Timer Stop;
        T1CON = 0x8030; //setting Timer1
        TMR1 = 0;
        // ADC sampling -- get from Aladdin's code
        //Average the signals
        
        int adcnum = 10;
        int sum1 = 0;
        int sum2 = 0;
        int sum3 = 0;
        int finalsum = 0; 
        int avg;
        
        //Dan's function
        
        
            //Lia's Function
                //Test speed of pic processing magOutput program
        //clock_t start = clock();
         //magOutput with read in from control algorithm
          //Equations from control algorithm when integration is complete
                /*
                torquetheta = sin(PI/2 ? thetat) * 0.5003 + (0.127 * ((PI /2 ? thetat) -1) *  thetaprimet + 0.9738 * (PI/2  - thetat);
                torquephi  = (0.127 * ((? /2 ? thetat) -1) * phiprimet 	
              */

            magOutput(0, 4.18);
           // magOutput(0.84, 5.23);
           // magOutput(1.7, 4.71);
//            magOutput(0.77, 3.1);
//            magOutput(2.093, 0);
//            magOutput(0.784, 5.3);
//            magOutput(1.57, 4.71);
//            magOutput(0, 3.14);
//            magOutput(2.03, 0);
//            magOutput(2.55, 2.093);
//            magOutput(0.51, 4.8);
//            magOutput(2.3, 2.3);
//            magOutput(0.74, 5);
        /*double dur = (clock() - start);
        printf("test done");
          ms_delay(5000);
     printf( "\f" ); 
      ms_delay(5000);
        printf("Dur: %d ",dur);
        ms_delay(5000);
        printf( "\f" ); */
        
                //Alex's Function
        
        int i;
        //Get values from ADC
            for(i = 1; i <= adcnum; i++){
                //pin 22 gets toggled
                ADC_ChannelEnable(SENSOR1);
                int adc1 = ADC_ReadData(SENSOR1); 
                //pin 23 gets toggled
                ADC_ChannelEnable(SENSOR2);
                int adc2 = ADC_ReadData(SENSOR2); 
                //pin 24 get toggled
                ADC_ChannelEnable(SENSOR3);
                int adc3 = ADC_ReadData(SENSOR3); 
                    //Get sum of all readings per sensor
                    sum1 += adc1;
                    sum2 += adc2;
                    sum3 += adc3;
                    finalsum = sum1 + sum2 + sum3;
            }
        avg = finalsum / adcnum;
        printf("Average: %d\n", avg);
         ms_delay(5000);
     printf( "\f" ); 
        // Timer Start;
        TMR1 = 1;
        break;
    }
    default:
    {
        ms_delay(10);
        break;
    }
    }
}


#endif /* COILINTENSE_H */
