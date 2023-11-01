#include "Lights/PointLight.h"

PointLight::PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants) :
	Light(colour), m_position(position), m_constants(constants) {}
void PointLight::setLightUniforms(Shader* shader) {
	shader->use();
	for (int i = 0; i < 1; i++) {
		std::string str = "pointLight[" + std::to_string(i) + ']';
		shader->setVec3(str + ".plightPosition", m_position);
		shader->setVec3(str + ".plightColour", m_colour);
		shader->setVec3(str + ".pAttenuation", m_constants);
	}
}
