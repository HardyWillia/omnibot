//Coil Intensity Test Program
#ifndef COILINTENSETEST_H
#define COILINTENSETEST_H

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
    int x;
    int y;

};

// A utility function to return square of distance between p1 and p2
int dist(PointType p1, PointType p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

using pairs = std::pair<PointType, PointType>;

unsigned square_distance(const PointType &lhs, const PointType &rhs)
{
    unsigned adj = std::abs(lhs.x - rhs.x);
    unsigned opp = std::abs(lhs.y - rhs.y);
    return adj * adj + opp * opp;
}

using Iterator = std::vector<PointType>::iterator;
unsigned minimal_distance_naive(Iterator first, Iterator last)
{
    pairs closest{*first, *std::next(first)};
    for (Iterator out = first; out != last; ++out)
    {
        pairs temp;
        temp.first = *out;
        for (Iterator in = std::next(out); in != last; ++in)
        {
            temp.second = *in;
            closest = std::min(closest, temp, [](const auto &lhs, const auto &rhs) {
                return square_distance(lhs.first, lhs.second) < square_distance(rhs.first, rhs.second);
            });
        }
    }
    return square_distance(closest.first, closest.second);
}

bool is_inside_rectangle(const PointType &input, const PointType &up_left, const PointType &bottom_right)
{
    return up_left.x <= input.x && input.x <= bottom_right.x && up_left.y >= input.y && input.y >= bottom_right.y;
}

pairs candidates_rectangle(const PointType &p, unsigned square_dist)
{
    double dist = std::sqrt(square_dist);
    pairs res{{p.x, static_cast<int>(p.y + dist)},
             {static_cast<int>(p.x + dist), static_cast<int>(p.y - dist)}};
    return res;
}

unsigned minimal_distance_rec(Iterator first, Iterator last, const std::size_t threshold = 3)
{
    // assume points are sorted by x
    if (std::distance(first, last) <= threshold)
        return minimal_distance_naive(first, last);
    auto pivot = std::next(first, std::distance(first, last) / 2);
    auto min_left = minimal_distance_rec(first, pivot);
    auto min_right = minimal_distance_rec(pivot, last);

    auto temp_min = std::min(min_left, min_right);
    // define the band inside which disctance can be less than temp_min
    auto not_too_left = std::partition(first, pivot, [&](const auto &p) {
        return p.x < (pivot->x - static_cast<int>(std::sqrt(temp_min)));
    });
    auto not_too_right = std::partition(pivot, last, [&](const auto &p) {
        return p.x <= (pivot->x + static_cast<int>(std::sqrt(temp_min)));
    });

    // and look for the closest pair inside
std::for_each(not_too_left, pivot, [&](const auto &lp) {
        auto [up_left, bottom_right] = candidates_rectangle(lp, std::sqrt(temp_min));
        auto outside = std::partition(pivot, not_too_right, [=](const auto &rp) {
            return !is_inside_rectangle(rp, up_left, bottom_right);
        });
        auto middle_closest = std::min_element(pivot, outside, [=](const auto &lhs, const auto &rhs) {
            return square_distance(lp, lhs) < square_distance(lp, rhs);
        });
        temp_min = std::min(temp_min, square_distance(lp, *middle_closest));
    });
    return temp_min;
}

double minimal_distance(std::vector<PointType> &points)
{
    std::sort(points.begin(), points.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.x < rhs.x;
    });
    return std::sqrt(minimal_distance_rec(points.begin(), points.end()));
}

double magOutput()
{
    PointType theta;
    PointType phi;
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
    ifstream coordfile("coilcoordinates.txt");

    if (datafile.is_open())
    {
        while (getline(datafile, line))
        {
            datafile >> theta.x >> phi.y;
            if (theta.x > PI / 4)
            {
                x = sqrt(pow(radius, 2) - pow(cos(theta.x), 2) * pow(radius, 2)) * cos(phi.y);
                y = sqrt(pow(radius, 2) - pow(cos(theta.x), 2) * pow(radius, 2)) * sin(phi.y);

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
                for (std::size_t i = 0u; i < 29; i++)
                {
                    int a, b;
                    while (coordfile.is_open())
                        coordfile >> a >> b;
                    points.push_back({a, b});

                    farcoil = sin(theta.x) * 30;
                    closecoilforce = (sin(abs(theta.x) * 30)) / (sin(abs(phi.y)));

                    /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W
                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */
                    vecmag = cos(abs(theta.x)) * max(farcoilforce, 100.0) + cos(abs(phi.y)) * (closecoilforce);

                    int intendedmag;
                    cout << "What is the intended vector magnitude: ";
                    cin >> intendedmag;

                    farcoilforce *= intendedmag / vecmag;
                    closecoilforce *= angle / vecmag;

                    farcoilmag = abs(farcoilforce) * 100;
                    closecoilmag = abs(closecoilforce) * 100;

                    cout << "Intensify the furthest coil at: "
                         << "100%" << endl;
                    cout << "Intensify the closest coil " << minimal_distance(points) << " at: " << setprecision(2) << closecoilmag << " %" << endl;
                }

            }
            else
            {
                x = theta.x;
                y = phi.y;
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
                for (std::size_t i = 0u; i < 29; i++)
                {
                    int a, b;
                    while (coordfile.is_open())
                        coordfile >> a >> b;
                    points.push_back({a, b});

                    farcoil = sin(theta.x) * 30;
                    closecoilforce = (sin(abs(theta.x) * 30)) / (sin(abs(phi.y)));

                    /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W
                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */
                    vecmag = cos(abs(theta.x)) * max(farcoilforce, 100.0) + cos(abs(phi.y)) * (closecoilforce);

                    int intendedmag;
                    cout << "What is the intended vector magnitude: ";
                    cin >> intendedmag;

                    farcoilforce *= intendedmag / vecmag;
                    closecoilforce *= angle / vecmag;

                    farcoilmag = abs(farcoilforce) * 100;
                    closecoilmag = abs(closecoilforce) * 100;

                    cout << "Intensify the furthest coil at: "
                         << "100%" << endl;
                    cout << "Intensify the closest coil " << minimal_distance(points) << " at: " << setprecision(2) << closecoilmag << " %" << endl;
                }
            }
        }
        datafile.close();
    }
    else
        cout << "Unable to open file";
}
#endif /* COILINTENSE_H */