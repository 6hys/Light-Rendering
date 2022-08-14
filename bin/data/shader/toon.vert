#version 150

in vec4 position;
in vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

out vec3 vertWorldPosition;
out vec3 normalVector;

void main() 
{
	// get vert location in world coords
    vertWorldPosition = vec3(modelViewMatrix * position);

    normalVector = normal;
    
	gl_Position = modelViewProjectionMatrix * position;
}