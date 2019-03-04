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
#include "veccon.h"

#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;
#define PI 3.14159265


//1ST FUNCTION
//Find distance of every nearby coil within radial distance
//Loop through addresses and add to a data structure
//Determine coils that are within 1 to 3.5cm

//Store all coils within that distance in a data structure
//Check if it is a deadzone
//If it is a deadzone, stall the program for () secs. Do not power on any coils


// Point in the xy-plane
struct PointType
{
    double x;
    double y;
};

//Use convex hull algorithm to find x and y closest and furthest from the torso

// Sort criterion: points are sorted with respect to their x-coordinate.
//                 If two points have the same x-coordinate then we compare
//                 their y-coordinates
bool sortPoints(const PointType &lhs, const PointType &rhs)
{
    return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}

// Check if three points make a right turn using cross product
bool right_turn(const PointType &P1, const PointType &P2, const PointType &P3)
{
    return ((P3.x - P1.x) * (P2.y - P1.y) - (P3.y - P1.y) * (P2.x - P1.x)) > 0;
}

double findDistance()
{

    ifstream myfile;
    //PointType *points;
    vector<PointType> lowerCH;
    vector<PointType> upperCH;

    // reading data from file
    myfile.open("coilcoordinates.txt");

    if (myfile.is_open())
    {
        //myfile >> n_points;
        //points = new PointType[999];
        vector<PointType> points;
        string line;
        int row = 0;
        while (getline(myfile, line))
        {
            std::stringstream ss(line);
            std::string token;
            int col = 1;

            PointType point;
            while (std::getline(ss, token, ' '))
            {
                if (col == 1)
                {
                    point.x = stod(token);
                }
                else
                {
                    point.y = stod(token);
                }
                col++;
            }
            points.push_back(point);
            row++;
        }
        // for (int i = 0; i < n_points; i++)
        //     myfile >> points[i].x >> points[i].y;

        myfile.close();

        //Sorting points
        //sort(points, points + n_points, sortPoints);
        //cout << "Sorted Points\n";
        //for (int i = 0; i != n_points; ++i)
           // cout << "(" << points[i].x << " , " << points[i].y << ")" << endl;


        //Computing upper convex hull
        upperCH.push_back(points[0]);
        upperCH.push_back(points[1]);

        for (int i = 2; i < points.size(); i++)
        {
            while (upperCH.size() > 1 and (!right_turn(upperCH[upperCH.size() - 2], upperCH[upperCH.size() - 1], points[i])))
                upperCH.pop_back();
            upperCH.push_back(points[i]);
            cout << "Sorted points: " << sortPoints(points[i-2], points[i-1]) << endl; 
        }
        cout << "Furthest coil: " << endl;
        cout << "(" << upperCH[upperCH.size()-1].x << " , " << upperCH[upperCH.size()].y << ")" << endl;

        //Computing lower convex hull
        lowerCH.push_back(points[points.size() - 1]);
        lowerCH.push_back(points[points.size() - 2]);

        for (int i = 2; i < points.size(); i++)
        {
            while (lowerCH.size() > 1 and (!right_turn(lowerCH[lowerCH.size() - 2], lowerCH[lowerCH.size() - 1], points[points.size() - i - 1])))
                lowerCH.pop_back();
            lowerCH.push_back(points[points.size() - i - 1]);
        }
        cout << "Closest coil: " << endl;
        for (int i = 0; i < lowerCH.size(); i++)
            cout << "(" << lowerCH[i].x << " , " << lowerCH[i].y << ")" << endl;
    }
}

    double intendvec;


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


        cout << "What is the intended vector: ";
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
