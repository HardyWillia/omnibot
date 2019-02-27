//Coil Intensity Program
#ifndef COILINTENSE_H 
#define COILINTENSE_H

/* Last edit logs:

    -Willia 02/11/19: Added base pseudocode from diagram
    -Willia 02/26/2019: Added function for computing magnitude



*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <thread>
#include <fstream>
#include <algorithm>

using namespace std;
#define PI 3.14159265

    double intendvec;

    //1ST FUNCTION ?? need clarification
    //Receive the angle of the coil furthest (theta) and the coil closest (phi) from the intended vector (output from control algorithm) 
    //***May need to put this in main

    //2ND FUNCTION
    //Intensify the furthest coil to 100%
    //Calculate the force of the closest coil
    //Calculate the current vector magnitude
    //Multiply the magnitudes of force at both coils
        //Get the magnitudes for each coil
    //Output the magnitudes (determines coil intensity for switching)

    double magOutput(double theta, double phi){

        double farcoil;
        double farcoilforce;
        double closecoilforce;
        double vecmag;
        double farcoilmag;
        double closecoilmag;
        int intensity;

        farcoil = sin(theta) * 30;
        closecoilforce = (sin(abs(theta) * 30))/(sin(abs(phi)));

        /*
            Max current 30A
            Max voltage 10.4V 
            Max wattage 304W

            **Will need at minimum 25% (76W) of intensity to power on a coil
            100% = 304W
            50% = 152W
        */
        vecmag = cos(abs(theta)) * max(farcoilforce, 100.0) + cos(abs(phi)) * (closecoilforce);


        cout << "What is the intended vector: " << endl;
        cin >> intendvec;

        farcoilforce *= intendvec / vecmag;
        closecoilforce *= intendvec / vecmag;

        farcoilmag = farcoilforce;
        closecoilmag = closecoilforce;

        //Used to check the magnitude for MIDTERM purposes
        cout << farcoilmag << endl;
        cout << closecoilmag << endl;

        return farcoilmag, closecoilmag;
    }


#endif /* VECCON_H */