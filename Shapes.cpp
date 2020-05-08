//
//  Shapes
//
//  Routines for tessellating a number of basic shapes
//
//  Students are to supply their implementations for the functions in
//  this file using the function addTriangle() to do the tessellation.
//
//  This code can be compiled as either C or C++.
//
//Arthor:Litong Peng

#include <cmath>

// Canvas.h pulls in all the OpenGL/GLFW/etc. header files for us
#include "Shapes.h"
#include "Canvas.h"
#include "Vertex.h"


#include <iostream>

#define Pi 3.1415926535


///
// makeCube - Create a unit cube, centered at the origin, with a given number
// of subdivisions in each direction on each face.
//
// @param subdivision - number of equal subdivisions to be made in each 
//        direction along each face
//
// Can only use calls to C.addTriangle()
///
void makeCube( Canvas &C, int subdivisions )
{
    if( subdivisions < 1 )
        subdivisions = 1;

    // YOUR IMPLEMENTATION HERE

    //initialize the cube
    float Incre[subdivisions+1];
    Vertex Increcre[subdivisions+1][subdivisions+1];
    float vertex1=0,vertex2=0;

    //the face where z=0.5
    //create vertices
    for(int i=0;i<=subdivisions;i++){
		vertex1=((float)i)/subdivisions;
		//calculate x
		Incre[i]=((1-vertex1)*-.5)+vertex1*.5;
		//calculate y
		for(int j=0;j<=subdivisions;j++){
			vertex2=((float)j)/subdivisions;
			Increcre[i][j].z=0.5; //z is 0.5
			Increcre[i][j].y=Incre[i];
			Increcre[i][j].x=((1-vertex2)*-.5)+vertex2*.5;
		}
	}
	//build triangles for this face
	for(int i=0;i<subdivisions;i++){
		for(int j=0;j<subdivisions;j++){
			C.addTriangle(Increcre[i][j], Increcre[i][j+1], Increcre[i+1][j+1]);//upper triangle
			C.addTriangle(Increcre[i+1][j+1], Increcre[i+1][j], Increcre[i][j]);//lower triangle
		}
	}
	
	//the face where z=-0.5
	//create vertices
    for(int i=0;i<=subdivisions;i++){
		vertex1=((float)i)/subdivisions;
		//calculate x
		Incre[i]=((1-vertex1)*.5)+vertex1*-.5;
		//calculate y
		for(int j=0;j<=subdivisions;j++){
			vertex2=((float)j)/subdivisions;
			Increcre[i][j].z=-0.5; //z is -0.5
			Increcre[i][j].y=Incre[i];
			Increcre[i][j].x=((1-vertex2)*-.5)+vertex2*.5;
		}
	}
	//add triangles for this face
	for(int i=0;i<subdivisions;i++){
		for(int j=0;j<subdivisions;j++){
			C.addTriangle(Increcre[i][j], Increcre[i][j+1], Increcre[i+1][j+1]);//upper triangle
			C.addTriangle(Increcre[i+1][j+1], Increcre[i+1][j], Increcre[i][j]);//lower triangle
		}
	}
	
	//the face where x=0.5
	//create vertices
    for(int i=0;i<=subdivisions;i++){
		vertex1=((float)i)/subdivisions;
		//calculate y
		Incre[i]=((1-vertex1)*-.5)+vertex1*.5;
		//calculate z
		for(int j=0;j<=subdivisions;j++){
			vertex2=((float)j)/subdivisions;
			Increcre[i][j].x=0.5; //x is 0.5
			Increcre[i][j].z=Incre[i];
			Increcre[i][j].y=((1-vertex2)*-.5)+vertex2*.5;
		}
	}
	//add triangles for this face
	for(int i=0;i<subdivisions;i++){
		for(int j=0;j<subdivisions;j++){
			C.addTriangle(Increcre[i][j], Increcre[i][j+1], Increcre[i+1][j+1]);//upper triangle
			C.addTriangle(Increcre[i+1][j+1], Increcre[i+1][j], Increcre[i][j]);//lower triangle
		}
	}
	
	//the face where x=-0.5
	//create vertices
    for(int i=0;i<=subdivisions;i++){
		vertex1=((float)i)/subdivisions;
		//calculate y
		Incre[i]=((1-vertex1)*.5)+vertex1*-.5;
		//calculate z
		for(int j=0;j<=subdivisions;j++){
			vertex2=((float)j)/subdivisions;
			Increcre[i][j].x=-0.5; //x is -0.5
			Increcre[i][j].z=Incre[i];
			Increcre[i][j].y=((1-vertex2)*-.5)+vertex2*.5;
		}
	}
	//add triangles for this face
	for(int i=0;i<subdivisions;i++){
		for(int j=0;j<subdivisions;j++){
			C.addTriangle(Increcre[i][j], Increcre[i][j+1], Increcre[i+1][j+1]);//upper triangle
			C.addTriangle(Increcre[i+1][j+1], Increcre[i+1][j], Increcre[i][j]);//lower triangle
		}
	}
	
	//the face where y=0.5
	//create vertices
    for(int i=0;i<=subdivisions;i++){
		vertex1=((float)i)/subdivisions;
		//calculate z
		Incre[(int)(vertex1*subdivisions)]=((1-vertex1)*-.5)+vertex1*.5;
		//calculate x
		for(int j=0;j<=subdivisions;j++){
			vertex2=((float)j)/subdivisions;
			Increcre[i][j].y=0.5; //y is 0.5
			Increcre[i][j].x=Incre[i];
			Increcre[i][j].z=((1-vertex2)*-.5)+vertex2*.5;
		}
	}
	//add triangles to this face
	for(int i=0;i<subdivisions;i++){
		for(int j=0;j<subdivisions;j++){
			C.addTriangle(Increcre[i][j], Increcre[i][j+1], Increcre[i+1][j]);//upper triangle
			C.addTriangle(Increcre[i][j+1], Increcre[i+1][j+1], Increcre[i+1][j]);//lower triangle
		}
	}
	
	//the face where y=-0.5
	//create vertices
    for(int i=0;i<=subdivisions;i++){
		vertex1=((float)i)/subdivisions;
		//calculate z
		Incre[(int)(vertex1*subdivisions)]=((1-vertex1)*.5)+vertex1*-.5;
		//calculate x
		for(int j=0;j<=subdivisions;j++){
			vertex2=((float)j)/subdivisions;
			Increcre[i][j].y=-0.5; //y is 0.5
			Increcre[i][j].x=Incre[i];
			Increcre[i][j].z=((1-vertex2)*-.5)+vertex2*.5;
		}
	}
	//add triangles to this face
	for(int i=0;i<subdivisions;i++){
		for(int j=0;j<subdivisions;j++){
			C.addTriangle(Increcre[i][j], Increcre[i][j+1], Increcre[i+1][j]);//upper triangle
			C.addTriangle(Increcre[i][j+1], Increcre[i+1][j+1], Increcre[i+1][j]);//lower triangle
		}
	}
}


