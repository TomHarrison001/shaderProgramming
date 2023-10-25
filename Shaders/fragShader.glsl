#version 330 core

out vec4 FragColour;
in vec3 vertexColour;

uniform float time;

void main() {
    FragColour = vec4(1.0, 0.7, 0.0, 1.0);  // RGBA - vertexColour * time
}
