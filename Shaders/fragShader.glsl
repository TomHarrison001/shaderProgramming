#version 330 core

out vec4 FragColour;
in vec3 normal;
in vec3 posInWS;
in vec2 uv;
in mat3 TBN;

uniform vec3 viewPos;

// material uniforms and variables
uniform sampler2D diffuseMap;
vec3 objColour = texture(diffuseMap, uv).rgb;
uniform sampler2D specularMap;
float specStrength = texture(specularMap, uv).r;
uniform sampler2D normalMap;
vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS);
uniform float shine;
uniform bool useDir, usePoint, useSpot, useNM;

// directional light uniforms
uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform float ambientFactor;

// calculation functions
vec3 calculateAmbient(vec3 lColour);
vec3 calculateDiffuse(vec3 lColour, vec3 lDir);
vec3 calculateSpecular(vec3 lColour, vec3 lDir);
float calculateAttenuation(vec3 lPos, vec3 lConstants);
float calculateIntensity(vec3 vDir, vec3 lDir, vec2 lRadii);

vec3 getDirectionalLight();
vec3 getPointLight(int i);
vec3 getSpotLight(int i);
vec3 toneMapping(vec3 x);

struct pointLight {
    vec3 colour;
    vec3 position;
    vec3 constants;
};

#define numPointLights 5
uniform pointLight pLight[numPointLights];

struct spotLight {
    vec3 colour;
    vec3 position;
    vec3 constants;
    vec3 direction;
    vec2 radii;
};

#define numSpotLights 1
uniform spotLight sLight[numSpotLights];

void main() {
    if (useNM) {
        n = texture(normalMap, uv).rgb;
        n = n * 2.0 - 1.0;
        n = normalize(TBN * n);
    }
    vec3 result = vec3(0.0);
    if (useDir) result += getDirectionalLight();
    for (int i = (usePoint) ? 0 : numPointLights; i < numPointLights; i++) {
        result += getPointLight(i);
    }
    for (int i = (useSpot) ? 0 : numSpotLights; i < numSpotLights; i++) {
        result += getSpotLight(i);
    }
    result = toneMapping(result);
    FragColour = vec4(result, 1.0);
}

vec3 getDirectionalLight() {
    // ambient
    vec3 ambient = calculateAmbient(lightColour);

    // diffuse
    vec3 diffuse = calculateDiffuse(lightColour, -lightDirection);

    // Blinn Phong specular
    vec3 specular = calculateSpecular(lightColour, -lightDirection);

    return ambient + diffuse + specular;
}

vec3 getPointLight(int i) {
    // attenuation
    float attn = calculateAttenuation(pLight[i].position, pLight[i].constants);
    vec3 lightDir = normalize(pLight[i].position - posInWS);

    // ambient
    vec3 ambient = calculateAmbient(pLight[i].colour);
    
    // diffuse
    vec3 diffuse = calculateDiffuse(pLight[i].colour, lightDir);

    // Blinn Phong specular
    vec3 specular = calculateSpecular(pLight[i].colour, lightDir);

    ambient *= attn;
    diffuse *= attn;
    specular *= attn;

    return diffuse + specular;
}

vec3 getSpotLight(int i) {
    // attenuation
    float attn = calculateAttenuation(sLight[i].position, sLight[i].constants);
    vec3 lightDir = normalize(sLight[i].position - posInWS);

    // ambient
    vec3 ambient = calculateAmbient(sLight[i].colour);
    
    // diffuse
    vec3 diffuse = calculateDiffuse(sLight[i].colour, lightDir);

    // Blinn Phong specular
    vec3 specular = calculateSpecular(sLight[i].colour, lightDir);
    
    ambient *= attn;
    diffuse *= attn;
    specular *= attn;

    // intensity
    float intensity = calculateIntensity(-lightDir, normalize(sLight[i].direction), sLight[i].radii);
    
    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    return diffuse + specular;
}

vec3 toneMapping(vec3 x) {
    const float a = 2.51, b = 0.03, c = 2.43, d = 0.59, e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * a + d) + e), 0.0, 1.0);
    // const float a = 0.15, b = 0.50, c = 0.10, d = 0.20, e = 0.02, f = 0.30;
    // return clamp((x * (a * x + c * b)) / (x * (a * x + b) + d * f) - e / f, 0.0, 1.0);
}

vec3 calculateAmbient(vec3 lColour) {
    return objColour * lColour * ambientFactor;
}

vec3 calculateDiffuse(vec3 lColour, vec3 lDir) {
    float diffuseFactor = dot(n, lDir);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = objColour * lColour * diffuseFactor;
    return diffuse;
}

vec3 calculateSpecular(vec3 lColour, vec3 lDir) {
    vec3 H = normalize(lDir + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, shine);
    vec3 specular = lColour * specLevel * specStrength;
    return specular;
}

float calculateAttenuation(vec3 lPos, vec3 lConstants) {
    float distance = length(lPos - posInWS);
    return 1.0 / (lConstants.x + lConstants.y * distance + lConstants.z * distance * distance);
}

float calculateIntensity(vec3 vDir, vec3 lDir, vec2 lRadii) {
    float theta = dot(vDir, lDir);
    float denom = lRadii.x - lRadii.y;
    float intensity = (theta - lRadii.y) / denom;
    return clamp(intensity, 0.0, 1.0);
}
