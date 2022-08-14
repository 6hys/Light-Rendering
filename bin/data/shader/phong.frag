#version 150

precision mediump float;

in vec3 vertWorldPosition;
in vec3 normalVector;

uniform float shininess;
uniform vec4 color;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec4 lightColor;
uniform int isSpecular;
uniform mat4 modelViewMatrix;

out vec4 outputColor;

void main() {

  //calculate normal in world coordinates
  mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));
  vec3 vertexNormal = normalize(normalMatrix * normalVector);

  vec3 lightDir = normalize(lightPosition - vertWorldPosition);
  vec3 viewDir = normalize(cameraPosition - vertWorldPosition);
  vec3 incidence = -lightDir;
  vec3 reflection = reflect(incidence, vertexNormal);

  // NdotL
  // N = normal
  // L = light direction normalised
  float NdotL = clamp(dot(normalVector, lightDir), 0.0, 1.0);

  if(isSpecular == 1)
  {
    // RdotV
    // R = normalised reflection
    // V = normalised view direction
    float RdotV = clamp(dot(reflection, viewDir), 0.0, 1.0);

    outputColor = (color * NdotL) + (lightColor * pow(RdotV, shininess));
  } 
  else
  {
    outputColor = (color * NdotL);
  }

  outputColor.w = 1.0;
}
