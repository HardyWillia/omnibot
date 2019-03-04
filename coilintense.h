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
#include <stack>
#include <stdlib.h>

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

    PointType p0;
 
    // A utility function to find next to top in a stack
    PointType nextToTop(stack<PointType> &S)
    {
        PointType p = S.top();
        S.pop();
        PointType res = S.top();
        S.push(p);
        return res;
    }
    
    // A utility function to swap two points
    int swap(PointType &p1, PointType &p2)
    {
        PointType temp = p1;
        p1 = p2;
        p2 = temp;
    }
    
    // A utility function to return square of distance between p1 and p2
    int dist(PointType p1, PointType p2)
    {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }
    
    int orientation(PointType p, PointType q, PointType r)
    {
        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    
        if (val == 0)
            return 0; // colinear
        return (val > 0) ? 1 : 2; // clock or counterclock wise
    }
    
    // A function used by library function qsort() to sort an array of
    // points with respect to the first point
    int compare(const void *vp1, const void *vp2)
    {
        PointType *p1 = (PointType *) vp1;
        PointType *p2 = (PointType *) vp2;
    
        // Find orientation
        double o = orientation(p0, *p1, *p2);
        if (o == 0)
            return (dist(p0, *p2) >= dist(p0, *p1)) ? -1 : 1;
    
        return (o == 2) ? -1 : 1;
    }
    
    // Prints convex hull of a set of n points.
    void convexHull(PointType points[], int n)
    {
        // Find the bottommost point
        int ymin = points[0].y, min = 0;
        for (int i = 1; i < n; i++)
        {
            int y = points[i].y;
    
            // Pick the bottom-most or chose the left most point in case of tie
            if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
                ymin = points[i].y, min = i;
        }
    
        // Place the bottom-most point at first position
        swap(points[0], points[min]);
    
        // Sort n-1 points with respect to the first point.  A point p1 comes
        // before p2 in sorted ouput if p2 has larger polar angle (in
        // counterclockwise direction) than p1
        p0 = points[0];
        qsort(&points[1], n - 1, sizeof(PointType), compare);
    
        // Create an empty stack and push first three points to it.
        stack<PointType> S;
        S.push(points[0]);
        S.push(points[1]);
        S.push(points[2]);
    
        // Process remaining n-3 points
        for (int i = 3; i < n; i++)
        {
            // Keep removing top while the angle formed by points next-to-top,
            // top, and points[i] makes a non-left turn
            while (orientation(nextToTop(S), S.top(), points[i]) != 2)
                S.pop();
            S.push(points[i]);
        }
    
        // Now stack has the output points, print contents of stack
        while (!S.empty())
        {
            PointType p = S.top();
            cout << "(" << p.x << ", " << p.y << ")" << endl;
            S.pop();
        }
    }

    double magOutput(PointType theta, PointType phi){
	
        double intendvec;
        double farcoil;
        double farcoilforce;
        double closecoilforce;
        double vecmag;
        double farcoilmag;
        double closecoilmag;
        int intensity;

        farcoil = sin(theta.x) * 30;
        closecoilforce = (sin(abs(theta.x) * 30))/(sin(abs(phi.y)));

                
                /*
                    Max current 30A
                    Max voltage 10.4V 
                    Max wattage 304W

                    **Will need at minimum 25% (76W) of intensity to power on a coil
                    100% = 304W
                    50% = 152W
                */
        vecmag = cos(abs(theta.x)) * farcoilforce + cos(abs(phi.y)) * (closecoilforce);

        cout << "This is the vector magnitude: " << vecmag << endl;


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
