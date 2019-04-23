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

#define PI 3.14159265

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
        //Conditons for Mapping 1 (grid)
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
        
        closecoilmag = closecoilmag;
        closex = closex;
        closey = closey;
    }
    
    return closex, closey, closecoilmag, farposx, farposy, farcoilmag;
}

#endif /* COILINTENSE_H */
