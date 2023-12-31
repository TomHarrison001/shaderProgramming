#pragma once

#include "Lights/SpotLight.h"

// static int to count the total amount of SpotLight objects
int SpotLight::sTotal_ = 0;

// Constructor takes in colour, position, direction, radii and constants
// index calculated from sTotal_
SpotLight::SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 dir, glm::vec2 radii, glm::vec3 constants, int index) :
	PointLight(colour, position, constants, index), m_direction(dir), m_radii(radii) {}
// sets uniforms in the fragment shader for spotlight attributes
void SpotLight::setLightUniforms(Shader* shader) {
	shader->use();
	std::string str = "sLight[" + std::to_string(m_index) + "].";
	shader->setVec3(str + "colour", m_colour);
	shader->setVec3(str + "position", m_position);
	shader->setVec3(str + "constants", m_constants);
	shader->setVec3(str + "direction", m_direction);
	shader->setVec2(str + "radii", m_radii);
}
