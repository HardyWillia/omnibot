//Coil Intensity Program

/* Last edit logs:

    -Willia 02/11/19: Added base pseudocode from diagram



*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <thread>
#include <fstream>

using namespace std;
#define PI 3.14159265

class OmnibotCoilIntensity{

    //1ST FUNCTION
    //Receive the angle of the coil furthest (theta) and the coil closest (phi) from the intended vector (output from control algorithm)

    //2ND FUNCTION
    //Intensify the furthest coil to 100%
        //Compute the sin(|theta|)
        //Multiply by the magnitude output of that coil at a max current of 30Amps

    //3RD FUNCTION
    //Calculate the force of the closest coil
        //Use (sin(|theta|) * (max forceof furthest coil))/(sin(|phi|))

    //4TH FUNCTION
    //Calculate the current vector magnitude
        //Use cos(|theta|) * max(force of furthest coil) + cos(|phi|) * (force of closest coil)

    //5TH FUNCTION
    //Multiply the magnitudes of force at both coils by (intended vector magnitude) / (current vector magnitude)
        //Get the magnitudes for each coil


    //Output the magnitudes (determines coil intensity for switching)


}