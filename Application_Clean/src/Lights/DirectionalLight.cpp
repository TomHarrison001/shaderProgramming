#pragma once

#include "Lights/DirectionalLight.h"

// Constructor takes in colour, direction and ambient (default to 0.5)
DirectionalLight::DirectionalLight(glm::vec3 colour, glm::vec3 direction, float ambient) :
	Light(colour), m_direction(direction), m_ambientFactor(ambient) {}
// sets uniforms in the fragment shader for directional light attributes
void DirectionalLight::setLightUniforms(Shader* shader) {
	shader->use();
	shader->setVec3("lightDirection", m_direction);
	shader->setVec3("lightColour", m_colour);
	shader->setFloat("ambientFactor", m_ambientFactor);
}
