//Vector Reconstruction Program

#ifndef VECCON_H
#define VECCON_H

/* Last edit logs:

    -Willia 02/11/19: Added base pseudocode from diagram
    -Willia 02/14/19: Added datatypes and code to last function
    -Willia 02/28/19: Implemented Convex Hull algorithm to find distances



*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <thread>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;
#define PI 3.14159265

// Point in the xy-plane
struct PointType
{
    double x;
    double y;
};

double theta[100];
double phi[100];
// double theta;
// double phi;
int radius = 17;
double coilAddress[300];

//Pick mapping based on position theta
//Theta and phi for the mapping
//Look at the onenote for the equations
double pickMapping()
{

    int num = 0;
    double angle, result, x, y;
    double mapping[2];
    double mapping2[2] = {x, y};
    double mapping1[2] = {x, y};

    string line;
    ifstream datafile("data.txt");

    if (datafile.is_open())
    {
        while (getline(datafile, line))
        {
            datafile >> theta[num] >> phi[num];
            if (theta[num] > PI / 4)
            {
                x = sqrt(pow(radius, 2) - pow(cos(theta[num]), 2) * pow(radius, 2)) * cos(phi[num]);
                y = sqrt(pow(radius, 2) - pow(cos(theta[num]), 2) * pow(radius, 2)) * sin(phi[num]);
                cout << "X and Y: " << endl
                     << x << endl
                     << y << endl;
                if (x < 0)
                {
                    result = (x * y) * -1;
                    result = atan2(y, x) + 180;
                    angle = result;
                }
                else
                {
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
                cout << "X and Y: " << endl
                     << x << endl
                     << y << endl;
                if (x < 0)
                {
                    result = (x * y) * -1;
                    result = atan2(y, x) + 180;
                    angle = result;
                }
                else
                {
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

    else
        cout << "Unable to open file";

    return angle, x, y, mapping[2];
}

//1ST FUNCTION
//Find distance of every nearby coil within radial distance
//Loop through addresses and add to a data structure
//Determine coils that are within 1 to 3.5cm

//Store all coils within that distance in a data structure
//Check if it is a deadzone
//If it is a deadzone, stall the program for () secs. Do not power on any coils

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
        // myfile >> n_points;
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
          //  cout << "(" << points[i].x << " , " << points[i].y << ")" << endl;

        //Computing upper convex hull
        upperCH.push_back(points[0]);
        upperCH.push_back(points[1]);

        for (int i = 2; i < points.size(); i++)
        {
            while (upperCH.size() > 1 and (!right_turn(upperCH[upperCH.size() - 2], upperCH[upperCH.size() - 1], points[i])))
                upperCH.pop_back();
            upperCH.push_back(points[i]);
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

#endif /* VECCON_H */
