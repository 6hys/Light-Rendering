#version 150

precision mediump float;

in vec3 vertWorldPosition;
flat in vec3 normalVector;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 color;

out vec4 outputColor;

void main() {

    vec3 lightDir = normalize(lightPosition - vertWorldPosition);
    
    float lightVal = clamp(dot(lightDir, normalVector), 0.0, 1.0);

    outputColor = vec4(lightVal, lightVal, lightVal, 1.0) * lightColor * color;
    outputColor.w = 1.0;
}
