//Coil Intensity Test Program
#ifndef COILINTENSE_H
#define COILINTENSE_H

/* Last edit logs:
    -Willia 02/11/19: Added base pseudocode from diagram
    -Willia 02/26/19: Added function for computing magnitude
    -Willia 03/04/19: Debugging the code to determine why the values are printing incorrectly
    -Willia 04/01/19: Added coilintensetest as a test program for further improvements
    -Willia 04/03/19: Finished initial coil identification, there is a bug in the array

*/

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <stdlib.h>
#include <iomanip>
#include <set>

using namespace std;
#define PI 3.14159265
#define px second
#define py first

//Intensify the furthest coil to 100%
//Calculate the force of the closest coil
//Calculate the current vector magnitude
//Multiply the magnitudes of force at both coils
//Get the magnitudes for each coil
//Output the magnitudes (determines coil intensity for switching)

// Points in the cartesian plane
typedef pair<long long, long long> pairll;
//vector<std::pair<long long, long long>> pnts[40];
pairll pnts[40];
int radius = 17;
int compare(pairll a, pairll b)
{
    return a.px < b.px;
}

double magOutput(int n)
{
    double theta[100];
    double phi[100];
    double intendvec;
    double farcoil;
    double farcoilforce;
    double closecoilforce;
    double vecmag;
    double farcoilmag;
    double closecoilmag;
    int intensity[2];

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

                mapping[2] = mapping2[2];
                cout << endl
                     << "Mapping 2 has been chosen." << endl;
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
                // sort(pnts, pnts + n, compare);
                int currentposx;
                int currentposy;
                // double best = INFINITY;
                // set<pairll> box;
                // box.insert(pnts[0]);
                // int left = 0;
                for (int i = 1; i < n; ++i)
                {
                    // while (left < i && pnts[i].px - pnts[left].px > best)
                    //     box.erase(pnts[left++]);
                    // for (decltype(box.begin()) it = box.lower_bound(make_pair(pnts[i].py - best, pnts[i].px - best)); it != box.end() && pnts[i].py + best >= it->py; it++)
                    //     best = min(best, sqrt(pow(pnts[i].py - it->py, 2.0) + pow(pnts[i].px - it->px, 2.0)));
                    // box.insert(pnts[i]);

                    cout << "What is your current position: ";
                    cin >> currentposx >> currentposy;

                    currentposx += 1;

                    farcoil = sin(theta[num]) * 30;
                    closecoilforce = (sin(abs(theta[num]) * 30)) / (sin(abs(phi[num])));

                    /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W
                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */
                    vecmag = cos(abs(theta[num])) * max(farcoil, 100.0) + cos(abs(phi[num])) * (closecoilforce);

                    int intendedmag;
                    cout << "What is the intended vector magnitude: ";
                    cin >> intendedmag;

                    closecoilforce *= intendedmag / vecmag;
                    closecoilmag = abs(closecoilforce) * 100;

                    if (closecoilmag != closecoilmag || closecoilmag > 100.0)
                    {
                        cout << "The vector cannot be re-created" << endl;
                    }
                    else if (closecoilmag == 0.0)
                    {
                        cout << "Only intensify the furthest coil to 100%" << endl;
                    }
                    else
                    {

                        cout << "Intensify the furthest coil to: "
                             << "100%" << endl;
                        cout << "Intensify the closest coil at position " << "(" << currentposx << ", "<< currentposy << ")" << " to: " << setprecision(2) << closecoilmag << " %" << endl;
                    }
                }
            }
            else
            {
                x = theta[num];
                y = phi[num];
                mapping[2] = mapping1[2];
                cout << endl
                     << "Mapping 1 has been chosen" << endl;
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

                //Sort through the coordinates to find the closest to a given point
                // sort(pnts, pnts + n, compare);
                int currentposx;
                int currentposy;
                // double best = INFINITY;
                // set<pairll> box;
                // box.insert(pnts[0]);
                // int left = 0;
                for (int i = 1; i < n; ++i)
                {
                    // while (left < i && pnts[i].px - pnts[left].px > best)
                    //     box.erase(pnts[left++]);
                    // for (decltype(box.begin()) it = box.lower_bound(make_pair(pnts[i].py - best, pnts[i].px - best)); it != box.end() && pnts[i].py + best >= it->py; it++)
                    //     best = min(best, sqrt(pow(pnts[i].py - it->py, 2.0) + pow(pnts[i].px - it->px, 2.0)));
                    // box.insert(pnts[i]);

                    cout << "What is your current position: ";
                    cin >> currentposx >> currentposy;

                    currentposx += 1;

                    farcoil = sin(theta[num]) * 30;
                    closecoilforce = (sin(abs(theta[num]) * 30)) / (sin(abs(phi[num])));

                    /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W
                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */
                    vecmag = cos(abs(theta[num])) * max(farcoil, 100.0) + cos(abs(phi[num])) * (closecoilforce);

                    int intendedmag;
                    cout << "What is the intended vector magnitude: ";
                    cin >> intendedmag;

                    closecoilforce *= intendedmag / vecmag;
                    closecoilmag = abs(closecoilforce) * 100;

                    if (closecoilmag != closecoilmag || closecoilmag > 100.0)
                    {
                        cout << "The vector cannot be re-created" << endl;
                    }
                    else if (closecoilmag == 0.0)
                    {
                        cout << "Only intensify the furthest coil to 100%" << endl;
                    }
                    else
                    {

                        cout << "Intensify the furthest coil to: "
                             << "100%" << endl;
                        cout << "Intensify the closest coil at position "
                             << "(" << currentposx << ", " << currentposy << ")"
                             << " to: " << setprecision(2) << closecoilmag << " %" << endl;
                    }
                }
            }
        }
        datafile.close();
    }
    else
        cout << "Unable to open file";
}
#endif /* COILINTENSE_H */
