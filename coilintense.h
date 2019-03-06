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
        double y1;
        double y2;
    };

    PointType p0;
 

    double magOutput(PointType theta, PointType phi){
	
        double intendvec;
        double farcoil;
        double farcoilforce;
        double closecoilforce;
        double vecmag;
        double farcoilmag;
        double closecoilmag;
        int intensity[2];

        farcoil = sin(theta.x) * 30;
        closecoilforce = (sin(abs(theta.x) * 30))/(sin(abs(phi.y1)));

                
                /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W

                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */
        vecmag = cos(abs(theta.x)) * max(farcoilforce, 100.0) + cos(abs(phi.y2)) * (closecoilforce);

        //cout << "This is the vector magnitude: " << vecmag << endl;

        PointType ycoor1;
        PointType ycoor2;
        cout << "What is the intended vector: ";
        cin >> ycoor1.y1 >> ycoor2.y2;

        farcoilforce *= ycoor2.y2 / vecmag;
        closecoilforce *= ycoor1.y1 / vecmag;

        farcoilmag = abs(farcoilforce) * 100;
        closecoilmag = abs(closecoilforce) * 100;

        //Used to check the magnitude for MIDTERM purposes
        //cout << "Intensity for furthest coil: " << setprecision(2) << farcoilmag << "%" << endl;

        if(closecoilmag == NAN){
            cout << "The vector cannot be created" << endl;
        } else{
            cout << "Intensity for furthest coil: " << "100%" << endl;
            cout << "Intensity for closest coil: " << setprecision(2) << closecoilmag << "%" << endl;
        }

        return farcoilmag, closecoilmag;
    }



#endif /* VECCON_H */
