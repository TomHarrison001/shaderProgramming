#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aUV;
layout(location = 3) in vec3 aTangent;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 normal;
out vec3 posInWS;
out vec2 uv;
out vec3 tangent;

void main() {
    normal = mat3(transpose(inverse(Model))) * aNorm;
    vec4 worldSpace = Model * vec4(aPos, 1.0);
    posInWS = worldSpace.xyz;
    uv = aUV;
    tangent = aTangent;
    gl_Position = Projection * View * worldSpace;
}
