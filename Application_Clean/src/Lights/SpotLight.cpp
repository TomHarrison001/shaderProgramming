#include "Lights/SpotLight.h"

SpotLight::SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants, int index, glm::vec3 dir, glm::vec2 radii) :
	PointLight(colour, position, constants, index), m_direction(dir), m_radii(radii) {}
void SpotLight::setLightUniforms(Shader* shader) {
	shader->use();
	std::string str = "sLight[" + std::to_string(m_index) + "].";
	shader->setVec3(str + "colour", m_colour);
	shader->setVec3(str + "position", m_position);
	shader->setVec3(str + "constants", m_constants);
	shader->setVec3(str + "direction", m_direction);
	shader->setVec2(str + "radii", m_radii);
}
