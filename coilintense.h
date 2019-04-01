//Coil Intensity Program
#ifndef COILINTENSE_H 
#define COILINTENSE_H

/* Last edit logs:
    -Willia 02/11/19: Added base pseudocode from diagram
    -Willia 02/26/19: Added function for computing magnitude
    -Willia 03/04/19: Debugging the code to determine why the values are printing incorrectly
*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <cmath>
#include <thread>
#include <fstream>
#include <algorithm>
#include "veccon.h"

#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stack>
#include <stdlib.h>
#include <iomanip>

using namespace std;
#define PI 3.14159265



    //1ST FUNCTION
    //Intensify the furthest coil to 100%
    //Calculate the force of the closest coil
    //Calculate the current vector magnitude
    //Multiply the magnitudes of force at both coils
        //Get the magnitudes for each coil
    //Output the magnitudes (determines coil intensity for switching)

    // Points in the xy-plane
    struct PointType
    {
        double x;
        double y;
        //double y2;
    }; PointType p0;


    // A utility function to return square of distance between p1 and p2
    int dist(PointType p1, PointType p2){
            return (p1.x - p2.x) * (p1.x - p2.x)+ (p1.y - p2.y) * (p1.y - p2.y);
    }

    double magOutput(PointType theta, PointType phi){
	
        double intendvec;
        double farcoil;
        double farcoilforce;
        double closecoilforce;
        double vecmag;
        double farcoilmag;
        double closecoilmag;
        int intensity[2];
        int n;

        std::vector<PointType> points = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}};
        
        //Code to identify the furthest and closest coil.
        int ymin = points[0].y, min = 0;
        int xmax = points[0].x, maximum = 0;

        // Go through all points and find one with least y value
        for (int i = 1; i < n; i++)
        {
            int y = points[i].y;

            if ((y < ymin) || (ymin == y && points[i].x < points[min].x)){
                ymin = points[i].y, min = i;
                xmax = points[i].x, maximum = i;
            }

                farcoil = sin(xmax) * 30;
                closecoilforce = (sin(abs(xmax) * 30)) / (sin(abs(ymin)));

                /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W
                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */
                vecmag = cos(abs(xmax)) * max(farcoilforce, 100.0) + cos(abs(ymin)) * (closecoilforce);
        }

    
        PointType ycoor1;
        PointType ycoor2;
        cout << "What is the intended vector (angle and magnitude): ";
        cin >> ycoor1.y >> ycoor2.y;

        farcoilforce *= ycoor2.y / vecmag;
        closecoilforce *= ycoor1.y / vecmag;

        farcoilmag = abs(farcoilforce) * 100;
        closecoilmag = abs(closecoilforce) * 100;


        if(closecoilmag != closecoilmag || closecoilmag > 100.0){
            cout << endl << "The vector cannot be re-created" << endl;
        } else {
            cout << "Intensity for furthest coil: " << "100%" << endl;
            cout << "Intensity for closest coil: " << xmax << ", " << ymin << "at: " << setprecision(2) << closecoilmag << " %" << endl;
        }

        return farcoilmag, closecoilmag;
    }



#endif /* VECCON_H */