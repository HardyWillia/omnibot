//Coil Intensity Program

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

class OmnibotCoilIntensity{

    double x = 0;
    double y = 0;
    double theta[100];
    double phi[100];
    int radius = 17;
    double coilAddress[300];
    double intendvec;

    //1ST FUNCTION ?? need clarification
    //Receive the angle of the coil furthest (theta) and the coil closest (phi) from the intended vector (output from control algorithm)

    //2ND FUNCTION
    //Intensify the furthest coil to 100%
    //Calculate the force of the closest coil
    //Calculate the current vector magnitude
    //Multiply the magnitudes of force at both coils
        //Get the magnitudes for each coil
    //Output the magnitudes (determines coil intensity for switching)

    double magOutput(){

        double farcoil;
        double farcoilforce;
        double closecoilforce;
        double vecmag;
        double farcoilmag;
        double closecoilmag;
        int intensity;
        int num = 0;

        farcoil = sin(theta[num]) * 30;
        closecoilforce = (sin(abs(theta[num]) * 30))/(sin(abs(phi[num])));
        vecmag = cos(abs(theta[num])) * max(farcoilforce, 100.0) + cos(abs(phi[num])) * (closecoilforce);

        num++;

        cout << "What is the intended vector: " << endl;
        cin >> intendvec;

        farcoilforce *= intendvec / vecmag;
        closecoilforce *= intendvec / vecmag;

        farcoilmag = farcoilforce;
        closecoilmag = closecoilforce;

        //Used to check the magnitude for MIDTERM purposes
        cout << farcoilmag;
        cout << closecoilmag;

        return farcoilmag, closecoilmag;
    }

}