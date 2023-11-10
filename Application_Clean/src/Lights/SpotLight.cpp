#pragma once

#include "Lights/SpotLight.h"

int SpotLight::sTotal_ = 0;

SpotLight::SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 dir, glm::vec2 radii, glm::vec3 constants) :
	PointLight(colour, position, constants), m_direction(dir), m_radii(radii) {
	m_index = sTotal_++;
}
void SpotLight::setLightUniforms(Shader* shader) {
	shader->use();
	std::string str = "sLight[" + std::to_string(m_index) + "].";
	shader->setVec3(str + "colour", m_colour);
	shader->setVec3(str + "position", m_position);
	shader->setVec3(str + "constants", m_constants);
	shader->setVec3(str + "direction", m_direction);
	shader->setVec2(str + "radii", m_radii);
}
