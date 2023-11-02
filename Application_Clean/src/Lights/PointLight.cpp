#include "Lights/PointLight.h"

PointLight::PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants, int index) :
	Light(colour), m_position(position), m_constants(constants), m_index(index) {}
void PointLight::setLightUniforms(Shader* shader) {
	shader->use();
	std::string str = "pLight[" + std::to_string(m_index) + "].";
	shader->setVec3(str + "position", m_position);
	shader->setVec3(str + "colour", m_colour);
	shader->setVec3(str + "constants", m_constants);
}
