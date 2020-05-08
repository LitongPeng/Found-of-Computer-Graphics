//
//  Lighting
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Litong Peng
//
//  Simple class for setting up Phong illumination/shading.
//
//  This code can be compiled as either C or C++.
//

#include "Lighting.h"

// Add any global definitions and/or variables you need here.

///
// This function sets up the lighting, material, and shading parameters
// for the Phong shader.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void setUpPhong( GLuint program )
{
    // Add your code here
    //load the program
    glUseProgram(program);

	//get the uniform location of diffuse color for OpenGL
	GLint dColor = glGetUniformLocation(program, "diffuse");
	//get the uniform location of specular color for OpenGL
	GLint sColor = glGetUniformLocation(program, "specular");
	//get the uniform location of light position for OpenGL
	GLint lPos = glGetUniformLocation(program, "light");

	float d[] = {1.0,0.0,0.0};
	float s[] = {1.0,1.0,1.0};
	float l[] = {0.0,1000.0,1000.0};

	//Pass the uniform location into the shader
	glUniform3fv(dColor, 1, d);
	glUniform3fv(sColor, 1, s);
	glUniform3fv(lPos, 1, l);
}
