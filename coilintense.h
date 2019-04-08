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
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265

//Global variables
double theta[100];
double phi[100];
double intendvec;
double farcoilforce;
double closecoilforce;
double vecmag;
double farcoilmag;
double closecoilmag;
int intensity[2];
int radius;

int num = 0;
double angle, result, x, y;


//Intensify the furthest coil to 100%
//Calculate the force of the closest coil
//Calculate the current vector magnitude
//Multiply the magnitudes of force at both coils
//Get the magnitudes for each coil
//Output the magnitudes (determines coil intensity for switching)


// Points in the Cartesian plane
void currentposition(int currentposx, int currentposy){

    int n = 2;
    int farposx = abs(6 - currentposx);
    int farposy = abs(5 - currentposy);
    int i;
    //Sort through the coordinates to find the closest to a given point
    for (i = 1; i < n; ++i)
    {

        if (currentposx >= 6)
        {
            currentposx = 1;

            if (angle >= 0.0 && angle < 40.0)
            {
                currentposx += 1;
            }
            else if (angle > 40.0 && angle <= 90.0)
            {
                currentposy += 1;
            }
            else if (angle > 90 && angle <= 180)
            {
                currentposx = abs(7 - currentposx);
                currentposy += 2;
            }
        }
        else
        {
            currentposx += 1;
        }

        farcoilforce = sin(theta[num]) * 30;
        closecoilforce = (sin(abs(theta[num]) * 30)) / (sin(abs(phi[num])));

        /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W
                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */

        vecmag = cos(theta[num] * -1) * 100.0 + cos(abs(phi[num])) * (closecoilforce);

        int intendedmag;
        printf ("What is the intended vector magnitude: \n");
        scanf("%d", &intendedmag);

        //farcoilforce *= intendedmag/vecmag;
        //farcoilmag = abs(farcoilforce) * 100;

        closecoilforce *= intendedmag / vecmag;
        closecoilmag = abs(closecoilforce) * 100;

        if (closecoilmag != closecoilmag || closecoilmag > 100.0)
        {
            printf("The vector cannot be re-created\n");
            break;
        }
        //  if (farcoilmag != farcoilmag || farcoilmag > 100.0)
        //  {
        //         printf ( "The vector cannot be re-created\n");
        //  }
        else if (closecoilmag == 0.0)
        {
            printf("ONLY intensify the furthest coil at position (%d, %d) to: %0.2lfc\n", farposx, farposy, 100.0);
            //farcoilmag == 100.0;
        }
        else
        {

            printf("Intensify the furthest coil at position (%d, %d) to: %0.2lfc\n", farposx, farposy, 100.0);

            // printf ( "Intensify the furthest coil ("  farposx  ", "  farposy  ")"
            //       " to: "
            //       setprecision(2)  farcoilmag  "%"  "\n";
            printf ( "Intensify the closest coil at position (%d, %d) to: %0.2lfc\n", currentposx, currentposy, closecoilmag);

        }
    }
}

//Output the magnitude
double magOutput()
{

    double mapping[2];
    double mapping2[2] = {x, y};
    double mapping1[2] = {x, y};
    char line;
    FILE *fp;
    char datafile[] = "data.txt";

    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
               perror("Error while opening the file.\n");
               exit(EXIT_FAILURE);
        
    }
    while (*fgets(line, sizeof(line), fp))
    {

        fscanf(fp, "%lf %lf", &theta[num], &phi[num]);

        //Conditions for Mapping 2 (Bullseye)
        if (theta[num] < PI / 4)
        {
            x = sqrt(pow(radius, 2) - pow(cos(theta[num]), 2) * pow(radius, 2)) * cos(phi[num]);
            y = sqrt(pow(radius, 2) - pow(cos(theta[num]), 2) * pow(radius, 2)) * sin(phi[num]);

            mapping[2] = mapping2[2];
            printf("\nMapping 2 has been chosen\n");

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
                printf("The angle is: %0.2lf\n", angle);
            }
            else
            {
                result = atan2(y, x) * 180 / PI;
                angle = abs(result);
                printf("The angle is: %0.2lf\n", angle);
            }
        }

        else
        {
            //Conditons for Mapping 1 (grid)
            x = theta[num];
            y = phi[num];
            mapping[2] = mapping1[2];
            printf("\nMapping 1 has been chosen\n");
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
                printf("The angle is: %0.2lf\n", angle);
            }
            else
            {
                result = atan2(y, x) * 180 / PI;
                angle = abs(result);
                printf("The angle is: %0.2lf\n", angle);
            }
        }
        printf("Your current position: (%lf , %lf) \n", x, y);
        currentposition(x, y);
        ++num;
        }
    fclose(fp);

}
#endif /* COILINTENSE_H */
