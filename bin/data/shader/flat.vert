#version 150

in vec4 position;
in vec3 normal;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

out vec3 vertWorldPosition;
flat out vec3 normalVector;


void main() {

    gl_Position = modelViewProjectionMatrix * position;

    // get vert location in world coords
    vertWorldPosition = vec3(modelViewMatrix * position);

    normalVector = normal;
}