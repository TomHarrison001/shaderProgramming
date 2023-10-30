#version 330 core

out vec4 FragColour;
in vec3 normal;
in vec3 posInWS;

uniform vec3 viewPos;
uniform vec3 cubeColour;
uniform vec3 lightColour;
uniform vec3 lightDirection;

uniform float ambientFactor;
uniform float shine;
uniform float specStrength;

vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS);

vec3 getDirectionalLight();

void main() {
    vec3 result = getDirectionalLight();
    FragColour = vec4(result, 1.0);
}

vec3 getDirectionalLight() {
    // ambient
    vec3 ambient = cubeColour * lightColour * ambientFactor;

    // diffuse
    float diffuseFactor = dot(n, -lightDirection);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * lightColour * diffuseFactor;

    // Blinn Phong specular
    vec3 H = normalize(-lightDirection + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, shine);
    vec3 specular = lightColour * specLevel * specStrength;

    return ambient + diffuse + specular;
}
