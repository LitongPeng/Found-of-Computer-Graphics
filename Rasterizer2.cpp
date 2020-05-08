//
//  Rasterizer.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Modifications by Warren R. Carithers.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Litong Peng
//

#include <cmath>


#include <list>
#include <algorithm>
#include <iostream>

#include "Rasterizer.h"
#include "Canvas.h"

using namespace std;

///
// Simple class that performs rasterization algorithms
///

///
// Constructor
//
// @param n number of scanlines
// @param C The Canvas to use
///
Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}

///
// Draw a filled polygon.
//
// Implementation should use the scan-line polygon fill algorithm
// discussed in class.
//
// The polygon has n distinct vertices.  The coordinates of the vertices
// making up the polygon are stored in the x and y arrays.  The ith
// vertex will have coordinate (x[i],y[i]).
//
// You are to add the implementation here using only calls to the
// setPixel() function.
//
// @param n - number of vertices
// @param x - array of x coordinates
// @param y - array of y coordinates
///

class edge
{
public:
    int yMin;
    int yMax;
    double x;
    double inverseSlope;
};
//create an edge table to store each bucket
vector<edge> table(int n,const int x[],const int y[])
{
    vector<edge> edgeTable;
    edge bucket;
    //loop through every edges
    for (int j=0;j<n;j++)
    {
        //if the first one is less than the second one
        if (y[j%n]<y[(j+1)%n])
        {
            bucket.yMin=y[j%n];
            bucket.yMax=y[(j+1)%n];
            bucket.x=x[j%n];
            //if the first one is bigger than or equal to the second one
        }else{
            bucket.yMin=y[(j+1)%n];
            bucket.yMax=y[j%n];
            bucket.x=x[(j+1)%n];
        }
        // if they are not equal, then add their bucket to the edge table edgeTable
        if (bucket.yMax-bucket.yMin!=0)
        {
            bucket.inverseSlope=(double)(x[j%n]-x[(j+1)%n])/(double)(y[j%n]-y[(j+1)%n]);
            edgeTable.push_back(bucket);
        }
    }
    return edgeTable;
}

//sort by y
struct sortY
{
    bool operator()(const edge structA,const edge structB)
    {
        return (structA.yMin<structB.yMin);
    }
};
//sort by x
struct sortX
{
    bool operator()(const edge structA,const edge structB)
    {
        return (structA.x<structB.x);
    }
};

double floorOperator(double m)
{
    return floor(m+0.5);
}

void Rasterizer::drawPolygon(int n, const int x[], const int y[] )
{
    // YOUR IMPLEMENTATION HERE
    //create an dege table
    std::vector<edge> edgeTable=table(n,x,y);
    edge bucket;
    //sort the edge table by y
    sort(edgeTable.begin(),edgeTable.end(),sortY());

    bool inside;
    vector<edge> activeEdgeTable;
    //the end of scan line
    int end=edgeTable[edgeTable.size()-1].yMax;

    for (int scanLine=edgeTable[0].yMin; scanLine<=end;scanLine++)
    {
        //initiliaze the inside
        inside=false;
        int j=0;
        while (j<edgeTable.size())
        {
            bucket=edgeTable[j];
            //if the current scan line is of the y min
            if (bucket.yMin==scanLine)
            {
                activeEdgeTable.push_back(bucket);
                edgeTable.erase(edgeTable.begin()+j);
            }else{
                j++;
            }
        }
        if (scanLine<end)
        {
            j=0;
            while (j<activeEdgeTable.size())
            {
                bucket=activeEdgeTable[j];
                //if the current scan line is of the y max
                if (bucket.yMax==scanLine)
                {
                    //remove the current scan line from the active edge table
                    activeEdgeTable.erase(activeEdgeTable.begin()+j);
                }else{
                    j++;
                }
            }
        }
        //sort the active edge table by x
        sort(activeEdgeTable.begin(),activeEdgeTable.end(),sortX());

        int Index=0;
        int endX=*max_element(x,x+n);
        for (int currentX=0; currentX<=endX&&Index<activeEdgeTable.size();currentX++)
        {
            if (currentX==floorOperator(activeEdgeTable[Index].x))
            {
                if (Index+1<activeEdgeTable.size()&&currentX!=floorOperator(activeEdgeTable[Index+1].x))
                {
                    //whether the line is inside or outside
                    inside=!inside;
                }
                while (Index<activeEdgeTable.size()&&currentX==floorOperator(activeEdgeTable[Index].x))
                {
                    //update the x value
                    activeEdgeTable[Index].x+=activeEdgeTable[Index].inverseSlope;
                    //set the pixel
                    C.setPixel(currentX,scanLine);
                    Index++;
                }
            }
            //if the picel is in side
            if (inside)
            {
                //set the pixel
                C.setPixel(currentX,scanLine);
            }
        }
    }
}
