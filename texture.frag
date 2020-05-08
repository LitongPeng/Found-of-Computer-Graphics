#version 150

// Texture mapping vertex shader
//
// Contributor:  Litong Peng

// INCOMING DATA

// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading and texture mapping computations

//texture and texture coordinates
uniform sampler2D t;
in vec2 coordinates;

// OUTGOING DATA

out vec4 finalColor;

void main()
{
    // Replace this code with your implementation of this shader
//send the texture and the texture coordinates to the texture color
   vec4 color = texture(t,coordinates);
	
    finalColor = color;
}
