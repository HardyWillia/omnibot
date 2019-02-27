//Vector Reconstruction Program

#ifndef VECCON_H 
#define VECCON_H

/* Last edit logs:

    -Willia 02/11/19: Added base pseudocode from diagram
    -Willia 02/14/19: Added datatypes and code to last function



*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <thread>
#include <fstream>

using namespace std;
#define PI 3.14159265


    double x;
    double y;
    double theta[100];
    double phi[100];
   // double theta;
   // double phi;
    int radius = 17;
    double coilAddress[300];

    //Pick mapping based on position theta 
        //Theta and phi for the mapping
        //Look at the onenote for the equations
    double pickMapping(){

            int num = 0;
	    double angle, result;
            double mapping[2];
            double mapping2[2] = {x, y};
            double mapping1[2] = {x, y};

            string line;
                ifstream datafile ("data.txt");

                if (datafile.is_open())
                {
                    while ( getline (datafile,line))		
                    {
			datafile >> theta[num] >> phi[num];
                        if (theta[num] > PI/4){
                            x = sqrt(pow(radius, 2) - pow(cos(theta[num]), 2) * pow(radius, 2)) * cos(phi[num]);
                            y = sqrt(pow(radius, 2) - pow(cos(theta[num]), 2) * pow(radius, 2)) * sin(phi[num]);
			    cout << "X and Y: " << endl << x << endl << y << endl;
                                if(x < 0){
                                        result = (x * y) * -1;
                                        result = atan2(y, x) + 180;
                                        angle = result;
                                 }
                                else{
                                        result = atan2(y, x);
                                        angle = result;
                                }

			    mapping[2] = mapping2[2];
			    cout << "Mapping 2 has been chosen" << endl;
                            cout << "The angle is: " << angle << endl;
			    ++num;
                        }
                        else
                        {
                            x = theta[num];
                            y = phi[num];
                            cout << "X and Y: " << endl << x << endl << y << endl;
                                if(x < 0){
                                        result = (x * y) * -1;
                                        result = atan2(y, x) + 180;
                                        angle = result;
                                 }
                                else{
                                        result = atan2(y, x);
                                        angle = result;
                                }
                            
			    mapping[2] = mapping1[2];
			    cout << "Mapping 1 has been chosen" << endl;
                            cout << "The angle is: " << angle << endl;
			    ++num;
                        }

                    }
                    datafile.close();
                
                }

                else cout << "Unable to open file"; 

            
            return angle, x, y, mapping[2];
        }


    //1ST FUNCTION
    //Find distance of every nearby coil within radial distance
        //Loop through addresses and add to a data structure
        //Determine coils that are within 1 to 3.5cm

    
    //Store all coils within that distance in a data structure
        //Check if it is a deadzone
        //If it is a deadzone, stall the program for () secs. Do not power on any coils

    double findDistance(){

        // for(int i = 0; i < coilAddress[]; i++){

        // }

    }
    



    //2ND FUNCTION    
    //Determine angle
        //Check if x < 0
            //If true, multiply x and y by -1
            //Compute arctan(y/x) and add 180 to the result
            //Return the angle
        //Otherwise
            //Computer arctan(y/x)
            //Return the angle
 /*   double returnAngle(){
        double angle, result;

        if(x < 0){
               result = (x * y) * -1;
               result = atan(y/x) + 180;
               angle = result;
            }
        else{
            result = atan(y/x);
            angle = result;
        }
        return angle;
    }
*/

    //Output the result


#endif /* VECCON_H */
