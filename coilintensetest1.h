//Coil Intensity Test Program
#ifndef COILINTENSETEST1_H
#define COILINTENSETEST1_H

/* Last edit logs:
    -Willia 02/11/19: Added base pseudocode from diagram
    -Willia 02/26/19: Added function for computing magnitude
    -Willia 03/04/19: Debugging the code to determine why the values are printing incorrectly
    -Willia 04/01/19: Added coilintensetest as a test program for further improvements
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
#include <iterator>
#include <stack>
#include <stdlib.h>
#include <iomanip>
#include <set>

using namespace std;
#define PI 3.14159265
#define px second
#define py first

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
    int x;
    int y;

};

typedef pair<long long, long long> pairll;
pairll pnts[29];
int compare(pairll a, pairll b)
{
    return a.px < b.px;
}


double magOutput(pairll pnts[], int n)
{
    double theta;
    double phi;
    double intendvec;
    double farcoil;
    double farcoilforce;
    double closecoilforce;
    double vecmag;
    double farcoilmag;
    double closecoilmag;
    int intensity[2];
    std::vector<PointType> points;

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
            datafile >> theta >> phi;
            if (theta > PI / 4)
            {
                x = sqrt(pow(radius, 2) - pow(cos(theta), 2) * pow(radius, 2)) * cos(phi);
                y = sqrt(pow(radius, 2) - pow(cos(theta), 2) * pow(radius, 2)) * sin(phi);

                mapping[2] = mapping2[2];
                cout << "Mapping 2 has been chosen." << endl;
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
                    cout << "The angle is: " << setprecision(3) << angle << endl;
                }
                else
                {
                    result = atan2(y, x) * 180 / PI;
                    angle = result;
                    cout << "The angle is: " << setprecision(3) << angle << endl;
                }

                ++num;

                //Sort through the coordinates to find the closest to a given point
                sort(pnts, pnts + n, compare);
                double best = INFINITY;
                set<pairll> box;
                box.insert(pnts[0]);
                int left = 0;
                for (int i = 1; i < n; ++i)
                {
                    while (left < i && pnts[i].px - pnts[left].px > best)
                        box.erase(pnts[left++]);
                    for (decltype(box.begin()) it = box.lower_bound(make_pair(pnts[i].py - best, pnts[i].px - best)); it != box.end() && pnts[i].py + best >= it->py; it++)
                        best = min(best, sqrt(pow(pnts[i].py - it->py, 2.0) + pow(pnts[i].px - it->px, 2.0)));
                    box.insert(pnts[i]);

                    farcoil = sin(theta) * 30;
                    closecoilforce = (sin(abs(theta) * 30)) / (sin(abs(phi)));

                    /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W
                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */
                    vecmag = cos(abs(theta)) * max(farcoil, 100.0) + cos(abs(phi)) * (closecoilforce);

                    int intendedmag;
                    cout << "What is the intended vector magnitude: ";
                    cin >> intendedmag;

                    //farcoilforce *= intendedmag / vecmag;
                    closecoilforce *= intendedmag / vecmag;

                    //farcoilmag = abs(farcoilforce) * 100;
                    closecoilmag = abs(closecoilforce) * 100;

                    cout << "Intensify the furthest coil at: "
                         << "100%" << endl;
                    cout << "Intensify the closest coil " << best << " at: " << setprecision(2) << closecoilmag << " %" << endl;
                }
            }
            else
            {
                x = theta;
                y = phi;
                mapping[2] = mapping1[2];
                cout << "Mapping 1 has been chosen" << endl;
                if (x < 0)
                {
                    x *= -1;
                    y *= -1;
                    // cout << "X and Y: " << endl << x << endl << y << endl;
                    result = atan2(y, x);
                    angle = result * 180 / PI;
                    if (angle < 0)
                    {
                        angle = angle + 180;
                    }
                    cout << "The angle is: " << setprecision(3) << angle << endl;
                }
                else
                {
                    result = atan2(y, x) * 180 / PI;
                    angle = result;
                    cout << "The angle is: " << setprecision(3) << angle << endl;
                }

                //Sort through the coordinates to find the closest to a given point
                sort(pnts, pnts + n, compare);
                double best = INFINITY;
                set<pairll> box;
                box.insert(pnts[0]);
                int left = 0;
                for (int i = 1; i < n; ++i)
                {
                    while (left < i && pnts[i].px - pnts[left].px > best)
                        box.erase(pnts[left++]);
                    for (decltype(box.begin()) it = box.lower_bound(make_pair(pnts[i].py - best, pnts[i].px - best)); it != box.end() && pnts[i].py + best >= it->py; it++)
                        best = min(best, sqrt(pow(pnts[i].py - it->py, 2.0) + pow(pnts[i].px - it->px, 2.0)));
                    box.insert(pnts[i]);

                    farcoil = sin(theta) * 30;
                    closecoilforce = (sin(abs(theta) * 30)) / (sin(abs(phi)));

                    /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W
                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */
                    vecmag = cos(abs(theta)) * max(farcoil, 100.0) + cos(abs(phi)) * (closecoilforce);

                    int intendedmag;
                    cout << "What is the intended vector magnitude: ";
                    cin >> intendedmag;

                    //farcoilforce *= intendedmag / vecmag;
                    closecoilforce *= intendedmag / vecmag;

                    //farcoilmag = abs(farcoilforce) * 100;
                    closecoilmag = abs(closecoilforce) * 100;

                    cout << "Intensify the furthest coil at: "
                         << "100%" << endl;
                    cout << "Intensify the closest coil " << best << " at: " << setprecision(2) << closecoilmag << " %" << endl;
                }
            }
        }
        datafile.close();
    }
    else
        cout << "Unable to open file";
}
#endif /* COILINTENSE_H */