//
//  Textures
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//
//  Simple class for setting up texture mapping parameters.
//
//  This code can be compiled as either C or C++.
//

#ifdef __cplusplus
#include <iostream>
#else
#include <stdio.h>
#endif

#include "Textures.h"

// this is here in case you are using SOIL;
// if you're not, it can be deleted.
#include <SOIL.h>

#ifdef __cplusplus
using namespace std;
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint t;

// Add any global definitions and/or variables you need here.

///
// This function loads texture data for the GPU.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the various shaders.
///
void loadTexture( void )
{
    // Add your code here.
    glEnable(GL_TEXTURE_2D);
	int weight;
	int height;
	int c;
	stbi_set_flip_vertically_on_load(true);
	//Load the image
	unsigned char* img = stbi_load("smiley2.png",&weight, &height, &c, STBI_rgb_alpha);

	//if we don't have the image then return
	if (img == NULL)
		return
    //if we have the image 
	//Bind the texture to the image
	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);

	//Set the texture parameters to the shader
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//maintain the property of the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, weight, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);	
}

///
// This function sets up the parameters for texture use.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the various shaders.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void setUpTexture( GLuint program )
{
    // Add your code here.
    //build the active texture
	glActiveTexture(GL_TEXTURE0);
	//Bind the saved texture id with program
	glBindTexture(GL_TEXTURE_2D, t);
    //load program
	glUseProgram(program);

	//Pass the texture value to the shader
	glUniform1i(glGetUniformLocation(program, "t"), GL_TEXTURE0);
}
