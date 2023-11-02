#version 330 core

out vec4 FragColour;
in vec3 normal;
in vec3 posInWS;

uniform vec3 viewPos;
uniform vec3 cubeColour;

// Directional Light Uniforms
uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform float ambientFactor;

uniform float shine;
uniform float specStrength;

// Point Light Uniforms
uniform vec3 plightColour;
uniform vec3 plightPosition;
uniform vec3 pAttenuation;

// Spot Light Uniforms
uniform vec3 slightPosition;
uniform vec3 slightColour;
uniform vec3 sAttenuation;
uniform vec3 sDirection;
uniform vec2 sRadii;

vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS);

vec3 getDirectionalLight();
vec3 getPointLight(int i);
vec3 getSpotLight();

struct pointLight {
    vec3 colour;
    vec3 position;
    vec3 constants;
};

#define numPointLights 1
uniform pointLight pLight[numPointLights];

void main() {
    vec3 result = getDirectionalLight();
    for (int i = 0; i < numPointLights; i++) {
        result += getPointLight(i);
    }
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

vec3 getPointLight(int i) {
    float distance = length(pLight[i].position - posInWS);
    float attn = 1.0 / (pLight[i].constants.x + pLight[i].constants.y * distance + pLight[i].constants.z * distance * distance);
    vec3 lightDir = normalize(pLight[i].position - posInWS);

    // ambient
    vec3 ambient = cubeColour * pLight[i].colour * ambientFactor;
    
    // diffuse
    float diffuseFactor = dot(n, -lightDir);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * pLight[i].colour * diffuseFactor;

    // Blinn Phong specular
    vec3 H = normalize(-lightDir + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, shine);
    vec3 specular = pLight[i].colour * specLevel * specStrength;

    ambient *= attn;
    diffuse *= attn;
    specular *= attn;

    return diffuse + specular;
}
