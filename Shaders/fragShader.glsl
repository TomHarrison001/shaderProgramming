#version 330 core

out vec4 FragColour;
in vec3 normal;
in vec3 posInWS;

uniform vec3 viewPos;

// Geometry Uniforms
uniform vec3 objColour;
uniform float objShine;
uniform float objSpecStrength;

// Directional Light Uniforms
uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform float ambientFactor;

vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS);

vec3 getDirectionalLight();
vec3 getPointLight(int i);
vec3 getSpotLight(int i);
vec3 toneMapping(vec3 x);

struct pointLight {
    vec3 colour;
    vec3 position;
    vec3 constants;
};

#define numPointLights 1
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
    vec3 result = getDirectionalLight();
    for (int i = 0; i < numPointLights; i++) {
        result += getPointLight(i);
    }
    for (int i = 0; i < numSpotLights; i++) {
        result += getSpotLight(i);
    }
    result = toneMapping(result);
    FragColour = vec4(result, 1.0);
}

vec3 getDirectionalLight() {
    // ambient
    vec3 ambient = objColour * lightColour * ambientFactor;

    // diffuse
    float diffuseFactor = dot(n, -lightDirection);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = objColour * lightColour * diffuseFactor;

    // Blinn Phong specular
    vec3 H = normalize(-lightDirection + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, objShine);
    vec3 specular = lightColour * specLevel * objSpecStrength;

    return ambient + diffuse + specular;
}

vec3 getPointLight(int i) {
    float distance = length(pLight[i].position - posInWS);
    float attn = 1.0 / (pLight[i].constants.x + pLight[i].constants.y * distance + pLight[i].constants.z * distance * distance);
    vec3 lightDir = normalize(pLight[i].position - posInWS);

    // ambient
    vec3 ambient = objColour * pLight[i].colour * ambientFactor;
    
    // diffuse
    float diffuseFactor = dot(n, -lightDir);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = objColour * pLight[i].colour * diffuseFactor;

    // Blinn Phong specular
    vec3 H = normalize(-lightDir + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, objShine);
    vec3 specular = pLight[i].colour * specLevel * objSpecStrength;

    ambient *= attn;
    diffuse *= attn;
    specular *= attn;

    return diffuse + specular;
}

vec3 getSpotLight(int i) {
    float distance = length(sLight[i].position - posInWS);
    float attn = 1.0 / (sLight[i].constants.x + sLight[i].constants.y * distance + sLight[i].constants.z * distance * distance);
    vec3 lightDir = normalize(sLight[i].position - posInWS);

    // ambient
    vec3 ambient = objColour * sLight[i].colour * ambientFactor;
    
    // diffuse
    float diffuseFactor = dot(n, lightDir);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = objColour * sLight[i].colour * diffuseFactor;

    // Blinn Phong specular
    vec3 H = normalize(viewDir + lightDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, objShine);
    vec3 specular = sLight[i].colour * specLevel * objSpecStrength;
    
    ambient *= attn;
    diffuse *= attn;
    specular *= attn;

    float theta = dot(-lightDir, normalize(sLight[i].direction));
    float denom = sLight[i].radii.x - sLight[i].radii.y;
    float intensity = (theta - sLight[i].radii.y) / denom;
    intensity = clamp(intensity, 0.0, 1.0);
    
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
