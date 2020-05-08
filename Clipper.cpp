//
//  Clipper.cpp
//
//  Created by Warren R. Carithers on 01/15/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Litong Peng
//

#include "Vertex.h"
#include "Clipper.h"




	
///
// Simple module that performs clipping
///

///
// Constructor
///
Clipper::Clipper() {
}

///
// clipPolygon
//
// Clip the polygon with vertex count in and vertices inV against the
// rectangular clipping region specified by lower-left corner ll and
// upper-right corner ur. The resulting vertices are placed in outV.
//
// The routine should return the with the vertex count of polygon
// resulting from the clipping.
//
// @param in    the number of vertices in the polygon to be clipped
// @param inV   the incoming vertex list
// @param outV  the outgoing vertex list
// @param ll    the lower-left corner of the clipping rectangle
// @param ur    the upper-right corner of the clipping rectangle
//
// @return number of vertices in the polygon resulting after clipping
//
///






//check if the point is inside the boundary
bool Clipper::inside(Vertex v, Vertex boundary, int side){
	switch(side){
		case 1 : if(v.x > boundary.x){return false;}else{return true;} //right
		case 2 : if(v.y > boundary.y){return false;}else{return true;} //top
		case 3 : if(v.x < boundary.x){return false;}else{return true;} //left
		case 4 : if(v.y < boundary.y){return false;}else{return true;} //bottom
	}
}

//deal with the intersection point
Vertex Clipper::intersect(Vertex previous, Vertex current, Vertex b1, int side){
	Vertex intersection = {0,0};
	float m = (float)(previous.y-current.y)/(previous.x-current.x);
	bool vertical = true;
	//if the boundary is horizontal
	if(side==2||side==4){
		vertical = false;
	}
	if(vertical){
		intersection.x = b1.x;
		int dX = intersection.x-current.x;
		int intersectionY = current.y + (m*dX);
		intersection.y=intersectionY;
	}else{
		intersection.y=b1.y;
		int dY = intersection.y-current.y;
		int intersectionX = current.x + (dY/m);
		intersection.x=intersectionX;
	}
	//retunr the vertex of interseced point
	return intersection;
}

// @param in       the number of inputs
// @param inV[]    input vertexs
// @param outV[]   output vertexs
// @param boundary boundaries
// @param side     the side being worked on
int Clipper::SHPC(Vertex inV[], Vertex outV[], int in, Vertex boundary, int side){
	int out=0;
	//last vertex is the initial in this turn
	Vertex previous = inV[in-1];
	//the current vertex
	Vertex current = {0,0};
	//loop through all input vertexs
	for(int j=0;j<in;j++){
		current = inV[j];
        //check if the current vertex is inside
		if(inside(current, boundary, side)){
			//if the previous vertex is also inside,
			if(inside(previous, boundary, side)){
				//add the current vertex to the output
				outV[out]=current;
				//add the count of output number
				out++;
				//else intersect
			}else{
				//add the current vertex and intersect to output
				//and add the count of output number also
				outV[out] = intersect(previous, current, boundary, side);
				out++;
				outV[out] = current;
				out++;
			}
			//if the current vertex is not inside
		}else{
			//if the previous vertex is inside
			if(inside(previous, boundary, side)){
				//we add the intersect to output
				outV[out] = intersect(previous, current, boundary, side);
				//and add the count of output number also
				out++;
			}
		}
		//set the previous vertex to current vertex
		previous = current;
	}
	//retunrn the number of output
	return out;
}

///
// clipPolygon
//
// Clip the polygon with vertex count in and vertices inV against the
// rectangular clipping region specified by lower-left corner ll and
// upper-right corner ur. The resulting vertices are placed in outV.
//
// The routine should return the with the vertex count of polygon
// resulting from the clipping.
//
// @param in    the number of vertices in the polygon to be clipped
// @param inV   the incoming vertex list
// @param outV  the outgoing vertex list
// @param ll    the lower-left corner of the clipping rectangle
// @param ur    the upper-right corner of the clipping rectangle
//
// @return number of vertices in the polygon resulting after clipping
//
///

int Clipper::clipPolygon( int in, const Vertex inV[], Vertex outV[],
                          Vertex ll, Vertex ur )
{
    // YOUR CODE GOES HERE
    //initialize
	int count = 0;
	//set two vertexs of lower-left corner and upper-right corner
	Vertex ul = {ll.x, ur.y};
	Vertex lr = {ur.x, ll.y};
	Vertex myInit[50];
	for(int i=0;i<in;i++){
		myInit[i] = inV[i];
	}
	Vertex second[50];
	Vertex third[50];
	Vertex forth[50];
	int in2, in3, in4;
	//clip on each four edges
	in2 = SHPC(myInit, second, in, ur,1);
	in3 = SHPC(second, third, in2, ur,2);
	in4 = SHPC(third, forth, in3, ll,3);
	count = SHPC(forth, outV, in4, ll,4);

    return( count );  // remember to return the outgoing vertex count!

}