#version 150

// Phong fragment shader
//
// Contributor:  Litong Peng

// INCOMING DATA

// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading computations

//diffuse lighting color
uniform vec3 diffuse;
//light position color
uniform vec3 light;
//diffuse lighting color
uniform vec3 specular;

//Normal vector
in vec3 n;
//position vector
in vec3 p;

// OUTGOING DATA
out vec4 finalColor;

void main()
{
    // Replace this code with your implementation of this shader
	//Calculate the normal of the light
	vec3 nn = normalize(n);
//Calculate the direction of the light
	vec3 l = normalize(light - p);
	//Get the lambertian value
	float lambertian = max(dot(l,nn), 0);
	
	float s = 0.0;
	
	//If we have a light
	if (lambertian > 0.0) {
		//Calculate the reflection direction
		vec3 r = reflect(-l, nn);
//Calculate the view direction
		vec3 v = normalize(-p);

		//Calculate the specular angle
		float angle = max(dot(r, v), 0.0);
//Calculate the specular intensity
		s = pow(angle, pow(4.0,16.0));
	}

	//Calculate the final color
	finalColor = vec4(lambertian*diffuse + s*specular, 1.0);
}