///
// makeCylinder - Create polygons for a cylinder with unit height, centered at
// the origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cylinder
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCylinder( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE

    //initialize the cylinder
    float Z[radialDivisions], X[radialDivisions];
    double degree=0;
    Vertex top[radialDivisions+1], bottom[radialDivisions+1];
    //the center point of top circle
    top[radialDivisions].y=0.5;
    top[radialDivisions].x=0;
    top[radialDivisions].z=0;
    //the center point of bottom circle
    bottom[radialDivisions].y=-.5;
    bottom[radialDivisions].x=0;
    bottom[radialDivisions].z=0;
    //the circumference of circle
    for(int i=0;i<radialDivisions;i++){
		X[i]=radius*sin(degree);
		Z[i]=radius*cos(degree);
		top[i].x=X[i];
		top[i].y=0.5;
		top[i].z=Z[i];
		
		bottom[i].x=X[i];
		bottom[i].y=-.5;
		bottom[i].z=Z[i];
		degree+=2*Pi/((double)radialDivisions);
	}
	//draw  the circle
	for(int i=0;i<radialDivisions;i++){
		if(i==radialDivisions-1){
			C.addTriangle(top[radialDivisions], top[i], top[0]);
			C.addTriangle(bottom[radialDivisions], bottom[0], bottom[i]);
		}else{
			C.addTriangle(top[radialDivisions], top[i], top[i+1]);
			C.addTriangle(bottom[radialDivisions], bottom[i+1], bottom[i]);
		}
	}
	
	Vertex face1, face2;
	//loop through the faces
	for(int i=0;i<radialDivisions;i++){
		Vertex my_left[heightDivisions+1];
		Vertex my_right[heightDivisions+1];
		//if it is the last face
		if(i==radialDivisions-1){
			face1=bottom[i], face2=bottom[0];
		}else{
			face1=bottom[i], face2=bottom[i+1];
		}
		my_left[0]=face1;
		my_right[0]=face2;
		float decre=-0.5;
		//loop through the divisions along the height
		for(int j=1;j<=heightDivisions;j++){
			decre+=1.0/((float)heightDivisions);
			my_left[j].y=decre;
			my_left[j].x=face1.x;
			my_left[j].z=face1.z;
			
			my_right[j].y=decre;
			my_right[j].x=face2.x;
			my_right[j].z=face2.z;
			
			C.addTriangle(my_left[j-1], my_right[j-1], my_left[j]);
			C.addTriangle(my_right[j-1], my_right[j], my_left[j]);
		}
	}
}


