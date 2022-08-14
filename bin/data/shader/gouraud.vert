#version 150

in vec4 position;
in vec3 normal;

out vec4 vertexColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec3 lightPosition;
uniform float shininess;
uniform vec4 color;
uniform vec4 lightColor;
uniform int isSpecular;

void main(){
    mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));

    vec3 vertWorldPosition = vec3(modelViewMatrix * position);
    vec3 vertexNormal = normalize(normalMatrix * normal);

    vec3 lightDir = normalize(lightPosition - vertWorldPosition);   
    vec3 incidenceNorm = normalize(-vertWorldPosition);
    vec3 reflection = normalize(-reflect(lightDir, vertexNormal));  

    // calculate diffuse 
    float diffuse = clamp(dot(vertexNormal, lightDir), 0.0, 1.0);    

    // initialise specular
    float specular = 0.0;

    if(isSpecular == 1)
    {
        // calculate specular
        float specularValue = clamp(dot(reflection, incidenceNorm), 0.0, 1.0);
        specular = pow(specularValue, 0.3 * shininess);
    }

    vertexColor = (diffuse * color) + (specular * lightColor);
    vertexColor.w = 1.0; 

    gl_Position = modelViewProjectionMatrix * position;
}