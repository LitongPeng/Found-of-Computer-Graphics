//
//  Rasterizer.cpp
//
//  Created by Warren R. Carithers on 01/28/14.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor: Litong Peng
//

#include <cmath>

#include "Rasterizer.h"

#include "Canvas.h"

///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n number of scanlines
// @param C the Canvas to be used
///

Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}


///
// Draw my initials
//
// Draw my own initials using calls to drawLine(), in the same
// manner that makeLines() in the driver program draws 'CG'.
///

void Rasterizer::myInitials( void ) {

    // ######## Use light blue (0.678,0.847,0.902) for initials ######## 

    C.setColor( 0.678, 0.847, 0.902 );

    //draw letter "P"

    drawLine(75,37,112,37);
    drawLine(112,37,112,112);
    drawLine(112,112,225,112);
    drawLine(225,112,262,149);
    drawLine(262,149,262,187);
    drawLine(262,187,225,225);
    drawLine(225,225,75,225);
    drawLine(75,225,75,37);
    drawLine(112,150,187,150);
    drawLine(187,150,215,168);
    drawLine(215,168,187,187);
    drawLine(187,187,112,187);
    drawLine(112,187,112,150);

     //draw letter "L"

    drawLine(375,37,525,37);
    drawLine(525,37,525,75);
    drawLine(525,75,412,75);
    drawLine(412,75,412,225);
    drawLine(412,225,375,225);
    drawLine(375,225,375,37);



    //
    // add code here to draw your initials
    // with calls to your drawLine() function
    // 

}

///
// Draw a line from (x0,y0) to (x1, y1)
//
// Implementation should be using the Midpoint Line Algorithm.
//
// You are to add the implementation here using only calls to the
// setPixel() method of the Canvas.
//
// @param x0 x coord of first endpoint
// @param y0 y coord of first endpoint
// @param x1 x coord of second endpoint
// @param y1 y coord of second endpoint
///

void Rasterizer::drawLine( int x0, int y0, int x1, int y1 )
{
    //
    // add code here to implement drawLine()
    // using the midpoint line algorithm
    //
float vertical;
    float dx = (float) (x1 - x0),
		  dy = (float) (y1 - y0);
	float m = (dx != 0) ? dy / dx : vertical, 
		  origin = y0 - m * x0;


      //to decide the slope direction 
	int d_X = dx > 0 ? 1 : -1,
		d_Y = dy > 0 ? 1 : -1,
		Yy = d_Y > 0 ? 0 : -1; 

//initialize the pixel and the real x,y
	int x_pixel = x0, y_pixel = y0; 
	float x, y; 

//the vertical line situation
	if (m == vertical) {
		for (y_pixel = y0; y_pixel != y1; y_pixel += d_Y) {
			C.setPixel(x_pixel, y_pixel + Yy);
		}

//gentle slope
	} else if (-1. <= m && m <= 1.) { 
		for (x_pixel = x0; x_pixel != x1; x_pixel += d_X) {
			y = m * x_pixel + origin; 

			if (d_Y * 2 * y > d_Y * (2 * y_pixel + 1)) { 
				y_pixel += d_Y;
			}

			C.setPixel(x_pixel, y_pixel);
		}
	}

//steep slope
	else { 
		for (y_pixel = y0; y_pixel != y1; y_pixel += d_Y) {
			x = (y_pixel - origin) / m; 

			if (d_X * 2 * x > d_X * (2 * x_pixel + d_X)) { 
				x_pixel += d_X;
			}

			C.setPixel(x_pixel, y_pixel + Yy);
		}
	}
}