///
// makeCone - Create polygons for a cone with unit height, centered at the
// origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cone
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCone( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE

     float Y[radialDivisions], X[radialDivisions];
    //initialize the circle face
    double degre=0;
    Vertex front[radialDivisions+1];
    front[radialDivisions].y=0;
    front[radialDivisions].x=0;
    front[radialDivisions].z=0.5;
    for(int i=0;i<radialDivisions;i++){
		Y[i]=radius*sin(degre);
		X[i]=radius*cos(degre);
		front[i].x=X[i];
		front[i].y=Y[i];
		front[i].z=0.5;

		degre+=2*Pi/((double)radialDivisions);
	}
	//draw the circle faxe
	for(int i=0;i<radialDivisions;i++){
		if(i==radialDivisions-1){
			C.addTriangle(front[radialDivisions], front[i], front[0]);
		}else{
			C.addTriangle(front[radialDivisions], front[i], front[i+1]);
		}
	}
	Vertex peak={0, 0, -0.5};
	
	Vertex face1, face2;
	//loop through the faces
	for(int i=0;i<radialDivisions;i++){
		Vertex my_left[heightDivisions+1];
		Vertex my_right[heightDivisions+1];
		//if it is the last face
		if(i==radialDivisions-1){
			face1=front[0], face2=front[i];
		}else{
			face1=front[i+1], face2=front[i];
		}
		my_left[0]=face1;
		my_right[0]=face2;
		float decre=0.5;
		//loop through the divisions along the height
		for (int j=1;j<=heightDivisions;j++){
			if(j==heightDivisions){
				C.addTriangle(peak, my_left[j-1], my_right[j-1]);
			}else{
				decre-=1.0/((float)heightDivisions);
				degre=decre+0.5;
				
				my_left[j].z=decre;
				my_left[j].x=((1-degre)*peak.x)+(degre*my_left[0].x);
				my_left[j].y=((1-degre)*peak.y)+(degre*my_left[0].y);
				
				my_right[j].z=decre;
				my_right[j].x=((1-degre)*peak.x)+(degre*my_right[0].x);
				my_right[j].y=((1-degre)*peak.y)+(degre*my_right[0].y);
				
				C.addTriangle(my_left[j-1], my_right[j-1], my_left[j]);
				C.addTriangle(my_right[j-1], my_right[j], my_left[j]);
			}
		}
	}
}


///
// makeSphere - Create sphere of a given radius, centered at the origin, 
// using spherical coordinates with separate number of thetha and 
// phi subdivisions.
//
// @param radius - Radius of the sphere
// @param slices - number of subdivisions in the theta direction
// @param stacks - Number of subdivisions in the phi direction.
//
// Can only use calls to C.addTriangle()
///
void makeSphere( Canvas &C, float radius, int slices, int stacks )
{
    // IF DOING RECURSIVE SUBDIVISION:
    //   use a minimum value of 1 instead of 3
    //   add an 'else' clause to set a maximum value of 5
    if( slices < 3 )
        slices = 3;

    if( stacks < 3 )
        stacks = 3;
    
    // YOUR IMPLEMENTATION HERE
    
    //initialize the spere
    Vertex top={0, 0.5, 0}, bottom={0, -0.5, 0};
    Vertex sphere[stacks+1][slices];
    double degree1=0, degree2=0;
    //create vertices
    for(int i=1;i<stacks;i++){
		degree1+=Pi/((float)stacks);
		for(int j=0;j<slices;j++){
			degree2+=2*Pi/((float)slices);
			sphere[i][j].x=radius*cos(degree2)*sin(degree1);
			sphere[i][j].z=radius*sin(degree2)*sin(degree1);
			sphere[i][j].y=radius*cos(degree1);
		}
		
		degree2=0;
	}
	//draw the spere
	for(int i=1;i<=stacks;i++){
		//the bottom stack for the spere
		if(i==stacks){
			for(int j=0;j<slices;j++){
				if(j==slices-1){
					C.addTriangle(bottom, sphere[i-1][j], sphere[i-1][0]);
				}else{
					C.addTriangle(bottom, sphere[i-1][j], sphere[i-1][j+1]);
				}
			}
			//set a maximum value of 5
		}else{
			//top stack for the spere
			if(i==1){
				for(int j=0;j<slices;j++){
					if(j==slices-1){
						C.addTriangle(top, sphere[i][0], sphere[i][j]);
					}else{
						C.addTriangle(top, sphere[i][j+1], sphere[i][j]);
					}
				}
				//from the top to botton 
			}else{
				for(int j=0;j<slices;j++){
					Vertex first, second, third, forth;
					if(j==slices-1){
						first=sphere[i-1][j], second=sphere[i-1][0], 
						third=sphere[i][j], forth=sphere[i][0];
					}else{
						first=sphere[i-1][j], second=sphere[i-1][j+1], 
						third=sphere[i][j], forth=sphere[i][j+1];
					}
					C.addTriangle(first, second, third);
					C.addTriangle(second, forth, third);
				}
			}
		
		}
	}
}
